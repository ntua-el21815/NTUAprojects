#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<string.h>

volatile static int alarm_flag = 0;

void alarm_handler(int sig){
	alarm_flag = 1;
}

int main(int argc,char *argv[]){
	int child_id = (int) *argv[1]; //Probably ot working well.
	pid_t this_pid = getpid();
	int secs = 0;
	struct sigaction alarm_action;
	alarm_action.sa_handler = alarm_handler;
	sigaction(SIGALRM,&alarm_action,NULL);
	kill(this_pid,SIGALRM);
	while(1){
		if(alarm_flag == 1){
			printf("I am the child %d and my pid is %d.Seconds Elapsed %d\n",child_id,this_pid,secs);
			alarm_flag = 0;
			alarm(15);
		}
		else{
			sleep(1);
			secs++;
		}
	}
	exit(0);
}
