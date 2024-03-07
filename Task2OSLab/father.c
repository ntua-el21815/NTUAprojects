#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<string.h>

int how_many_children(int argc,char *argv[]){
	if (argc != 2 || argv[1] == NULL){
		printf("Invalid Input.Use: ./a.out tftt...(any number of gates) "
		"where 't':open gate and 'f':closed gate for each child process.\n");
		return -1;
	}
	if(strspn(argv[1],"tf") != strlen(argv[1]) || strlen(argv[1]) == 0){
		//strspn returns the span of the substring made up only of t,f, 
		printf("Invalid Input.Only characters allowed are 't' for open gate and 'f' for closed.\n");
		return -1;
	}
	return strlen(argv[1]);
}

int main(int argc,char *argv[]){
	int status;
	const int children = how_many_children(argc,argv);
	if(children == -1){
		return 1;
	}
	pid_t child_pid[children];
	pid_t father_pid = getpid();
	for(int i = 0;i < children;i++){
		int child_pid_now = fork();
		if(child_pid_now < 0){
                	perror("Error while creating child ");
                	exit(1);
		}
		if(child_pid_now == 0){
			char id = (char) i; //Seems not to be working.Change ASAP.
			char *argv_child[] = {"./childexec",&id,NULL};
			execv(argv_child[0],argv_child);
		}
		if(child_pid_now > 0){
		       	printf("[PARENT/PID=%d] Created child %d (PID=%d) and intial state %c\n"
                	,father_pid,i,child_pid_now,argv[1][i]);
			child_pid[i] = child_pid_now;
		}
	}
	for(int i = 0;i < children;i++){	
		waitpid(child_pid[i],&status,0);
	}
        return 0;
}
