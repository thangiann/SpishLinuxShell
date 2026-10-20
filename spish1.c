#include <stdio.h>

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

void stringcopy(char a[], char b[]) {
    int i = 0;

    while (a[i] != '\0') {
        b[i] = a[i];
        i++;
    }

    b[i] = '\0';
}

void command_history(){
	for (int i = 0; i < MAXHIST - 1; i++){
		char tmp[MAXLINE];
		stringcopy(hist[i], tmp);
		stringcopy(hist[i + 1], hist[i]);
		stringcopy(tmp, hist[i + 1]);
	}


}

int check_for_history(){
	if(line[0] == 'h' && line[1] == 'i'&& line[2] == 's' && line[3] == 't' && line[4] == 'o'&& line[5] == 'r' && line[6] == 'y'){
		return 1;
	}

	return 0;
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
	
	} 
	if (check_for_history() != 1){
		int i = 0;
		while (line[i] != '\0'){
			hist[0][i] = line[i];
			i++;
		}
		hist[0][i] = '\0';
	}	
	command_history(line);
}

/* Check if the line[] array starts with the word "exit"
 * Return 1 if it does, or 0 if it does not.
 */
int check_for_exit()
{
	if(line[0] == 'e' && line[1] == 'x' && line[2] == 'i' && line[3] == 't'){
		return 1;
	}

	return 0;
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
		else if (check_for_history() == 1)
			for (size_t i = 0; i < MAXHIST; i++){
				printf("%s\n", hist[i]);
			}		
		else printf("you typed: %s\n", line);
	}
	printf("bye!\n");
	return 0;
}