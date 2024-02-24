#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>

int main(){
	char *A[7];
	printf("%lu\n",A);
	printf("%lu\n",&A[0]);
}
