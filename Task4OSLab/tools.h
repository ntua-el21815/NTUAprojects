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


//Packing the input into a simple struct.
struct parser {
    struct hostent* host_server; //Host server.
	int port; //Port number.
	bool debug; //Debug mode.
};

struct list {
	void* ptr;
	struct list* next;
};

void strip(char* str);
	/* Use : Strips the string from any whitespace.
	   Return Value : None.
	*/

struct parser input_parser(int argc, char* args[]);
	/* Use : Parses the input given by the user and checks if it is valid.
	*/


void* allocate_array(int size,struct list* allocated_space);
	/* Use : Allocates memory for an array of size 'size'.
	   Return Value : The pointer to the allocated memory.
	   Error Handling is done inside the function.
	*/

void free_all(struct list* space_used);
	/* Use : Frees all the memory allocated using the allocate_array function.
	   Return Value : None.
	*/

char* to_lower(char* str);
	/* Use : Converts a string to lowercase.
	   Return Value : The string in lowercase.
	*/

bool exited(char* str);
	/* Use : Checks if the user wants to quit.
	   Return Value : True if the user wants to quit | False otherwise.
	*/

int set_stdin_nonblocking();
	/* Use : Sets the stdin to non-blocking mode.
	   Return Value : 0 if successful | -1 otherwise.
	*/