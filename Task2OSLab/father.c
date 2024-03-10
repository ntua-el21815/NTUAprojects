#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<string.h>
#include<stdbool.h>

volatile static sig_atomic_t usr1_flag = false;
volatile static sig_atomic_t term_flag = false;
volatile static sig_atomic_t child_flag = false;

int how_many_children(int argc,char *argv[]){
	/*Use : Error handling for user input.Checks if argc and argv are as expected.
	  Return Values : -1 if input is invalid | If input is valid the number of children (>0) is returned.
	 */
	if (argc != 2 || argv[1] == NULL){
		//If more or less than one argument are given to the program we reject them.
		printf("Invalid Input.Use: %s tftt...(any number of gates) "
		"where 't':open gate and 'f':closed gate for each child process.\n",argv[0]);
		return -1;
	}
	if(strspn(argv[1],"tf") != strlen(argv[1]) || strlen(argv[1]) == 0){
		//strspn returns the span of the substring made up only of t,f.
		//If the user gives some other character (e.g 'e' or '') we reject it.
		printf("Invalid Input.Only characters allowed are 't' for open gate and 'f' for closed.\n");
		return -1;
	}
	return strlen(argv[1]); //Number of children is the length of the given string.
}

sig_atomic_t set_handler(int signal,void (*handler) (int)){
	/* Use : Sets handler function for the given signal.Signal should be any of the available macros (e.g SIGUSR1).
	   Return Values : false if setting the handler fails otherwise true. 
	 */
        //Initialise struct to empty.Otherwise garbage values in fields(sigaction,mask,flags,restorer).
        //That would produce undefined behaviour :(
        struct sigaction action = {};
        action.sa_handler = handler;
        if(sigaction(signal,&action,NULL) == -1){
                return false;
        }
        return true;
}

void usr1_handler(int sig){
	usr1_flag = true;
	return;
}

void term_handler(int sig){
	term_flag = true;
	return;
}

void child_handler(int sig){
	child_flag = true;
	return;
}

int run_child(char *exec_path,int child_id,char gate_stat){
	/* Use : The function accepts the path of the executable for the child process (string),the id of the child
	   process and the status that the child's gate should have.
	   Return Values : -1 if there is an error when calling execv | 0 return value should not be reached normally
	   since execv takes control.
	 */
	char id[2];
	snprintf(id,2,"%d",child_id);
	char gate_status[2];
	snprintf(gate_status,2,"%c",gate_stat);
	//Child needs to know its id and its gate status which were given to the parent.
        //We pass those as arguments into its *argv[] pointer array.
	char *argv_child[] = {exec_path,id,gate_status,NULL};
	if(execv(argv_child[0],argv_child) == -1){
		perror("Error while initiating child.");
		return -1;
 	}
	return 0;
}

int get_child_id(int pid,int children,int *child_pid){
	/* Use : Looks for the id of the child based on its pid.Accepts as arguments the pid to look for,the number
	   of children and the array of the pids of the children processes.
	   Return Value : -1 if the id does not correspond to the given pid | Otherwise the id of the child with the
	   given pid.
	 */
	for(int i = 0;i < children;i++){
		if(child_pid[i] == pid) return i;
	}
	return -1;
}

int main(int argc,char *argv[]){
	int status; //To access any child's status.
	if(!set_handler(SIGUSR1,usr1_handler)){
		perror("Error while setting SIGUSR1 handler.");
		return 1;
	}
	if(!set_handler(SIGTERM,term_handler)){
                perror("Error while setting SIGTERM handler.");
		return 1;
        }
	if(!set_handler(SIGCHLD,child_handler)){
                perror("Error while setting SIGCHLD handler.");
		return 1;
        }
	const int children = how_many_children(argc,argv);
	if(children == -1){
		return 1;
	}
	pid_t *child_pid = malloc(children * sizeof(pid_t));
	//Here the pids of the created children will be stored.
	//Static decalaration is not mandatory but initialises to 0 which prevents garbage values in case of error.
	pid_t father_pid = getpid();
	for(int i = 0;i < children;i++){
		int child_pid_now = fork();
		if(child_pid_now < 0){
                	perror("Error while creating child.");
                	return 1;
		}
		if(child_pid_now == 0){
			//This code is executed only by the new child process.
			if(run_child("./childexec",i,argv[1][i]) == -1){
				return 1;		
			}
		}
		if(child_pid_now > 0){
			//This code is executed only by the parent process.
		       	printf("[PARENT/PID=%d] Created child %d (PID=%d) and intial state '%c'\n"
                	,father_pid,i,child_pid_now,argv[1][i]);
			child_pid[i] = child_pid_now;
		}
	}
	while(true){
		if(usr1_flag){
			//When SIGUSR1 is given send same siganl to all children.
			for(int i = 0;i < children;i++){ 
				kill(child_pid[i],SIGUSR1);
			}
			usr1_flag = false;
		}
		if(term_flag){
			//When SIGTERM is given terminate all children and then self terminate.
			for(int i = 0;i < children;i++){ 
				kill(child_pid[i],SIGTERM);
			}
			term_flag = false;
			waitpid(-1,&status,0); //Wait for all the children to terminate before self termination.
			return 0;
		}
		if(child_flag){
			pid_t child_terminated_pid = wait(&status); //Wait here retuns the pid of the killed child.
			int child_id = get_child_id(child_terminated_pid,children,child_pid);
			if(child_id == -1) {
				//Serious error if we cannot find the child id that means tha the pid we got is garbage.
				printf("Some child died and couldn't be found.\n");
				return 1;
			}
			pid_t new_child_pid = fork();
			if(new_child_pid == 0){
				//This code is executed only by the new child process.
				run_child("./childexec",child_id,argv[1][child_id]);
			}
			child_pid[child_id] = new_child_pid;
			printf("[PARENT/PID=%d] Child %d with PID=%d exited\n"
			,father_pid,child_id,child_terminated_pid);
			printf("[PARENT/PID=%d] Created new child for gate %d (PID=%d) and intial state '%c'\n"
			,father_pid,child_id,new_child_pid,argv[1][child_id]);
		}
		/*
		for(int i = 0;i < children;i++){
			//Constantly check the status of each child.In case one child exits print the Exit code.
			int status = 0;
			if(status = waitpid(child_pid[i],&status,0) <= 0){
				printf("Exit Code: %d\n",status);
				return 1;
			}
		}
		*/
	}
        return 0;
}
