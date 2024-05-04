#include"tools.h"

struct parser input_parser(int argc, char* args[]) {
    struct parser parsed = {
        .host_server = NULL,
        .port = -1,
        .debug = false
    };
    int i = 1;
    while(i < argc){
        if(strcmp(args[i],"--host") == 0){
            if((i + 1) < argc){
                int length = strlen(args[i + 1]);
                char* cand_host = (char*) malloc(length + 1);
                strcpy(cand_host,args[i + 1]);
                struct hostent* host = gethostbyname(cand_host);
                if(host == NULL){
                    perror("Error while getting host.Using default instead.");
                    free(cand_host);
                    return parsed;
                }
                parsed.host_server = host;
                i += 2;
                free(cand_host);
            }
            else{
                printf("Argument missing for %s.\n",args[i]);
                parsed.host_server = NULL;
                return parsed;
            }
        }
        else if(strcmp(args[i],"--port") == 0){
            if((i + 1) < argc){
                int cand_port = atoi(args[i + 1]);
                if(cand_port == 0){
                    printf("Invalid port number %s.Using default instead.\n",args[i + 1]);
                    parsed.port = -1;
                    return parsed;
                }
                parsed.port = cand_port;
                i += 2;
            }
            else{
                printf("Argument missing for %s.Using default instead.\n",args[i]);
                parsed.port = -1;
                return parsed;
            }
        }
        else if(strcmp(args[i],"--debug") == 0){
            parsed.debug = true;
            i++;
        }
        else{
            printf("Invalid argument %s.\n",args[i]);
            exit(1);
        }
    }
    return parsed;
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

char* to_lower(char* str){
    for(int i = 0;str[i] != '\0';i++){
        str[i] = tolower(str[i]);
    }
    return str;
}

bool exited(char* str){
    char* quit_string = "exit";
    if (strcmp(to_lower(str),quit_string) == 0){
        return true;
    }
    return false;
}