#include"tools.h"

struct parser input_parser(int argc, char* args[]) {
    if (argc < 2) {
        printf("Did not provide number of children. Usage: %s <nChildren> [--random] [--round-robin].\n", args[0]);
        return (struct parser){-1, ROUND_ROBIN};
    }
    if (argc > 3) {
        printf("Too many parameters given. Usage: %s <nChildren> [--random] [--round-robin].\n", args[0]);
        return (struct parser){-1, ROUND_ROBIN};
    }
    int num_of_children = atoi(args[1]);
    if (num_of_children == 0) {
        printf("Number of children not valid. Usage: %s <nChildren> [--random] [--round-robin].\n", args[0]);
        return (struct parser){-1, ROUND_ROBIN};
    }
    enum schedule scheduling_process = ROUND_ROBIN;
    if (argc == 3) {
		//Checks for the existence of flag that changes the scheduling process.
        if (strcmp(args[2], "--random") == 0) {
            scheduling_process = RANDOM;
        }
        else if (strcmp(args[2], "--round-robin") == 0) {
            scheduling_process = ROUND_ROBIN;
        }
        else {
            printf("Wrong flag given. Usage: %s <nChildren> [--random] [--round-robin].\n", args[0]);
            return (struct parser){-1, ROUND_ROBIN};
        }
    }
    return (struct parser){num_of_children, scheduling_process};
}

int run_child(char *exec_path,int child_id,char gate_stat){
	char *argv_child[] = {exec_path,NULL};
	if(execv(argv_child[0],argv_child) == -1){
		perror("Error while initiating child.");
		return -1;
 	}
	return 0;
}

int get_child_id(pid_t to_look_pid,int children,pid_t *child_pid){
	for(int i = 0;i < children;i++){
		if(child_pid[i] == to_look_pid) return i;
	}
	return -1;
}

void* allocate_array(int size,void** space_used){
    void *array = malloc(size);
    space_used = realloc(space_used,sizeof(space_used) + sizeof (array));
    if(array == NULL){
        perror("Error while allocating memory.");
        free_all(space_used);
        exit(1);
    }
    return array;
}

void free_all(void **space_used){
    for(int i = 0;space_used[i] != NULL;i++){
        free(space_used[i]);
    }
    free(space_used);
}

bool close_all_pipes(int** pipes,int** pipes2,int children){
    for(int i = 0;i < children;i++){
        if(close(pipes[i][0]) == -1 || close(pipes2[i][1]) == -1){
            perror("Error while closing pipes.");
            return false;
        }
    }
    return true;
}

char* to_lower(char* str){
    for(int i = 0;str[i] != '\0';i++){
        if(str[i] >= 'A' && str[i] <= 'Z'){
            str[i] = str[i] + 32;
        }
    }
    return str;
}

bool quit(char* str){
    char* quit_strings[3] = {"quit","exit","q"};
    for(int i = 0;i < 3;i++){
        if(strcmp(to_lower(str),quit_strings[i]) == 0){
            return true;
        }
    }
    return false;
}

bool kill_children(pid_t *child_pid,int children){
    for(int i = 0;i < children;i++){
        if(kill(child_pid[i],SIGKILL) == -1){
            perror("Error while killing children.");
            return false;
        }
    }
    return true;
}