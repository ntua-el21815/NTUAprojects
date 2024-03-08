#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<string.h>
#include<stdbool.h>

volatile static int alarm_timer = 0;
//Very important : Volatile lets the compiler know that the variable may change due to an outside signal (SIGALRM)
//If variable is not declared volatile then the compiler may assume that its value can only change from insturctions
//withing this program.

void alarm_handler(int sig){
	alarm_timer ++; //Equivalent to seconds elapsed as we set alarm every second.
	return;
}

void set_alarm_handler(void){
	//Initialise struct to empty.Otherwise garbage values in fields(sigaction,mask,flags,restorer).
	//That would produce undefined behaviour :(
	struct sigaction alarm_action = {};
        alarm_action.sa_handler = alarm_handler;
        sigaction(SIGALRM,&alarm_action,NULL);
	return;
}

char* status_reader(char status){
	return (status == 't') ? "open" : "closed";
}

int main(int argc,char *argv[]){
	char child_id = argv[1][0]; 
	//The id of the child is passed as the first argument.
	//The reason it is a char : It was embedded into the argv[1] string.
	pid_t this_pid = getpid();
	set_alarm_handler();
	while(true){
		if(alarm_timer % 15 == 0){
			printf("[ID=%c/PID=%d/TIME=%d] The gates are %c!\n",child_id,this_pid,alarm_timer,argv[2][0]);
		}
		alarm(1);
		pause();//Pausing the program till next alarm.
	}
	exit(0);
}
