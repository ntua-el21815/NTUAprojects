#include"tools.h"

int main(int argc,char *argv[]){
	//allocated_space array is used to store all pointers to dynamically allocated memory.
	void** allocated_space = malloc(0);  
	//Store the input from the user into a parser struct.Defined in tools.h.
	struct parser input = input_parser(argc,argv);
	int val;
	//In child_pid the pids of the created children will be stored.
	pid_t *child_pid = allocate_array(input.num_of_children * sizeof(pid_t),allocated_space);
	pid_t parent_pid = getpid();
        //Create one pipe for each child.
    int** pipes = allocate_array(input.num_of_children * sizeof(int*),allocated_space);
	if(input.num_of_children == -1){
		//Parser failed.See definition of input_parser.
		free_all(allocated_space);
		return 1;
	}
	for(int i = 0;i < input.num_of_children;i++){
		pipes[i] = allocate_array(2 * sizeof(int),allocated_space);
	}
	for(int i = 0;i < input.num_of_children;i++){
		//Creating one pipe for each child.
		if(pipe(pipes[i]) == -1){
			perror("Failed to create pipe.");
			free_all(allocated_space);
			return 1;
		}
	}
	printf("[Parent] [%d] Parent process started.\n"
	"Number of children to create: %d, scheduling process: %s.\n",
	parent_pid,input.num_of_children,
	input.scheduling_process == RANDOM ? "random" : "round-robin");
	for(int i = 0;i < input.num_of_children;i++){
		//Creating the children one by one.
		int child_pid_now = fork();
		if(child_pid_now < 0){
			perror("Error while creating child.");
			for(int j = 0;j < i ;j++){
				//Making sure that if parent exits abnormally,there are no zombie children left.
				kill(child_pid[j],SIGKILL);
			}
			free_all(allocated_space);
            exit(1);
		}
		if(child_pid_now == 0){
			//This code is executed only by the new child process.
			/*if(run_child("./childexec",i,argv[1][i]) == -1){
				for(int j = 0;j < i;j++){
					kill(child_pid[j],SIGKILL);
				}
				kill(parent_pid,SIGKILL);
				exit(1);		
			}*/
			while(true){
				int gIndex = i;
				if(read(pipes[i][0],&val,sizeof(int)) == -1){
					perror("Error while reading from pipe.");
					close(pipes[i][0]);
					close(pipes[i][1]);
					exit(1);
				}
				close(pipes[i][0]);
				printf("[Child %d] [%d] Child received %d!\n", gIndex, getpid(), val);
				val --;
				sleep(1);
				write(pipes[i][1],&val,sizeof(int));
				close(pipes[i][1]);
				printf("[Child %d] [%d] Child Finished hard work, writing back %d\n",gIndex,getpid(),val);
			}
			exit(0);
		}
		if(child_pid_now > 0){		
			//This code is executed only by the parent process.		
			printf("[Parent] [%d] Created child %d (PID=%u).\n"
			,parent_pid,i,child_pid_now);
			child_pid[i] = child_pid_now;
			
		}
	}
	struct pollfd *poll_fds = allocate_array(input.num_of_children * sizeof(struct pollfd),allocated_space);
	for(int i = 0;i < input.num_of_children;i++){
		poll_fds[i].fd = pipes[i][0];
		poll_fds[i].events = POLLIN;
	}
	printf("[Parent] [%d] Type a number to send job to a child!\n",parent_pid);
	char line[100];
	while(fgets(line,sizeof(line) + 1,stdin) != NULL){
		if(line[0] == '\n'){
			continue;
		}
		break;
	}
	int to_send = atoi(line);
	if(to_send == 0){
		printf("Invalid input!\n");
	}
	val = to_send;
	srand(time(NULL));
	int selected_child = rand() % input.num_of_children;
	write(pipes[selected_child][1],&val,sizeof(int));
	close(pipes[selected_child][1]);
	//Poll for the child that has finished its job.
	int timeout = 5000; // Timeout in milliseconds
	int result = poll(poll_fds, input.num_of_children, timeout);
	if (result == -1) {
		perror("Error while polling");
		free_all(allocated_space);
		return 1;
	} else if (result == 0) {
		printf("[Parent] [%d] Timeout occurred. No child finished its job.\n", parent_pid);
	} else {
		for (int i = 0; i < input.num_of_children; i++) {
			if (poll_fds[i].revents & POLLIN) {
				printf("[Parent] [%d] Child %d (PID=%u) has finished its job.\n", parent_pid, i, child_pid[i]);
				// Read the value sent by the child
				read(pipes[i][0], &val, sizeof(int));
				break;
			}
		}
	}
	close(pipes[selected_child][0]);
	printf("[Parent] [%d] Received %d from child %d.\n",parent_pid,val,selected_child);
	//Kill all children.
	for(int i = 0;i < input.num_of_children;i++){
		kill(child_pid[i],SIGTERM);
	}
	free_all(allocated_space);
    return 0;
}
