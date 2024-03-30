#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<string.h>
#include<stdbool.h>

enum schedule {RANDOM, ROUND_ROBIN};

struct parser {
    int num_of_children;
    enum schedule scheduling_process;
};

struct parser input_parser(int argc, char* args[]) {
	/* Use : Parses the input given by the user and checks if it is valid.
	   Return Values : If the input is invalid the function returns a struct with -1 as the number of children.
	   Otherwise it returns a struct with the number of children and the scheduling process.
	*/
    if (argc < 2) {
        printf("Did not provide number of children. Usage: %s <nChildren> [--random] [--round-robin].\n", args[0]);
        return (struct parser){-1, ROUND_ROBIN};
    }
    if (argc > 3) {
        printf("Too many parameters given. Usage: %s <nChildren> [--random] [--round-robin].\n", args[0]);
        return (struct parser){-1, ROUND_ROBIN};
    }
    int num_of_children = atoi(args[1]);
    if (num_of_children == 0) {
        printf("Number of children not valid. Usage: %s <nChildren> [--random] [--round-robin].\n", args[0]);
        return (struct parser){-1, ROUND_ROBIN};
    }
    enum schedule scheduling_process = ROUND_ROBIN;
    if (argc == 3) {
		//Checks for the existence of flag that changes the scheduling process.
        if (strcmp(args[2], "--random") == 0) {
            scheduling_process = RANDOM;
        }
        else if (strcmp(args[2], "--round-robin") == 0) {
            scheduling_process = ROUND_ROBIN;
        }
        else {
            printf("Wrong flag given. Usage: %s <nChildren> [--random] [--round-robin].\n", args[0]);
            return (struct parser){-1, ROUND_ROBIN};
        }
    }
    return (struct parser){num_of_children, scheduling_process};
}

int run_child(char *exec_path,int child_id,char gate_stat){
	/* Use : The function accepts the path of the executable for the child process (string),the id of the child
	   process and the status that the child's gate should have.
	   Return Values : -1 if there is an error when calling execv | 0 return value should not be reached normally
	   since execv takes control.
	 */
	char *argv_child[] = {exec_path,NULL};
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
	struct parser input = input_parser(argc,argv);
	if(input.num_of_children == -1){
		return 1;
	}
	pid_t *child_pid = malloc(input.num_of_children * sizeof(pid_t));
	//Here the pids of the created children will be stored.
	if(child_pid == NULL){
		perror("Failed to allocate memory.");
		return 1;
	}
	pid_t parent_pid = getpid();

	printf("[PARENT/PID=%u] Parent process started.\n"
	"Number of children to create: %d, scheduling process: %s.\n",
	parent_pid,input.num_of_children,input.scheduling_process == RANDOM ? "random" : "round-robin");

	for(int i = 0;i < input.num_of_children;i++){
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
				kill(parent_pid,SIGKILL);
				exit(1);		
			}
		}
		if(child_pid_now > 0){		
			//This code is executed only by the parent process.		
		       	printf("[PARENT/PID=%u] Created child %d (PID=%u).\n"
                	,parent_pid,i,child_pid_now);
			child_pid[i] = child_pid_now;
		}
	}
        return 0;
}
