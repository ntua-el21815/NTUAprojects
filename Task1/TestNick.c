#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc,char* argv[]){

if (argc<2 || argc == 1){
	printf("Usage: ./a.out filename");
 	return 1;
}

int status;
pid_t child;
int fd = open(argv[1], O_CREAT | O_APPEND | O_WRONLY , 0644);
child = fork(); //δημιουργει νεο παιδι αντιγραφο,κληρονομει ενα αντιγραφο των μεταβλητων του πατερα με τις τιμες που εχουν εκεινη την στιγμη
if(child<0){
// error
}
if(child == 0){
	char buf[100];
	sprintf(buf, "[CHILD] getpid()=%d,getppid()=%d\n",getpid(),getppid());
	if(fd == -1){
		perror("open");//error when opening the file
	return 1;
}
if (write(fd, buf, strlen(buf)) < strlen(buf)) {
	perror("write");
	return 1;
}// error when writing in the file
close(fd);
exit(0);//τον βρογχο αυτον τον εκτελει η διεργασια παιδι(θελω να γραψει σε αρχειο) 
}

else{
	char buf2[100];
	sprintf(buf2,"[PARENT] getpid()=%d,getppid()=%d\n",getpid(),getppid());
	if (fd == -1){
		perror("open parent");
		return 1;
}
if (write(fd, buf2, strlen(buf2)) < strlen(buf2)) {
	perror("write parent");
	return 1;
}
close(fd);
wait(&status);
exit(0);//τον βρογχο αυτον τον εκτελει ο πατερας, κανει exit αφοτου εχει τελειωσει και το παιδι
}
}
