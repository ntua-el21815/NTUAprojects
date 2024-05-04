#include"tools.h"
/* All functions which are used are defined in tools.c and
   declared in tools.h.
   Please refer to tools.c for the implementation of the functions.
   For the interface of the functions refer to tools.h.
*/

int main(int argc,char* argv[]){
    struct parser parsed = input_parser(argc,argv);
    if(parsed.host_server == NULL){
        parsed.host_server = gethostbyname(DEFAULT_HOST);
    }
    printf(RED "Host: %s\n" RESET,parsed.host_server -> h_name);
    if (parsed.port == -1){
        parsed.port = DEFAULT_PORT;
    }
    printf(RED "Port: %d\n" RESET,parsed.port);
    if(parsed.debug){
        printf(RED "Debug mode is on.\n" RESET);
        #ifndef DEBUG
        #define DEBUG
        #endif
    }
    else{
        printf(GREEN "Debug mode is off.\n" RESET);
        #ifdef DEBUG
        #undef DEBUG
        #endif
    }
    int domain = AF_INET; //Ipv4 address family.
    int type = SOCK_STREAM; // TCP connection protocol.
    int protocol = 0;
    int sock_fd = socket(domain,type,protocol);
    if(sock_fd == -1){
        perror("Error while creating the socket.");
        exit(1);
    }
    struct sockaddr_in server_address = {
        .sin_family = AF_INET,
        .sin_port = htons(parsed.port),
    };
    bcopy((char*)parsed.host_server -> h_addr_list[0],(char*)&server_address.sin_addr.s_addr,parsed.host_server -> h_length);
    #ifdef DEBUG
    char* ip = inet_ntoa(server_address.sin_addr);
    printf("IP Address: %s\n",ip);
    #endif
    printf("Connecting to the server...\n");
    int connection_status = connect(sock_fd,(struct sockaddr*)&server_address,sizeof(server_address));
    if(connection_status == -1){
        perror("Error while connecting to the server.");
        exit(1);
    }
    printf("Connected to the server.\n");
    char buffer[MAX_INPUT];
    struct timeval timeout = {
        .tv_sec = 0,
        .tv_usec = 10000
    };
    fd_set read_fds;
    FD_ZERO(&read_fds); //Clear all file descriptors from the set.
    FD_SET(sock_fd,&read_fds); //Add the socket file descriptor to the set.
    FD_SET(STDIN_FILENO,&read_fds); //Add the standard input file descriptor to the set.
    while(true){
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
            buffer[n] = '\0';
            printf("Message from the server: %s",buffer);
        }
        if(FD_ISSET(STDIN_FILENO,&read_fds)){
            int n = read(STDIN_FILENO,buffer,255);
            if(n == -1){
                perror("Error while reading from the standard input.");
                exit(1);
            }
            buffer[n] = '\0';
            printf("Message from the client: %s",buffer);
            int write_status = write(sock_fd,buffer,n);
            if(write_status == -1){
                perror("Error while writing to the socket.");
                exit(1);
            }
        }
    }
    /*
    char *message = "get";
    int message_length = strlen(message);
    int write_status = write(sock_fd,message,message_length);
    if(write_status == -1){
        perror("Error while writing to the socket.");
        exit(1);
    }
    char buffer[256];
    int n = read(sock_fd,buffer,255);
    if(n == -1){
        perror("Error while reading from the socket.");
        exit(1);
    }
    printf("Message from the server: %s",buffer);
    char *message2 = "1 Nik Agg dokimi";
    int message_length2 = strlen(message2);
    int write_status2 = write(sock_fd,message2,message_length2);
    if(write_status2 == -1){
        perror("Error while writing to the socket.");
        exit(1);
    }
    n = read(sock_fd,buffer,255);
    if(n == -1){
        perror("Error while reading from the socket.");
        exit(1);
    }
    buffer[n] = '\0';
    printf("Message from the server: %s\n",buffer);
    char *response = (char*)malloc(n*sizeof(char));
    strcpy(response,buffer);
    int response_length = strlen(response);
    int write_status3 = write(sock_fd,response,response_length);
    if(write_status3 == -1){
        perror("Error while writing to the socket.");
        exit(1);
    }
    n = read(sock_fd,buffer,255);
    if(n == -1){
        perror("Error while reading from the socket.");
        exit(1);
    }
    buffer[n] = '\0';
    printf("Message from the server: %s",buffer);
    close(sock_fd);
    */
}