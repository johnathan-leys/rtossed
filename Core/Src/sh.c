#include <string.h>
#include <stdio.h>

#include "main.h"
#include "sh.h"

//Project 01B code

int sh(void)
{
	char inputLine[100];	//initial declaration
	while (1) {		//Added in order to loop shell forever w/ idle task

		sh_getline(inputLine);

		printf("%s\n\r", inputLine);

		if ((strncmp(inputLine, "echo ", 5)) == 0) {	//if first 5 chars are "echo " with a space
			printf("%s\n\r", inputLine + 5);
		}

	}
	return 0;
}

/*
"Use getchar() to get a single character. Manage the string buffer such that a long line of input does not
beyond the end of the input line string. Return if a newline or carriage return is detected. Appropriately handle
backspace"
*/

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

		/*
		   if(iter >= 100){ //try to handle bigger lines
		   char *tempArray = (char *)calloc(iter + 10, sizeof(char)); //is calloc allowed?
		   strcpy(tempArray, inputLine); //set them to be same
		   inputLine=tempArray;//set to new array (larger)
		   }
		 */

		holder = getchar();	//grab new char for next iteration
		printf("%c", holder);	//show characters on screen like bash, can handle oo length

	}

	inputLine[iter] = '\0';	//string termination
	return 0;		//successful completion
}
