#include <stdio.h>
#include <string.h>
#include <unistd.h> //doesnt work in windows, needs linux environment

#define MAXLINE 1024
#define MAXHIST 10

char line[MAXLINE+1];
int histcount = 0;
char hist[MAXHIST][MAXLINE];

#define MAXPROMPT 30
char prompt[MAXPROMPT - 1] = "spish$";

int echo_setting = 0;

/* Just print our prompt */
void show_prompt()
{
	char pwd[MAXLINE];
	getcwd(pwd, MAXLINE);
	printf("%s:~", pwd);
    printf("%s ", prompt);
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
		printf("%s \n", line);
		return 0;
	}
	if (check_for_cd() == 1){
		do_cd();
		printf("%s \n", line);
		return 0;
	}
	if (check_for_pwd() == 1){
		do_pwd();
		printf("%s \n", line);
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

void get_options(){

	FILE *fp;
	char key[MAXLINE], value[MAXLINE];

	fp = fopen(".spishrc", "r");
	if (fp == NULL){
		perror("error");
		return;
	} 

	while((fgets(line, MAXLINE, fp)) != NULL){
		if (sscanf(line, "%s%s", key, value) < 2)
			continue; 
		if(strncmp(line, "#", 1) == 0){
			continue;
		}
		if(strcmp(key,"prompt") == 0){
			strncpy(prompt, value,MAXPROMPT - 1);
		}
		if(strcmp(key,"echo")){
			echo_setting = strcmp(value, "off");
		}

	}

	fclose(fp);
	return;
}

int main()
{
	printf("This is the Systems Programming @ Ioannina Shell (spish)\n");
	printf("Enter 'exit' to finish\n\n");

	get_options();

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