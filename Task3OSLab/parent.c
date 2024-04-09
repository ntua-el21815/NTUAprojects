#include"tools.h"
/* All functions which are used are defined in tools.c and
   declared in tools.h.
   Please refer to tools.c for the implementation of the functions.
   For the interface of the functions refer to tools.h.
*/

int main(int argc,char *argv[]){
	
	//allocated_space array is used to store all pointers to dynamically allocated memory.
	//This is done so that all memory can be freed at the end of the program.
	struct list* allocated_space = malloc(sizeof(struct list));
	//Initialize the list.
	allocated_space -> ptr = NULL;
	allocated_space -> next = NULL;

	//Store the input from the user into a parser struct.Defined in tools.h.
	struct parser input = input_parser(argc,argv);

	if(input.num_of_children == -1){
		//Parser failed.See definition of input_parser.
		free_all(allocated_space);
		return 1;
	}

	//In child_pid the pids of the created children will be stored.
	pid_t *child_pid = (pid_t*) allocate_array(input.num_of_children * sizeof(pid_t),allocated_space);
	pid_t parent_pid = getpid();
    
	//pipes_fc will be used to send data from parent to child
	//pipes_cf will be used to send data from child to parent
	int** pipes_fc = (int**) allocate_array(input.num_of_children * sizeof(int*),allocated_space);
	int** pipes_cf = (int**) allocate_array(input.num_of_children * sizeof(int*),allocated_space);

	for(int i = 0;i < input.num_of_children;i++){
		pipes_fc[i] = (int*) allocate_array(2 * sizeof(int),allocated_space);
		pipes_cf[i] = (int*) allocate_array(2 * sizeof(int),allocated_space);
	}
	
	for(int i = 0;i < input.num_of_children;i++){
		//Creating one pipe for each child.
		if(pipe(pipes_fc[i]) == -1 || pipe(pipes_cf[i]) == -1){
			perror("Failed to create pipe.");
			free_all(allocated_space);
			return 1;
		}
	}

	printf(TURQUOISE "[Parent] [%d] Parent process started.\n"
	"Number of children to create: %d, scheduling process: %s.\n" RESET,
	parent_pid,input.num_of_children,
	input.scheduling_process == RANDOM ? "random" : "round-robin");

	for(int i = 0;i < input.num_of_children;i++){
		//Creating the children one by one.
		pid_t child_pid_now = fork();

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
				exit(1);
			}

			while(true){
				char* COLOUR = choose_colour(gIndex%6);
				if(read(pipes_fc[gIndex][0],&val,sizeof(int)) == -1){
					perror("Error while reading from pipe.");
					continue;//Retry if there is an error.
				}
				printf("%s",COLOUR);
				printf("[Child %d] [%d] Child received %d!\n" RESET, gIndex, getpid(), val);
				//Message's only purpose is synchronization.
				//Every time a child has read the value it acknowledges,so that the
				//parent can repromt the user for input.
				char msg[] = "ready";
				if(write(pipes_cf[gIndex][1],&msg,strlen(msg) + 1) == -1){
					perror("Error while writing to pipe.");
					continue;//Retry if there is an error.
				}
				val --;
				sleep(10);
				//Converting to string to process at the parent's end.
				char back[MAX_INPUT];
				snprintf(back,MAX_INPUT,"%d",val);
				printf("%s",COLOUR);
				printf("[Child %d] [%d] Child Finished hard work, writing back %s\n" RESET 
				,gIndex,getpid(),back);
				if(write(pipes_cf[gIndex][1],&back,strlen(back) + 1) == -1){
					perror("Error while writing to pipe.");
					continue;//Retry if there is an error.
				}
			}
			exit(0);
		}
		if(child_pid_now > 0){		
			//This code is executed only by the parent process.		
			printf(TURQUOISE "[Parent] [%d] Created child %d (PID=%u).\n" RESET
			,parent_pid,i,child_pid_now);
			child_pid[i] = child_pid_now;
			
		}
	}
	
	//Parent process code.
	/*
	  TIMEOUT is the time polling time to get tha value back from children.
	  val stores the value sent by parent for processing.
	  selected_child is initialized to 0 for round-robin,else it is randomly selected.
	  msg is used to store the message received from the child.
	  line is used to store the input from the user.
	  MAX_INPUT defined in tools.h.
	*/
	const int TIMEOUT = 100;
	int val;
	int selected_child = 0;
	char msg[MAX_INPUT];
	char line[MAX_INPUT];
	//Setting stdin to non blocking.So that the parent can continue
	//without consantly waiting for input from the user.
	if(set_stdin_nonblocking() == -1){
		kill_children(child_pid,input.num_of_children);
		free_all(allocated_space);
		return 1;
	}
	struct pollfd *poll_fds = (struct pollfd *) allocate_array(input.num_of_children * sizeof(struct pollfd),allocated_space);
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
	printf(TURQUOISE "[Parent] [%d] Type a number to send job to a child!\n" RESET,parent_pid);
	while(true){
		while(true){
			int input_length = read(STDIN_FILENO,line,MAX_INPUT);
			if(input_length > 0){
				//Replace the newline character with the null terminator.
				line[input_length - 1] = '\0';
				break;
			}
			int ret = poll(poll_fds,input.num_of_children,TIMEOUT);
			if(ret == -1){
				perror("Error while polling.Exit if error persists.");
				//Retry if there is an error.Can always exit from parent if needed.
				continue;
			}
			for(int i = 0;i < input.num_of_children;i++){
				bool child_sent_data = poll_fds[i].revents & POLLIN;
				if(child_sent_data){
					if(read(pipes_cf[i][0],&msg,MAX_INPUT) == -1){
						perror("Error while reading from pipe.");
						free_all(allocated_space);
						kill_children(child_pid,input.num_of_children);
						return 1;
					}
					if(strcmp(msg,"ready") == 0){
						//Remprompting whilst waiting for the child to finish.
						printf(TURQUOISE "[Parent] [%d] Type a number to send job to a child!\n"
						RESET,parent_pid);
					}
					else{
						printf(ORANGE "[Parent] [%d] Received %s from child %d.\n"
						RESET,parent_pid,msg,i);
						//Reprompt the user to send a job to a child.
						printf(TURQUOISE "[Parent] [%d] Type a number to send job to a child!\n"
						RESET,parent_pid);
					}
				}
			}
		}
		if(quitted(line)){
			//If user quits with exit end the loop.
			break;
		}
		if(strcmp(to_lower(line),"help") == 0){
			printf(TURQUOISE "[Parent] [%d] Type a number to send job to a child!\n" RESET,parent_pid);
			printf(TURQUOISE "[Parent] [%d] To exit type \"exit\".\n" RESET,parent_pid);
			continue;
		}
		int to_send = atoi(line);
		strip(line); //Needed to remove any whitespace.Easier to check for "0".
		if(to_send == 0 && strcmp(line,"0") != 0){
			printf(TURQUOISE "[Parent] [%d] Invalid input.\n" RESET,parent_pid);
			printf(TURQUOISE "[Parent] [%d] Type a number to send job to a child!\n" RESET,parent_pid);
			continue;
		}
		if(input.scheduling_process == RANDOM){
			srand(time(NULL));
			selected_child = rand() % input.num_of_children;
		}
		printf(PINK "[Parent] [%d] Assigned %d to child %d.\n" RESET,parent_pid,to_send,selected_child);
		val = to_send;
		if(write(pipes_fc[selected_child][1],&val,sizeof(int)) == -1){
			perror("Error while writing to pipe.");
			free_all(allocated_space);
			kill_children(child_pid,input.num_of_children);
			return 1;
		}
		//Reprompt the user to send a job to a child.
		printf(TURQUOISE "[Parent] [%d] Type a number to send job to a child!\n" RESET,parent_pid);
		if(input.scheduling_process == ROUND_ROBIN){
			//Select the next child in circular fashion.
			selected_child = (selected_child + 1) % input.num_of_children;
		}
	}
	close_all_pipes(pipes_cf,pipes_fc,input.num_of_children);
	kill_children(child_pid,input.num_of_children);
	printf(TURQUOISE "[Parent] [%d] All children killed!\n" RESET,parent_pid);
	free_all(allocated_space);
    return 0;
}
