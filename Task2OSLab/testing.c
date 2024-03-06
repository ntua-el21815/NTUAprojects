#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
#include<sys/wait.h>

//Global Signal Handler Variable Definitions 
int alarm_called = 0;
int user_sgn_called = 0;

void user_sgn_handler(){
	printf("%s\n","The user signal has just been received...");
	exit(1);
}

void alarm_handler(int signum,siginfo_t *info,void *context){
	alarm_called = 1;
	return;
}

int main(){
	int status;
	pid_t father_pid = getpid();
	struct sigaction action;
	action.sa_handler = user_sgn_handler;
	sigaction(SIGUSR1,&action,NULL);
	pid_t child_pid = fork();
	if(child_pid > 0){
		printf("[PARENT/PID=%d] Created child 0 (PID=%d) and initial state 't'\n",father_pid,child_pid);
		waitpid(-1,&status,0);
		exit(0);
	}
	if(child_pid == 0){
		pid_t this_pid = getpid();
		struct sigaction alarm_action;
		alarm_action.sa_sigaction = alarm_handler;
		sigaction(SIGALRM,&alarm_action,NULL);
		kill(this_pid,SIGALRM);
		for(int secs = 0;secs <= 60;secs++){
			if(alarm_called == 1){
				alarm(15);
				alarm_called = 0;
                        	printf("[ID=0/PID=%d/TIME=%d] The gates are open\n",this_pid,secs);
			}
			sleep(1);
		}
		exit(0);
	}
}
