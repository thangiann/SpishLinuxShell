#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAXLINE 1024
#define MAXHIST 10

char line[MAXLINE+1];
int histcount = 0;
char hist[MAXHIST][MAXLINE];

/* Just print our prompt */
void show_prompt()
{
	char pwd[MAXLINE];
	getcwd(pwd, MAXLINE);
	printf("%s:~", pwd);
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

void do_cd(){
	if (strcmp(line, "cd") == 0){
		chdir("/");
	}
	const char *target = "cd ";
	char *match = strstr(line, target);

	char dir_target[MAXLINE];
	if (match != NULL) {
		char *after = match + strlen("cd ");
		
		int i = 0;

		while (*after != '\n' && *after != '\0' && i < MAXLINE - 1) {
			dir_target[i] = *after;
			i++;
			after++;
		}
		
		dir_target[i] = '\0'; 
	}

	chdir(dir_target);
}

void do_pwd(){
	char pwd[MAXLINE];
	printf("%s\n", getcwd(pwd, MAXLINE));
}

int check_for_history()
{
    return (strcmp(line, "history") == 0);
}

int check_for_exit()
{
    return (strcmp(line, "exit") == 0);
}

int check_for_cd(){
	return (strncmp(line, "cd ", 3) == 0 || strcmp(line, "cd") == 0);
}

int check_for_pwd(){
	return (strcmp(line,"pwd") == 0);
}

int do_command(){
	if (check_for_exit() == 1){
		return 1;
	}

	if (check_for_history() == 1){
		print_history();
		return 0;
	}
	if (check_for_cd() == 1){
		do_cd();
		return 0;
	}
	if (check_for_pwd() == 1){
		do_pwd();
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