#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>
#include<poll.h>
#include<fcntl.h>

//Colors for the output.
#define RESET "\033[0m"
#define RED "\033[31;1m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define GRAY "\033[38;1m"
#define ORANGE "\033[38;5;208m"
#define PINK "\033[38;5;13m"
#define TURQUOISE "\033[38;5;45m"

char* choose_colour(int i);
	/* Use : Chooses a colour based on the id of the child.
	   Return Value : The colour that corresponds to the id of the child.
	*/

//Maximum expected input and message size.
#define MAX_INPUT 100

//Just an enumeration of the scheduling processes.
enum schedule {RANDOM, ROUND_ROBIN};

//Packing the input into a simple struct.
struct parser {
    int num_of_children;
    enum schedule scheduling_process;
};

struct parser input_parser(int argc, char* args[]);
	/* Use : Parses the input given by the user and checks if it is valid.
	   Return Values : If the input is invalid the function returns a struct with -1 as the number of children.
	   Otherwise it returns a struct with the number of children and the scheduling process.
	*/

int run_child(char *exec_path,int child_id,char gate_stat);
	/* Use : The function accepts the path of the executable for the child process (string),the id of the child
	   process and the status that the child's gate should have.
	   Return Values : -1 if there is an error when calling execv | 0 return value should not be reached normally
	   since execv takes control.
	 */

int get_child_id(pid_t to_look_pid,int children,pid_t *child_pid);
	/* Use : Looks for the id of the child based on its pid.Accepts as arguments the pid to look for,the number
	   of children and the array of the pids of the children processes.
	   Return Value : -1 if the id does not correspond to the given pid | Otherwise the id of the child with the
	   given pid.
    */

void* allocate_array(int size,void** space_used);
	/* Use : Allocates memory for an array of size 'size'.
	   Return Value : The pointer to the allocated memory.
	   Error Handling is done inside the function.
	*/

void free_all(void **space_used);
	/* Use : Frees all the memory allocated using the allocate_array function.
	   Return Value : None.
	*/

bool close_all_pipes(int** pipes,int** pipes2,int children);
	/* Use : Closes all the pipes that are open.
	   Return Value : True if all the pipes are closed successfully | False otherwise.
	*/
char* to_lower(char* str);
	/* Use : Converts a string to lowercase.
	   Return Value : The string in lowercase.
	*/
bool quit(char* str);
	/* Use : Checks if the user wants to quit.
	   Return Value : True if the user wants to quit | False otherwise.
	*/
bool kill_children(pid_t *child_pid,int children);
	/* Use : Kills all the children processes.
	   Return Value : True if all the children are killed successfully | False otherwise.
	*/