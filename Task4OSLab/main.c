#include"tools.h"
/* All functions which are used are defined in tools.c and
   declared in tools.h.
   Please refer to tools.c for the implementation of the functions.
   For the interface of the functions refer to tools.h.
   All macros are defined in tools.h.
*/

int main(int argc,char* argv[]){
    struct parser parsed = input_parser(argc,argv);
    if(parsed.host_server == NULL){
        //If the host is not provided or invalid port is given, then the default host is used.
        parsed.host_server = gethostbyname(DEFAULT_HOST);
    }
    printf(RED "Host: %s\n" RESET,parsed.host_server -> h_name);
    if (parsed.port == -1){
        //If the port is not provided or invalid port is given, then the default port is used.
        parsed.port = DEFAULT_PORT;
    }
    printf(RED "Port: %d\n" RESET,parsed.port);
    if(parsed.debug){
        printf(RED "Debug mode is on." RESET "\n");
    }
    else{
        printf(GREEN "Debug mode is off." RESET "\n");
    }
    const int domain = AF_INET; //Ipv4 address family.
    const int type = SOCK_STREAM; // TCP connection protocol.Stream communication.
    const int protocol = 0; // OS chooses the protocol.
    int sock_fd = socket(domain,type,protocol);
    if(sock_fd == -1){
        perror("Error while creating the socket.");
        exit(1);
    }
    const struct sockaddr_in server_address = {
        .sin_family = domain,
        .sin_port = htons(parsed.port),
    };
    bcopy((char*)parsed.host_server -> h_addr_list[0],(char*)&server_address.sin_addr.s_addr,parsed.host_server -> h_length);
    if(parsed.debug){
        char* ip = inet_ntoa(server_address.sin_addr);
        printf("IP Address: %s\n",ip);
    }
    printf(BLUE "Connecting to the server..." RESET "\n");
    int connection_status = connect(sock_fd,(struct sockaddr*)&server_address,sizeof(server_address));
    if(connection_status == -1){
        perror("Error while connecting to the server.");
        exit(1);
    }
    printf(BLUE "Connected to the server." RESET "\n");
    char buffer[MAX_INPUT];
    //Setting up timeval struct for select.It holds the timeout value.
    struct timeval timeout = {
        .tv_sec = 0,
        .tv_usec = 10000
        //Timeout of 10 milliseconds.
    };
    //Setting up the file descriptor set.
    enum request req;
    fd_set read_fds;
    while(true){
        FD_ZERO(&read_fds); //Clear all file descriptors from the set.
        FD_SET(sock_fd,&read_fds); //Add the socket file descriptor to the set.
        FD_SET(STDIN_FILENO,&read_fds); //Add the standard input file descriptor to the set.
        int select_status = select(sock_fd + 1,&read_fds,NULL,NULL,&timeout);
        if(select_status == -1){
            perror("Error while selecting the file descriptors.");
            exit(1);
        }
        if(FD_ISSET(sock_fd,&read_fds)){
            int n = read(sock_fd,buffer,255);
            if(n == -1){
                perror("Error while reading from the socket.");
                exit(1);
            }
            buffer[n - 1] = '\0';
            if(parsed.debug){
                printf(RED "[DEBUG] read '%s'" RESET "\n",buffer);
            }
            if(req == GET){
                print_line(buffer);
            }
            if(req == PERMISSION){
                print_response(buffer);
            }
        }
        if(FD_ISSET(STDIN_FILENO,&read_fds)){
            int n = read(STDIN_FILENO,buffer,255);
            if(n == -1){
                perror("Error while reading from the standard input.");
                exit(1);
            }
            buffer[n-1] = '\0';
            if(exited(buffer)){
                printf("Exiting the client.\n");
                req = EXIT;
                break;
            }
            char* token = malloc(n*sizeof(char));
            strcpy(token,buffer);
            token = strtok(token," ");
            if(strcmp(token,"get") == 0){
                strcpy(buffer,"get");
                req = GET;
            }
            else if(strcmp(buffer,"help") == 0){
                printf(MAGENTA "Commands:\n");
                printf("1. get : To get a status of the measured quantities.\n");
                printf("2. N <name> <surname> <reason> : To request permission to do an activity.\n"); 
                printf("3. exit : To exit the client." RESET "\n");
                req = HELP;
            }
            else{
                req = PERMISSION;
            }
            free(token);
            if(req == GET || req == PERMISSION){
                char *message = malloc(n*sizeof(char));
                strcpy(message,buffer);
                if(parsed.debug){
                    printf(RED "[DEBUG] sent '%s'" RESET "\n",message);
                }   
                int write_status = write(sock_fd,message,n);
                if(write_status == -1){
                    perror("Error while writing to the socket.");
                    exit(1);
                }
            }
        }
    }
    close(sock_fd);
    return 0;
}