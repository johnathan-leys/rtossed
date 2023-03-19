#include <string.h>
#include <stdio.h>

#include "main.h"
#include "sh.h"

//Project 01B code

int sh(void)
{
	char inputLine[100];	//initial declaration
	while (1) {		//Added in order to loop shell forever w/ idle task, avoid timeouts

		sh_getline(inputLine);

		printf("%s\n\r", inputLine);
       
		if ((strncmp(inputLine, "echo ", 5)) == 0) {	//if first 5 chars are "echo " with a space
			printf("%s\n\r", inputLine + 5);
		}

	}
	return 0;
}


int sh_getline(char *inputLine)
{

	char holder;		//hold each char that is read in

	int iter = 0;		//iterator
	holder = getchar();	//get initial char holder = getchar();
	putchar(holder);

	while (holder != '\n' && holder != '\r') {	//loop while holder char is not newline or carriage return  

		if ((holder != '\b') && (iter <= 100)) {	//if not backspace, not full string 
			inputLine[iter] = holder;	//set input char to array value[iter]
			iter++;
		} else if (iter > 0) {	//make sure we dont run into negative space
			iter--;	//decrement iter to replace previous char
			printf(" \b");	// replace with " ", go back, appears to make blank

		}


		holder = getchar();	//grab new char for next iteration
		printf("%c", holder);	//show characters on screen like bash, can handle oo length

	}
    

	inputLine[iter] = '\0';	//string termination
	return 0;		//successful completion
}
