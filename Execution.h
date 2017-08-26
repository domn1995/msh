#ifndef EXECUTION_H
#define EXECUTION_H

/* Domn Werner
   CS240-01
   03/16/2015 
   Assignment 3 "Execution.h" */
   
/* This is the header file for function pertaining to the 
   execution and allocation of commands in the msh program. */
   
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>   

#include "Setup.h"
#include "History.h"
#include "Pipe.h"

void Allocate(char*, char****); //allocates and returns number of arguments
int ExecuteCommand(char*);      //builds array of commands and executes them
void ExecuteNoHist(char*);      //executes without adding to history
void Execute(char**);           //executes command tokens in array of string passed in
void FreeArg(char****);         //frees dynamically allocated memory (NOT WORKING)
   
#endif
