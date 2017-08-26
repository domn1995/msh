#ifndef HISTORY_H
#define HISTORY_H

/* Domn Werner
   CS240-01
   Assignment 3 "History.h"
   03/16/2015 */
   
/* Handles the code related to msh's history feature */
      
#include "FormatString.h"
   
#define HIST_SIZE 20  //how many commands history will track

typedef struct Command 
{
  int comNumber; //the number of the command
  char com[MAX_STR_SIZE]; //command itself
} Command;

typedef struct History 
{
  int commandsExecuted;
  int iHist; //index of command array
  Command command[HIST_SIZE]; //array of commands and their numbers
} History;

void HistSetup(); //initializes History struct
void AddToHistory(char*); //adds a string (a command) to history
void PrintHistory(); //prints the history array
int ConvertToHistIndex(int); //converts command number to a valid history index
void ExecLastHistCom(); //executes the '!!' command
void ExecHistCom(char*);

#endif