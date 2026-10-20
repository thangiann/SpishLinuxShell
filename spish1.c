#include <stdio.h>

#define MAXLINE 1024
#define MAXHIST 10

char line[MAXLINE+1];
int histcount = 0;


/* Just print our prompt */
void show_prompt()
{
    printf("spish$ ");
}

/* a) read characters and put them in the line[] array until \n is met
 * b) do not exceed MAXLINE characters
 * c) add the '\0' character at the end
 */
void read_line()
{
	for(int i = 0; i < MAXLINE; i++){
        char c;

        scanf("%c", &c);

        if(c == '\n'){
			line[i] = '\0';
			break;
		}
		else {
			line[i] = c;
		}
	
}}

/* Check if the line[] array starts with the word "exit"
 * Return 1 if it does, or 0 if it does not.
 */
int check_for_exit()
{
	if(line[0] == 'e'){
		if(line[1] == 'x'){
			if(line[2] == 'i'){
				if(line[3] == 't'){
					return 1;
				}
			}
		}
	}

	return 0;
}



void command_history(){

}

int main()
{
	printf("This is the Systems Programming @ Ioannina Shell (spish)\n");
	printf("Enter 'exit' to finish\n\n");

	while (1)
	{
		show_prompt();
		read_line();
		if (check_for_exit() == 1)
			break;		
		else printf("you typed: %s\n", line);
	}
	printf("bye!\n");
	return 0;
}