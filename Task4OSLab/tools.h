#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<sys/select.h>
#include<unistd.h>
#include<stdio.h>
#include<ctype.h>
#include<time.h>

//Maximum length of input in characters.
#define MAX_INPUT 256

//Default host server.
#define DEFAULT_HOST "os4.iot.dslab.ds.open-cloud.xyz"
//Default port number.
#define DEFAULT_PORT 20241

//Colors for the output.
#define RESET "\033[0m"
#define RED "\033[31;1m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"

enum request{
	GET,
	PERMISSION,
	HELP,
	EXIT
};

//Packing the input into a simple struct.
struct parser {
    struct hostent* host_server; //Host server.
	int port; //Port number.
	bool debug; //Debug mode.
};

struct parser input_parser(int argc, char* args[]);
	/* Use : Parses the input given by the user and checks if it is valid.
	*/

bool exited(char* str);
	/* Use : Checks if the user wants to quit.
	   Return Value : True if the user wants to quit | False otherwise.
	*/

int set_stdin_nonblocking();
	/* Use : Sets the stdin to non-blocking mode.
	   Return Value : 0 if successful | -1 otherwise.
	*/

void print_line(char* message);
	/* Use : Prints the message in the format required for the application.
	   Return Value : None.
	*/

void print_response(char* response);
	/* Use : Prints the response from the server in the format required for the application.
	   Return Value : None.
	*/