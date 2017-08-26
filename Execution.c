/* Domn Werner
   CS240-01
   03/16/2015 
   Assignment 3 "Execution.c" */
   
#include "Execution.h"
#include "History.h"
   
void Allocate(char* s, char**** args)
{
	int numCommands;
	int numTokens;
	int com = 0; //index of current command being allocated
	int tok; //index of current token being allocated
	int iCom = 0;
	int iTok = 0; //current index to store a token
	int tBeg = 0; //index of string s where token starts
	int i;

	numCommands = CountCommands(s);

	*args = malloc(sizeof(char**) * numCommands);

	for (i = 0; i < numCommands; i++) //allocates array of commands
		(*args)[i] = malloc(sizeof(char*));

	for (i = numCommands; i > 0; i--) //allocates space for all tokens per command
	{
		tok = 0;
		numTokens = CountTokensInCommand(s); //counts the number of tokens per command in string 's'
		while (tok < numTokens)
		{
			(*args)[com][tok] = malloc((sizeof(char) * numTokens));
			tok++;
		}
		(*args)[com][tok] = malloc(sizeof(char)); //setting to null later
		com++;
	}

	for (i = 0; s[i] != '\0'; i++)
	{	
		printf("s[%d] = %c\n", i, s[i]);
		if (s[i] == ' ' && s[i + 1] != ';')
		{	
			printf("s[%d + 1] = %c\n", i, s[i + 1]);
			s[i] = '\0';
			(*args)[iCom][iTok] = (s + tBeg);
			tBeg = (i + 1);
			iTok++;
		}
		else if (s[i] == ' ' && s[i + 1] == ';')
		{
			printf("s[%d + 1] = %c\n", i, s[i + 1]);
			s[i] = '\0';
			(*args)[iCom][iTok] = (s + tBeg);
			tBeg = (i + 3);
			i += 2; //moves i to the index before the next token character
			(*args)[iCom][iTok + 1] = NULL; //sets last token to null
			iTok = 0;
			iCom++;
		}
		else if ((s[i + 1]) == '\0')
		{
			printf("s[%d + 1] = %c\n", i, s[i + 1]);
			(*args)[iCom][iTok] = (s + tBeg);
			(*args)[iCom][iTok + 1] = NULL; //sets last token to null
		}
	}

	(*args)[numCommands] = NULL; //cell after last command is null
}

int ExecuteCommand(char* com) //returns exit code if it finds 'exit' command in command string
{
	char*** comv; //array of commands		
	int i;
	
	char origCom[MAX_STR_SIZE]; //will store original command
		
	int addedToHist = 0; //flag for orig command has already been added to the list
	int exitCode = 0;
	int pipeFound = 0;
	
	ClearStr(origCom, MAX_STR_SIZE); //to be safe
	
	CopyStr(com, origCom); //copies com to origCom
	
	Allocate(com, &comv);

	PrintArgs(comv);

	//iterates through command array and executes command, checking for built-ins
	for (i = 0; comv[i] != NULL; i++)
	{
		if (strcmp(comv[i][0], "exit") == 0)
		{
			exitCode = 1;
			break;
		}
		else if (strcmp(comv[i][0], "history") == 0)
		{
			if (!addedToHist) //if whole command has not yet been added to history
			{			
				AddToHistory(origCom);				
				addedToHist = 1; //whole command has been added to history
			}
			PrintHistory(); //prints history
		}
		else if (strcmp(comv[i][0], "!!") == 0)
		{
			ExecLastHistCom();
		}
		else if (comv[i][0][0] == '!')
		{
			ExecHistCom(comv[i][0]);
		}
		else if (strcmp(comv[i][0], "export") == 0)
		{
			if (!addedToHist)
			{
				AddToHistory(origCom);
				addedToHist = 1;
			}
			ChangePath(comv[i]);
		}
		else 
		{
			if (!addedToHist)
			{
				AddToHistory(origCom);				
				addedToHist = 1;					
			}
			
			if (pipeFound = IsPipeCommand(comv[i]))
			{	
				printf("pipeFound\n", pipeFound);					
				BuildPipeComm(comv[i]);
			} 
			else
			{
				Execute(comv[i]);
			}
		}
		
		/* if (strcmp(comv[i][0], "export") == 0) //if first arg of a command is 'export'		
			ChangePath(comv[i]);		
		else
			Execute(comv[i]); */
	}
	
	ClearStr(origCom, strlen(origCom)); //to be safe
	
	return exitCode;
}

void ExecuteNoHist(char* com)
{	
	printf("ExecuteNoHist() called\n");
	char*** comv; //array of commands		
	int i;	

	Allocate(com, &comv);

	PrintArgs(comv);

	//iterates through command array and executes command, checking for built-ins
	for (i = 0; comv[i] != NULL; i++)
	{		
		if (strcmp(comv[i][0], "export") == 0)
		{			
			ChangePath(comv[i]);
		}
		else if (strcmp(comv[i][0], "history") == 0)
		{
			PrintHistory();
		}
		else 
		{			
			Execute(comv[i]);
		}
		
		/* if (strcmp(comv[i][0], "export") == 0) //if first arg of a command is 'export'		
			ChangePath(comv[i]);		
		else
			Execute(comv[i]); */
	}	
}

void Execute(char** args) //function that executes the commands in argv
{
	int status;
	pid_t pID = fork(); //forks here

	if (pID < 0) //error
	{
		fprintf(stderr, "\nFork failed");
		exit(1);
	}
	else if (pID == 0) //child process
	{
		if (execvp(*args, args) < 0) //exec command fails
		{
			printf("Command failed.\n");
			exit(1);
		}
		else
		{
			while (wait(&status) != pID);
		}
	}
	else //parent process
	{
		wait(NULL); //waits for child to finish
	}
}

void FreeArg(char**** args) //NOT WORKING
{
	int i, j;

	for (i = 0; (*args)[i] != NULL; i++)
	{
		for (j = 0; (*args)[i][j] != NULL; j++)
		{
			free((*args)[i][j]);
			(*args)[i][j] = NULL;
		}
	}
}
