#include"tools.h"
/* All functions which are used are defined in tools.c and
   declared in tools.h.
   Please refer to tools.c for the implementation of the functions.
   For the interface of the functions refer to tools.h.
*/

int main(int argc,char *argv[]){
	
	//allocated_space array is used to store all pointers to dynamically allocated memory.
	//This is done so that all memory can be freed at the end of the program.
	void** allocated_space = malloc(0);  
	
	//Store the input from the user into a parser struct.Defined in tools.h.
	struct parser input = input_parser(argc,argv);

	if(input.num_of_children == -1){
		//Parser failed.See definition of input_parser.
		free_all(allocated_space);
		return 1;
	}

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

			//val stores the value sent by parent for processing.
			int val;
			int gIndex = i;

			/* The write end of the fc pipe is not needed by the child.
			   The read end of the cf pipe is not needed by the child.
			   Both are closed.
			*/
			if(close(pipes_fc[gIndex][1]) == -1 || close(pipes_cf[gIndex][0]) == -1){
				perror("Error while closing pipe.");
				close(pipes_fc[gIndex][0]);
				exit(1);
			}

			while(true){
				if(read(pipes_fc[gIndex][0],&val,sizeof(int)) == -1){
					perror("Error while reading from pipe.");
					close(pipes_fc[gIndex][0]);
					exit(1);
				}
				
				printf("[Child %d] [%d] Child received %d!\n", gIndex, getpid(), val);
				//Message's only purpose is synchronization.
				char* msg = "ready";
				if(write(pipes_cf[gIndex][1],msg,strlen(msg) + 1) == -1){
					perror("Error while writing to pipe.");
					close(pipes_cf[gIndex][1]);
					exit(1);
				}
				val --;
				sleep(10);
				printf("[Child %d] [%d] Child Finished hard work, writing back %d\n",gIndex,getpid(),val);
				if(write(pipes_cf[gIndex][1],&val,sizeof(int)) == -1){
					perror("Error while writing to pipe.");
					close(pipes_cf[gIndex][1]);
					exit(1);
				}
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
	
	//Parent process code.
	/*val stores the value sent by parent for processing.
	  selected_child is initialized to 0 for round-robin,else it is randomly selected.
	  line is used to store the input from the user.
	  MAX_INPUT defined in tools.h.
	*/
	int val;
	int selected_child = 0;
	char line[MAX_INPUT];
	fcntl(0, F_SETFL, fcntl(0, F_GETFL) | O_NONBLOCK);
	struct pollfd *poll_fds = allocate_array(input.num_of_children * sizeof(struct pollfd),allocated_space);
	for(int i = 0;i < input.num_of_children;i++){
		//Setting up polling for all the pipes.
		poll_fds[i].fd = pipes_cf[i][0];
		poll_fds[i].events = POLLIN;
		//The write end of the cf pipe and the read end of the fc pipe are not needed by the parent.
		if(close(pipes_fc[i][0]) == -1 || close(pipes_cf[i][1]) == -1){
			perror("Error while closing pipe.");
			kill_children(child_pid,input.num_of_children);
			free_all(allocated_space);
			return 1;
		}
	}
	printf("[Parent] [%d] Type a number to send job to a child!\n",parent_pid);
	while(true){
		while(true){
			int input_length = read(0,line,100);
			if(input_length > 0){
				line[input_length - 1] = '\0';
				break;
			}
			int ret = poll(poll_fds,input.num_of_children,100);
			if(ret == -1){
				perror("Error while polling.");
				kill_children(child_pid,input.num_of_children);
				free_all(allocated_space);
				return 1;
			}
			for(int i = 0;i < input.num_of_children;i++){
				if(poll_fds[i].revents & POLLIN){
					read(pipes_cf[i][0],&val,sizeof(int));
					printf("[Parent] [%d] Received %d from child %d.\n",parent_pid,val,i);
					//Reprompt the user to send a job to a child.
					printf("[Parent] [%d] Type a number to send job to a child!\n",parent_pid);
				}
			}
		}
		if(quit(line)){
			break;
		}
		int to_send = atoi(line);
		if(to_send == 0){
			printf("[Parent] [%d] Invalid input.\n",parent_pid);
			printf("[Parent] [%d] Type a number to send job to a child!\n",parent_pid);
			continue;
		}
		if(input.scheduling_process == RANDOM){
			srand(time(NULL));
			selected_child = rand() % input.num_of_children;
		}
		val = to_send;
		write(pipes_fc[selected_child][1],&val,sizeof(int));
		//Reprompt the user to send a job to a child.
		char msg[strlen("ready") + 1];
		read(pipes_cf[selected_child][0],msg,strlen("ready") + 1);
		if (strcmp(msg, "ready") != 0) {
			printf("Did not read ready from child.\n");
			while(!kill_children(child_pid,input.num_of_children));
			free_all(allocated_space);
			return 1;
		}
		printf("[Parent] [%d] Type a number to send job to a child!\n",parent_pid);
		if(input.scheduling_process == ROUND_ROBIN){
			selected_child = (selected_child + 1) % input.num_of_children;
		}
	}
	close_all_pipes(pipes_cf,pipes_fc,input.num_of_children);
	//Kill all children.
	while(!kill_children(child_pid,input.num_of_children));
	waitpid(-1,NULL,0);
	free_all(allocated_space);
    return 0;
}
