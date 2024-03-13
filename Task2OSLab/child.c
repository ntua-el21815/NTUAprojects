#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<string.h>
#include<stdbool.h>

#define OPEN "open"
#define CLOSED "closed"

volatile static int alarm_timer = 0;
volatile static sig_atomic_t usr1_flag = false;
volatile static sig_atomic_t usr2_flag = false;
//Very important : Volatile lets the compiler know that the variable may change due to an outside signal
// (SIGALRM,SIGUSR1)
//If variable is not declared volatile then the compiler may assume that its value can only change from insturctions
//withing this program.

void term_handler(int sig){
	exit(0);
}
void continue_handler(int sig){
	return;
}

void alarm_handler(int sig){
	alarm_timer ++; //Equivalent to seconds elapsed as we set alarm every second.
	return;
}

void usr1_handler(int sig){
	usr1_flag = true;
	return;
}

void usr2_handler(int sig){
	usr2_flag = true;
	return;
}

sig_atomic_t set_handler(int signal,void (*handler) (int)){
	//Initialise struct to empty.Otherwise garbage values in fields(sigaction,mask,flags,restorer).
	//That would produce undefined behaviour :(
	struct sigaction action = {};
        action.sa_handler = handler;
        if(sigaction(signal,&action,NULL) == -1){
		return false;	
	}
	return true;
}



char* status_reader(char status){
	//Simple function that translates 't' to open and 'f' to closed.
	return (status == 't') ? OPEN : CLOSED;
}

int main(int argc,char *argv[]){
	if(!set_handler(SIGCONT,continue_handler)){
                perror("Failed on setting SIGCONT handler");
                return 1;
        }
	if(!set_handler(SIGALRM,alarm_handler)){
                perror("Failed on setting SIGALARM handler");
                return 1;
        }
        if(!set_handler(SIGUSR1,usr1_handler)){
                perror("Failed on setting SIGUSR1 handler");
                return 1;
        }
        if(!set_handler(SIGUSR2,usr2_handler)){
                perror("Failed on setting SIGUSR2 handler");
                return 1;
        }
	if(!set_handler(SIGTERM,term_handler)){
                perror("Failed on setting SIGALRM handler");
                return 1;
        }
	char* child_id = argv[1]; 
	//The id of the child is passed as the first argument.
	//The reason it is a char : It was embedded into the argv[1] string.
	pid_t this_pid = getpid();
	char *gate_status = status_reader(argv[2][0]);
	while(true){
		if(alarm_timer % 15 == 0){
			printf("[ID=%s/PID=%u/TIME=%d] The gates are %s!\n"
			,child_id,this_pid,alarm_timer,gate_status);
		}
		if(usr1_flag){
			printf("[ID=%s/PID=%du/TIME=%d] The gates are %s!\n"
                        ,child_id,this_pid,alarm_timer,gate_status);
			usr1_flag = false;
		}
		if(usr2_flag){
			gate_status = (gate_status == OPEN) ? CLOSED : OPEN;
			usr2_flag = false;
		}
		alarm(1);
		pause();//Pausing the program till next alarm.
	}
	return 0;
}
