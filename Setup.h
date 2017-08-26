#ifndef SETUP_H
#define SETUP_H

/* Domn Werner
   CS240-01
   Assignment 3 "Setup.h"
   03/16/2015 */
  
/* Handles the code related to the setup of the shell. It will 
   read SETUP_FILE and perform the commands found there. This 
   file will also contain the code related to the setup and
   and modification of the PATH environment variable. */

#include <stdlib.h>

#include "FormatString.h"
   
#define PATH_SIZE 1024 //max length of PATH var
#define PATH "PATH" //needs to go in Pathistory.h instead
#define SETUP_FILE ".mshrc"
   
char* varPATH; //points to PATH itself

void ShellSetup(); //reads and executes
void ChangePath(char**);
char* GetAppendToPath(char*);
int ExportSyntaxCorrect(char*); //returns 1 if export syntax is correct; 0 otherwise


#endif