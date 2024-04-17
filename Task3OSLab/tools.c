#include"tools.h"

char* choose_colour(int i){
    switch(i){
        case 0:
            return RED;
        case 1:
            return GREEN;
        case 2:
            return YELLOW;
        case 3:
            return MAGENTA;
        case 4:
            return CYAN;
        case 5:
            return WHITE;
        default:
            return RESET;
    }
}

void strip(char* str){
    int cutting_point = strcspn(str,"\t\n ");
    str[cutting_point] = '\0';
}

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
    if (num_of_children <= 0) {
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

void* allocate_array(int size,struct list* space_used){
    //Allocating memory as asked.
    void* new_space = malloc(size);
    #ifdef DEBUG
    printf("New pointer allocated at %p.\n",new_space);
    #endif
    if(new_space == NULL){
        perror("Error while allocating memory.");
        free_all(space_used);
        exit(1);
    }
    if(space_used -> ptr == NULL){
        //Initialising the first element of the list.
        space_used -> ptr = new_space;
        space_used -> next = NULL;
        return new_space;
    }
    struct list* current = space_used;
    while(current -> next != NULL){
        current = current -> next;
    }
    //Storing the new pointer by malloc in a new node.
    struct list* new_node = (struct list*) malloc(sizeof(struct list));
    new_node -> ptr = new_space;
    new_node -> next = NULL;
    //Setting the next of the last node to the new node.
    current -> next = new_node;
    return new_space;
}

void free_all(struct list* space_used){
    #ifdef DEBUG
    int size_used = 0;
    #endif
    for(int i = 0;space_used -> next != NULL;i++){
        #ifdef DEBUG
        printf(TURQUOISE "Freed ptr: %p\n" RESET,space_used -> ptr); 
        size_used += sizeof(space_used);
        #endif
        struct list* temp = space_used;
        free(temp -> ptr);
        space_used = space_used -> next;
    }
    if(space_used -> ptr != NULL){
        #ifdef DEBUG
        size_used += sizeof(space_used);
        printf(TURQUOISE "Freed ptr: %p\n" RESET,space_used -> ptr); 
        #endif
        free(space_used -> ptr);
    }
    free(space_used);
    #ifdef DEBUG
    printf("Storing ptrs needed %d bytes.\n",size_used);
    #endif
}

bool close_all_pipes(int** pipes,int** pipes2,int children){
    //Closing all the pipes that have not already been closed.
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
        str[i] = tolower(str[i]);
    }
    return str;
}

bool quitted(char* str){
    char* quit_strings[3] = {"quit","exit","q"};
    for(int i = 0;i < 3;i++){
        if(strcmp(to_lower(str),quit_strings[i]) == 0){
            return true;
        }
    }
    return false;
}

void kill_children(pid_t *child_pid,int children){
    for(int i = 0;i < children;i++){
        if(kill(child_pid[i],SIGKILL) == -1){
            printf("Error while killing child %d.\n",i);
            perror("Error :");
        }
    }
}

int set_stdin_nonblocking(){
    //Getting current flags for stdin.
    int flags = fcntl(STDIN_FILENO,F_GETFL,0);
    if(flags == -1){
        perror("Error while getting flags.");
        return -1;
    }
    //Adding the non-blocking flag.
    flags |= O_NONBLOCK;
    //Setting the new flags.
    if(fcntl(STDIN_FILENO,F_SETFL,flags) == -1){
        perror("Error while setting flags.");
        return -1;
    }
    return 0;
}
