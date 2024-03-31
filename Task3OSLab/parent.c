#include"tools.h"
/* All functions which are used are defined in tools.c and
   declared in tools.h.
   Please refer to tools.c for the implementation of the functions.
   For the interface of the functions refer to tools.h.
*/

int main(int argc,char *argv[]){
	//allocated_space array is used to store all pointers to dynamically allocated memory.
	void** allocated_space = malloc(0);  
	//Store the input from the user into a parser struct.Defined in tools.h.
	struct parser input = input_parser(argc,argv);

	if(input.num_of_children == -1){
		//Parser failed.See definition of input_parser.
		free_all(allocated_space);
		return 1;
	}

	//val stores the integer to be processed by the children.
	int val;
	//In child_pid the pids of the created children will be stored.
	pid_t *child_pid = allocate_array(input.num_of_children * sizeof(pid_t),allocated_space);
	pid_t parent_pid = getpid();
    //pipes_fc will be used to send data from parent to child
	//pipes_cf will be used to send data from child to parent
    int** pipes_fc = allocate_array(input.num_of_children * sizeof(int*),allocated_space);
	int** pipes_cf = allocate_array(input.num_of_children * sizeof(int*),allocated_space);

	for(int i = 0;i < input.num_of_children;i++){
		pipes_fc[i] = allocate_array(2 * sizeof(int),allocated_space);
		pipes_cf[i] = allocate_array(2 * sizeof(int),allocated_space);
	}

	for(int i = 0;i < input.num_of_children;i++){
		//Creating one pipe for each child.
		if(pipe(pipes_fc[i]) == -1 || pipe(pipes_cf[i]) == -1){
			perror("Failed to create pipe.");
			free_all(allocated_space);
			return 1;
		}
	}

	printf("[Parent] [%d] Parent process started.\n"
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
			while(true){
				int gIndex = i;
				//Child does not need the writing end of the fc pipe.
				close(pipes_fc[i][1]);
				if(read(pipes_fc[i][0],&val,sizeof(int)) == -1){
					perror("Error while reading from pipe.");
					close(pipes_fc[i][0]);
					exit(1);
				}
				printf("[Child %d] [%d] Child received %d!\n", gIndex, getpid(), val);
				val --;
				sleep(1);
				write(pipes_cf[i][1],&val,sizeof(int));
				printf("[Child %d] [%d] Child Finished hard work, writing back %d\n",gIndex,getpid(),val);
			}
			exit(0);
		}
		if(child_pid_now > 0){		
			//This code is executed only by the parent process.		
			printf("[Parent] [%d] Created child %d (PID=%u).\n"
			,parent_pid,i,child_pid_now);
			child_pid[i] = child_pid_now;
			
		}
	}
	int selected_child = 0;
	while(true){
		struct pollfd *poll_fds = allocate_array(input.num_of_children * sizeof(struct pollfd),allocated_space);
		for(int i = 0;i < input.num_of_children;i++){
			poll_fds[i].fd = pipes_cf[i][0];
			poll_fds[i].events = POLLIN;
		}
		printf("[Parent] [%d] Type a number to send job to a child!\n",parent_pid);
		char line[100];
		while(fgets(line,sizeof(line) + 1,stdin) != NULL){
			if(line[0] == '\n'){
				continue;
			}
			break;
		}
		if(line[0] == 'q'){
			break;
		}
		int to_send = atoi(line);
		if(to_send == 0){
			printf("Invalid input!\n");
		}
		val = to_send;
		if(input.scheduling_process == RANDOM){
			srand(time(NULL));
			selected_child = rand() % input.num_of_children;
		}
		write(pipes_fc[selected_child][1],&val,sizeof(int));
		close(pipes_fc[selected_child][0]);
		//Poll for the child that has finished its job.
		int ret = poll(poll_fds,input.num_of_children,-1);
		if(ret == -1){
			perror("Error while polling.");
			free_all(allocated_space);
			return 1;
		}
		for(int i = 0;i < input.num_of_children;i++){
			if(poll_fds[i].revents & POLLIN){
				selected_child = i;
				break;
			}
		}
		read(pipes_cf[selected_child][0],&val,sizeof(int));
		printf("[Parent] [%d] Received %d from child %d.\n",parent_pid,val,selected_child);
		if(input.scheduling_process == ROUND_ROBIN){
			selected_child = (selected_child + 1) % input.num_of_children;
		}
	}
	close_all_pipes(pipes_cf,pipes_fc,input.num_of_children);
	//Kill all children.
	for(int i = 0;i < input.num_of_children;i++){
		kill(child_pid[i],SIGTERM);
	}
	free_all(allocated_space);
    return 0;
}
