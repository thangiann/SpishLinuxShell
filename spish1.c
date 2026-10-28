#include <stdio.h>
#include <string.h>

#define MAXLINE 1024
#define MAXHIST 10

char line[MAXLINE+1];
int histcount = 0;
char hist[MAXHIST][MAXLINE];

/* Just print our prompt */
void show_prompt()
{
    printf("spish$ ");
}


void command_history()
{
    for (int i = 0; i < MAXHIST - 1; i++) {
        strcpy(hist[i], hist[i + 1]);
    }

    strcpy(hist[MAXHIST - 1], line);
}

void print_history(){
	for (int i = 0; i < 10; i++)
	{
		printf("%s\n", hist[i]);
	}
	
}

int check_for_history()
{
    return (strcmp(line, "history") == 0);
}

int check_for_exit()
{
    return (strcmp(line, "exit") == 0);
}

int do_command(){
	if (check_for_exit() == 1){
		return 1;
	}

	if (check_for_history() == 1){
		print_history();
		return 0;
	}
}

/* a) read characters and put them in the line[] array until \n is met
 * b) do not exceed MAXLINE characters
 * c) add the '\0' character at the end
 */
void read_line()
{	

	if (fgets(line, sizeof(line), stdin) == NULL) {
        // Handle EOF (e.g., Ctrl+D) by triggering exit
        strcpy(line, "exit");
        return;
    }
	
	line[strcspn(line, "\n")] = '\0'; 

	if (line[0] != '\0' && check_for_history() != 1) {
        command_history();
    }
}

int main()
{
	printf("This is the Systems Programming @ Ioannina Shell (spish)\n");
	printf("Enter 'exit' to finish\n\n");

	while (1) {
		show_prompt();
		read_line();
		if (do_command() == 1){
			break;
		}
		
	}
	printf("bye!\n");
	return 0;
}