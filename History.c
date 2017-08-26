/* Domn Werner
   CS240-01
   Assignment 3 "History.c"
   03/16/2015 */
   
#include <stdio.h>
#include "History.h" 
#include "Execution.h"

#define MAX_COMM_NUM 1000
   
History history;

void HistSetup()
{
  int i;

  history.iHist = 0;

  history.commandsExecuted = 0;

  for (i = 0; i < HIST_SIZE; i++)
    {
      history.command[i].comNumber = -1;
    }
}

int ConvertToHistIndex(int index)
{
  int hIndex;

  if (history.commandsExecuted <= HIST_SIZE)
     hIndex = index;      
  else
     hIndex = (abs((history.commandsExecuted - 1) - index - HIST_SIZE) -  1);

  return hIndex;     
}

void AddToHistory(char* com)
{  
  int i;

  int iHistLimit = 0; //indicates that history has exceeded 999 commands
 
  if (history.commandsExecuted > MAX_COMM_NUM - 1) //to prevent overflow
      history.commandsExecuted = 0;      

  if (history.iHist > HIST_SIZE - 1)
    {
      history.iHist = HIST_SIZE - 1;
      iHistLimit = 1;
    }


  if (history.commandsExecuted < HIST_SIZE && !iHistLimit)
    {
      history.command[history.iHist].comNumber = history.commandsExecuted;
      ClearStr(history.command[history.iHist].com, MAX_STR_SIZE);
      CopyStr(com, history.command[history.iHist].com);
    }
  else 
    {
      for (i = 0; i < (HIST_SIZE - 1); i++) //shifts all entries left
		{
			history.command[i].comNumber = history.command[i+1].comNumber;
			ClearStr(history.command[i].com, MAX_STR_SIZE);
			CopyStr(history.command[i+1].com, history.command[i].com);
		}
		
      history.command[i].comNumber = history.commandsExecuted;
      ClearStr(history.command[i].com, MAX_STR_SIZE);
      CopyStr(com, history.command[i].com);
    }

  history.commandsExecuted++;
  history.iHist++;
}

void PrintHistory() 
{
  int i = 0;

  for (i = 0; i < HIST_SIZE && (history.command[i].comNumber != -1); i++)    
      printf("%d %s\n", history.command[i].comNumber, history.command[i].com);
    
}

void ExecLastHistCom() //executes the operator '!!' if 's' is that command
{		
	char s[MAX_STR_SIZE];
	if (history.iHist < 1)
		printf("Event does not exist.\n");
	else 
	{		
		CopyStr(history.command[history.iHist - 1].com, s); //copies previous command from history to s
		ExecuteNoHist(s); //executes s
	}
}

void ExecHistCom(char* c)
{
	int iBeg; //beginning of substr
	int iEnd; //end of substr
	char histSubStr[MAX_STR_SIZE];
	char command[MAX_STR_SIZE];
	int i;
	int cIndex;
	int hIndex;
	int charsToMove;
	int temp;
	
	CopyStr(c, command);
	
	i = 1;

	while (command[i] == ' ' && command[i] != '\0')
		i++;

	iBeg = i;

	while (command[i] != ' ' && command[i] != '\0')
		i++;

	iEnd = i;

	charsToMove = 0;

	while (command[i] != '\0')
	{
		charsToMove++;
		i++;
	}

	if (iBeg == iEnd)
	{
		printf("Syntax error: token '!' requires an argument\n");
	}
	else
	{
		strncpy(histSubStr, command + iBeg, iEnd - iBeg);
		histSubStr[iEnd - iBeg + 1] = '\0';

		cIndex = atoi(histSubStr);

		ClearStr(histSubStr, MAX_STR_SIZE);

		hIndex = cIndex;

		if (cIndex >= history.commandsExecuted || (cIndex < (history.commandsExecuted - HIST_SIZE)) ||
			cIndex < 0 || ((histSubStr[0] + '0') < 48) || (histSubStr[0] + '0') > 58)
		{
			printf("Error: invalid command number\n");
		}
		else
		{
			cIndex = ConvertToHistIndex(cIndex); //converts to valid history index

			strncpy(histSubStr, command + iEnd, charsToMove);

			ClearStr(command, MAX_STR_SIZE);

			strcat(command, history.command[cIndex].com);
			strcat(command, histSubStr);

			/* if (!strcmp(command, history.command[cIndex].com) == 0) //if user added more args
				AddToHistory(command);

			if (strcmp(command, "history") == 0)
				PrintHistory();
			else */
			ExecuteNoHist(command);
		}
	}	
}
