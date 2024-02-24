#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>

int file_exists(char *file_name){
        struct stat info; //We don't need any other info about the file so we ignore it.
        return stat(file_name,&info);
}

int main(int argc,char *argv[]) {
	int status;

	//If there is not one file name then abort and inform user.
	if(argc != 2){
                printf("Usage ./Lab1.out filename\n");
                return 1;
       	}

	//If user asks for --help then help them.
        if(strcmp(argv[1],"--help") == 0){
                printf("Usage: ./Lab1.out filename\n");
                return 0;
        }
	
	char *file_name = argv[1];

	//If file already exists abort.
	if(file_exists(file_name) == 0){
                printf("Error: %s already exists\n",file_name);
                return 1;
        }

	pid_t child_id = fork();//Create child process.

        if(child_id < 0){
                //If negative value is returned the creation of child process was unsuccesful.
                perror("Unsuccesful");
		return 1;
		
        }

	if(child_id == 0){
		//In that case the child process will run the following code.
		pid_t this_id = getpid();//id of the child process
		pid_t parent_id = getppid();//id of the parent process
		const int this_pid_length = sizeof(this_id);
		const int parent_pid_length = sizeof(parent_id);
		int max_string_length = this_pid_length + parent_pid_length + strlen("[CHILD] getpid()=,getppid()=\n");
        	char *text_to_write = (char*)malloc(max_string_length);
		if(text_to_write == NULL){
			perror("Not enough memory");
			return 1;
		}
		snprintf(text_to_write,max_string_length,"[CHILD] getpid()=%d,getppid()=%d\n",this_id,parent_id);
		int fd = open(file_name, O_CREAT |O_APPEND | O_WRONLY,0644);
        	if (fd==-1){
                	perror("Open Error");
			free(text_to_write);
                	return 1;
       	 	}
        	if(write(fd,text_to_write,strlen(text_to_write))<strlen(text_to_write)){
                	perror("Write Error");
			free(text_to_write);
                	return 1;
        	}
		if(close(fd) == -1){
			perror("Failure to close file");
			free(text_to_write);
			return 1;
		}
		free(text_to_write);
		exit(0);
	}
	else{
		wait(&status);
		pid_t this_id = getpid();//id of the parent process
		pid_t parent_id = getppid();//id of the parent's parent process
		const int this_pid_length = sizeof(this_id);
		const int parent_pid_length = sizeof(parent_id);
		int max_string_length = this_pid_length + parent_pid_length + strlen("[CHILD] getpid()=,getppid()=\n");
        	char *text_to_write = (char*) malloc(max_string_length);
		if(text_to_write == NULL){
                        perror("Not enough memory");
                        return 1;
                }
        	snprintf(text_to_write,max_string_length,"[PARENT] getpid()=%d,getppid()=%d\n",this_id,parent_id);
		int fd = open(file_name, O_CREAT |O_APPEND | O_WRONLY,0644);
        	if (fd==-1){
                	perror("Open Error");
			free(text_to_write);
                	return 1;
        	}
            	if(write(fd,text_to_write,strlen(text_to_write))<strlen(text_to_write)){
                        perror("write Error");
			free(text_to_write);
                        return 1;
                }
                if(close(fd) == -1){
                        perror("Failure to close file");
			free(text_to_write);
			return 1;
                }
		free(text_to_write);
		exit(0);
	}
	return 0;
}

