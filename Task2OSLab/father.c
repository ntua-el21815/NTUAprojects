#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<string.h>

int main(int argc,char *argv[]){
	int status;
	const int children = strlen(argv[1]);
	pid_t child_pid[children];
	pid_t father_pid = getpid();
	for(int i = 0;i < children;i++){
		int child_pid_now = fork();
		if(child_pid_now < 0){
                	perror("Error while creating child ");
                	exit(1);
		}
		if(child_pid_now == 0){
			char *argv_child[] = {"./childexec",NULL};
			execv(argv_child[0],argv_child);
			exit(0);
		}
		if(child_pid_now > 0) child_pid[i] = child_pid_now;
	}
	for(int i = 0;i < children;i++){	
		printf("[PARENT/PID=%d] Created child %d (PID=%d) and intial state %c\n"
		,father_pid,i,child_pid[i],argv[1][i]);
	}
	waitpid(-1,&status,0);
        
}
