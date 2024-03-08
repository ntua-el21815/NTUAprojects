#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<string.h>
#include<stdbool.h>

int how_many_children(int argc,char *argv[]){
	//Error handling for user input is done here.
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

int main(int argc,char *argv[]){
	int status; //To access any child's status.
	const int children = how_many_children(argc,argv);
	if(children == -1){
		return 1;
	}
	static pid_t child_pid[children];//Here the pids of the created children will be stored.
	//Static decalaration is not mandatory but initialises to 0 which prevents garbage values in case of error.
	pid_t father_pid = getpid();
	for(int i = 0;i < children;i++){
		int child_pid_now = fork();
		if(child_pid_now < 0){
                	perror("Error while creating child ");
                	exit(1);
		}
		if(child_pid_now == 0){
			//Child needs to know its id and its gate status which were given to the parent.
			//We pass those as arguments into *argv[].
			char id[2];
			snprintf(id,2,"%d",i);
			char gate_status[2];
			snprintf(gate_status,2,"%c",argv[1][i]);
			char *argv_child[] = {"./childexec",id,gate_status,NULL};
			execv(argv_child[0],argv_child);
		}
		if(child_pid_now > 0){
		       	printf("[PARENT/PID=%d] Created child %d (PID=%d) and intial state %c\n"
                	,father_pid,i,child_pid_now,argv[1][i]);
			child_pid[i] = child_pid_now;
		}
	}
	while(true){
		for(int i = 0;i < children;i++){
			//Constantly check the status of each child.In case one child exits print the Exit code.
			int status = 0;
			if(status = waitpid(child_pid[i],&status,0) <= 0){
				printf("Exit Code: %d\n",status);
				return 1;
			}
		}
	};
        return 0;
}
