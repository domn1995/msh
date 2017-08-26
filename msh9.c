/* Domn Werner
CS240-01
03/16/2015
Assignment #3 "msh9.c" */

/* This version of msh that implements all the requirements for the assignment. It 
	uses a 3D array of pointers as a data structure to keep track of commands and tokens. */

#include "History.h"
#include "FormatString.h"
#include "Execution.h"
#include "Setup.h"

void GetInput(char*);     //gets input from the user like a command line
void CheckBuiltIn(char*); //executes built-ins or command line arguments 

int main()
{	
	char str[MAX_STR_SIZE];
	char* command;	
	varPATH = getenv(PATH); //declared in 'Setup.h'	
	int exitShell = 0;
	
	ShellSetup(); //executes '.mshrc' file	

	HistSetup(); //initializes history	

	while (1)
	{
		do 
		{
			GetInput(str);
		} 
		while (str[0] == '\0'); //loops while the user just presses enter

		command = Format(str);		
		printf("command = %s\n", command);

		exitShell = ExecuteCommand(command);	
			
		if (exitShell) break;

		ClearStr(str, strlen(str));				
	}

	return 0;
}

void GetInput(char* s) //function that gets input from user and stores it in 's'
{
	int i;

	printf("?: ");
	for (i = 0;; i++) //user input loop -- gets command from user
	{
		s[i] = getchar();
		if (s[i] == '\n') //if it receives new-line char
		{
			s[i] = '\0'; //replaces it with nullbyte
			break;         //and exists input loop
		}
	}
}