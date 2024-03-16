#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<string.h>
#include<stdbool.h>

/* Volatile makes sure that the compiler won't optimize the value of the flags as they may change from EXTERNAL signal.
 * sig_atomic_t An integer type which can be accessed as an atomic entity even in the presence of asynchronous           * interrupts made by signals.This means that the function call will not leave the memory in a bad state in case of
 * sudden termination. */

volatile sig_atomic_t usr1_flag = 0;
volatile sig_atomic_t usr2_flag = 0;
volatile sig_atomic_t term_flag = 0;
volatile sig_atomic_t child_flag = 0;

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

bool set_handler(int signal,void (*handler) (int)){
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
	usr1_flag = 1;
	return;
}

void usr2_handler(int sig){
        usr2_flag = 1;
        return;
}

void term_handler(int sig){
	term_flag = 1;
	return;
}

void child_handler(int sig){
	child_flag = 1;
	return;
}

int run_child(char *exec_path,int child_id,char gate_stat){
	/* Use : The function accepts the path of the executable for the child process (string),the id of the child
	   process and the status that the child's gate should have.
	   Return Values : -1 if there is an error when calling execv | 0 return value should not be reached normally
	   since execv takes control.
	 */
	char *id = malloc(sizeof(child_id));
	snprintf(id,sizeof(id),"%d",child_id);
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

int get_child_id(pid_t to_look_pid,int children,pid_t *child_pid){
	/* Use : Looks for the id of the child based on its pid.Accepts as arguments the pid to look for,the number
	   of children and the array of the pids of the children processes.
	   Return Value : -1 if the id does not correspond to the given pid | Otherwise the id of the child with the
	   given pid.
	 */
	for(int i = 0;i < children;i++){
		if(child_pid[i] == to_look_pid) return i;
	}
	return -1;
}


int main(int argc,char *argv[]){
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
	if(!set_handler(SIGUSR2,usr2_handler)){
                perror("Error while setting SIGUSR2 handler.");
                return 1;
        }
	const int children = how_many_children(argc,argv); 
	//Number of children should not change since we guarantee that n children will be running till parent exits.
	if(children == -1){
		return 1;
	}
	pid_t *child_pid = malloc(children * sizeof(pid_t));
	if(child_pid == NULL){
		perror("Failed to allocate memory.");
		return 1;
	}
	//Here the pids of the created children will be stored.
	pid_t father_pid = getpid();
	for(int i = 0;i < children;i++){
		//Creating the children one by one.
		int child_pid_now = fork();
		if(child_pid_now < 0){
                	perror("Error while creating child.");
			for(int j = 0;j < i ;j++){
				//Making sure that if parent exits abnormally,there are no zombie children left.
				kill(child_pid[j],SIGKILL);
			}
			free(child_pid);
                	exit(1);
		}
		if(child_pid_now == 0){
			//This code is executed only by the new child process.
			if(run_child("./childexec",i,argv[1][i]) == -1){
				for(int j = 0;j < i;j++){
					kill(child_pid[j],SIGKILL);
				}
				kill(father_pid,SIGKILL);
				exit(1);		
			}
		}
		if(child_pid_now > 0){		
			//This code is executed only by the parent process.		
		       	printf("[PARENT/PID=%u] Created child %d (PID=%u) and intial state '%c'\n"
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
			usr1_flag = 0;
		}
		if(usr2_flag){
                        //When SIGUSR2 is given send same siganl to all children.
                        for(int i = 0;i < children;i++){
                                kill(child_pid[i],SIGUSR2);
                        }
                        usr2_flag = 0;
                }
		if(term_flag){
			//When SIGTERM is given terminate all children and then self terminate.
			term_flag = 0;
			for(int i = 0;i < children;i++){ 
				printf("[PARENT/PID=%u] Waiting for %d children to exit\n",father_pid,children-i);
				if(kill(child_pid[i],SIGTERM) == -1){
					perror("Error while terminating child.Retrying.");
				}
				int status;
				waitpid(child_pid[i],&status,WUNTRACED);//wait for the child to terminate.
				while(!WIFEXITED(status)){
					//If signal failed send SIGKILL till child termminates.
					//SIGKILL is guaranteed to kill the process.
					//Call waitpid again to update the status.
					//This while loop ensures that the child will be killed.
					kill(child_pid[i],SIGKILL);
					waitpid(child_pid[i],&status,WUNTRACED);
				}
				printf("[PARENT/PID=%u] Child with PID=%u" 
				" terminated successfully with exit status code %d!\n",father_pid,child_pid[i]
				,WEXITSTATUS(status));
			}
			printf("[PARENT/PID=%u] All children exited, terminating as well.\n",father_pid);
			free(child_pid);
			break;
		}
		if(child_flag){
			child_flag = 0;
			int wstatus;
			pid_t affected_child_pid = waitpid(-1,&wstatus,WUNTRACED | WCONTINUED);
			int child_id = get_child_id(affected_child_pid,children,child_pid);
			if(WIFCONTINUED(wstatus)){
				//SIGCHLD is also sent after continuation but in that case we just continue.
				continue;
			}
			if(child_id == -1) {
				//Serious error if we cannot find the child id that means tha the pid we got is garbage.
				printf("Some child died and couldn't be found.\n");
				for(int i = 0;i < children;i++){
					//Making sure that if parent exits abnormally,there are no zombie children left.
					kill(child_pid[i],SIGKILL);                                                                                     }
				free(child_pid);
				exit(1);
			}
			if(WIFSTOPPED(wstatus)){
				//This block is executed if any child process stops due to outside signal.
				printf("[PARENT/PID=%u] Continued child %u (PID=%u) after stop signal\n"
				,father_pid,child_id,affected_child_pid);
				kill(affected_child_pid,SIGCONT);
			}
			if(WIFSIGNALED(wstatus) || WIFEXITED(wstatus)){
				//This block is executed if the child exits due to an outside signal or if it exits
				//normally via exit().
				pid_t new_child_pid = fork();
				if(new_child_pid == 0){
					//This code is executed only by the new child process.
					if(run_child("./childexec",child_id,argv[1][child_id]) == -1){
						for(int i = 0;i < children;i++){    
							kill(child_pid[i],SIGKILL);   
						}
						kill(father_pid,SIGKILL);
						exit(1);
					};
					
				}
				child_pid[child_id] = new_child_pid;
				printf("[PARENT/PID=%u] Child %u with PID=%u exited\n"
				,father_pid,child_id,affected_child_pid);
				printf("[PARENT/PID=%u] Created new child for gate %u (PID=%u) and intial state '%c'\n"
				,father_pid,child_id,new_child_pid,argv[1][child_id]);
			}
		}
	}
        return 0;
}
