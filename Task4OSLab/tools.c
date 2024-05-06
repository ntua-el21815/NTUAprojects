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

bool exited(char* str){
    if (strcmp(str,"exit") == 0){
        return true;
    }
    return false;
}

void print_line(char* message){
    printf("---------------------------\n");
    printf(GREEN "Latest Event:\n");
    printf("interval(%c)\n",message[0]);
    const int ll_size = 4;
    char* light_level = malloc(ll_size*sizeof(char));
    for(int i = 2;i < 5;i++){
        light_level[i-2] = message[i];
    }
    light_level[ll_size -1] = '\0';
    const int temp_size = 5;
    char* temperature = malloc(temp_size*sizeof(char));
    for(int i = 6;i < 10;i++){
        temperature[i-6] = message[i];
    }
    temperature[temp_size -1] = '\0';
    const int unix_time_size = 11;
    char* unix_time = malloc(unix_time_size*sizeof(char));
    for(int i = 11;i < 21;i++){
        unix_time[i-11] = message[i];
    }
    unix_time[unix_time_size -1] = '\0';
    double temperture_int = (double)atoi(temperature) / 100;
    //Only printing the first 2 decimal places.
    printf("Temperature is: %.2f\n",temperture_int);
    printf("Light Level is: %s\n",light_level);
    //Using localtime to convert the unix time to human readable time.
    time_t unix_time_int = atoi(unix_time);
    struct tm* human_time = localtime(&unix_time_int);
    char* time_to_print = asctime(human_time);
    time_to_print[strlen(time_to_print) - 1] = '\0';
    printf("Timestamp is: %s" RESET "\n",time_to_print);
    free(light_level);
    free(temperature);
    free(unix_time);
    return;
}

void print_response(char* message){
    if(strcmp(message,"try again") == 0){
        printf(RED "Try again.Wrong Command." RESET "\n");
        return;
    }
    char* first_word = malloc(4*sizeof(char));
    for(int i = 0;i < 3;i++){
        first_word[i] = message[i];
    }
    first_word[3] = '\0';
    if((strcmp(first_word,"get") == 0) && strlen(message) > 3){
        printf(RED "Try again.Wrong Command." RESET "\n");
        free(first_word);
        return;
    }
    if(strcmp(first_word,"ack") == 0){
        printf(GREEN "Response: '%s'" RESET "\n",message);
        free(first_word);
        return;
    }
    else{
        printf(GREEN "Send verification code: '%s'" RESET "\n",message);
        free(first_word);
        return;
    }
    free(first_word);
    return;
}
