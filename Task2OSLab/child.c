#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<string.h>

int main(){
	pid_t this_pid = getpid();
	printf("I am the child and my pid is %d\n",this_pid);
	return 0;
}
