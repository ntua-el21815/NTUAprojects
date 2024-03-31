#include"tools.h"

int main(int argc,char *argv[]){
	//allocated_space array is used to store all pointers to dynamically allocated memory.
	void** allocated_space = malloc(0);  
	//Store the input from the user into a parser struct.Defined in tools.h.
	struct parser input = input_parser(argc,argv);
	int val;
	//In child_pid the pids of the created children will be stored.
	pid_t *child_pid = allocate_array(input.num_of_children * sizeof(pid_t),allocated_space);
	pid_t parent_pid = getpid();
        //Create one pipe for each child.
    int** pipes = allocate_array(input.num_of_children * sizeof(int*),allocated_space);
	if(input.num_of_children == -1){
		//Parser failed.See definition of input_parser.
		free_all(allocated_space);
		return 1;
	}
	for(int i = 0;i < input.num_of_children;i++){
		pipes[i] = allocate_array(2 * sizeof(int),allocated_space);
	}
	for(int i = 0;i < input.num_of_children;i++){
		//Creating one pipe for each child.
		if(pipe(pipes[i]) == -1){
			perror("Failed to create pipe.");
			free_all(allocated_space);
			return 1;
		}
	}
	printf("[PARENT/PID=%u] Parent process started.\n"
	"Number of children to create: %d, scheduling process: %s.\n",
	parent_pid,input.num_of_children,
	input.scheduling_process == RANDOM ? "random" : "round-robin");
	for(int i = 0;i < input.num_of_children;i++){
		//Creating the children one by one.
		int child_pid_now = fork();
		if(child_pid_now < 0){
			perror("Error while creating child.");
			for(int j = 0;j < i ;j++){
				//Making sure that if parent exits abnormally,there are no zombie children left.
				kill(child_pid[j],SIGKILL);
			}
			free_all(allocated_space);
            exit(1);
		}
		if(child_pid_now == 0){
			//This code is executed only by the new child process.
			/*if(run_child("./childexec",i,argv[1][i]) == -1){
				for(int j = 0;j < i;j++){
					kill(child_pid[j],SIGKILL);
				}
				kill(parent_pid,SIGKILL);
				exit(1);		
			}*/
			close(pipes[i][1]);
			if(read(pipes[i][0],&val,sizeof(int)) == -1){
				perror("Error while reading from pipe.");
				close(pipes[i][0]);
				exit(1);
			}
			printf("[CHILD/PID=%u] Starting Work.\n",getpid());
			val --;
			sleep(1);
			printf("[CHILD/PID=%u] Finished Work.Result : %d \n",getpid(),val);
			close(pipes[i][0]);
			exit(0);
		}
		if(child_pid_now > 0){		
			//This code is executed only by the parent process.		
			printf("[PARENT/PID=%u] Created child %d (PID=%u).\n"
			,parent_pid,i,child_pid_now);
			child_pid[i] = child_pid_now;
			val = i;
			printf("Parent writing to pipe...\n");
			close(pipes[i][0]);
			write(pipes[i][1],&val,sizeof(int));
			close(pipes[i][1]);
			waitpid(child_pid_now,NULL,0);
		}
	}
	free_all(allocated_space);
    return 0;
}
