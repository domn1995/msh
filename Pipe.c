/* Domn Werner
   CS240-01
   03/16/2015 
   Assignment 3 "Pipe.c" */
   
/* This is the implementation file of the piping feature of msh */

#include "Pipe.h"
#include "FormatString.h"
#include <stdio.h>
#include <stdlib.h>

int IsPipeCommand(char** coms) //returns 1 if "|" found, else returns zero
{
	int i;
	int pipeFound = 0;
	
	for (i = 0; coms[i] != NULL; i++)
	{
		if (strcmp(coms[i], "|") == 0) //pipe operator found
		{
			pipeFound = 1;
			break;
		}
	}
	
	return pipeFound;
}

void BuildPipeComm(char** coms) //builds two command strings, before and after "|"
{
    int i = 0;
	int j = 0;
	int index = 0;	
	int pipeFound = 0;
	
	char com1[MAX_STR_SIZE];
	char com2[MAX_STR_SIZE];
	ClearStr(com1, MAX_STR_SIZE);
	ClearStr(com2, MAX_STR_SIZE);
	
	printf("index = %d\n", index);
	for (i = 0; coms[i] != NULL; i++)
	{
	    if (strcmp(coms[i],"|") == 0)
	    {
		printf("in if\n");
		i++;
		index = 0;
		break;
	    }
	    for (j = 0; coms[i][j] != '\0'; j++)
	    {
		com1[index++] = coms[i][j];
	    }
	    com1[index++] = ' ';	    		    
	}

	for (i; coms[i] != NULL; i++)
	{
	    for (j = 0; coms[i][j] != '\0'; j++)
	    {
		com2[index++] = coms[i][j];
	    }
	    com2[index++] = ' ';
	}
	
	//printf("atoi(coms[0][2]) = %d", atoi(coms[0][2]));	
	printf("com1 = %s\n", com1);
	printf("com2 = %s\n", com2);
	
	ExecPipe(com1, com2);
}	

void ExecPipe(char* cmd1, char* cmd2) //creates and executes pipe
{	
        FILE *pipein_fp, *pipeout_fp;
        char readbuf[80];

        /* Create one way pipe line with call to popen() */
        if ((pipein_fp = popen(cmd1, "r")) == NULL)
        {
                perror("popen");
                exit(1);
        }

        /* Create one way pipe line with call to popen() */
        if ((pipeout_fp = popen(cmd2, "w")) == NULL)
        {
                perror("popen");
                exit(1);
        }

        /* Processing loop */
        while(fgets(readbuf, 80, pipein_fp))
                fputs(readbuf, pipeout_fp);

        /* Close the pipes */
        pclose(pipein_fp);
        pclose(pipeout_fp);	
}