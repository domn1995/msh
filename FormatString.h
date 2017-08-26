#ifndef FORMAT_STRING_H
#define FORMAT_STRING_H

/* Domn Werner
   CS240-01
   03/16/2015 
   Assignment 3 "FormatString.h" */
   
/* This is a header file containing different functions
   that are used to format strings and character arrays. */
   
#include <stdio.h>
#include <string.h>
   
#define MAX_STR_SIZE 1024 //length of largest command msh can receive

char* RemoveSpaces(char*);  //removes leading/trailing whitespace and all but one whitespace between each token
int CountTokensInCommand(char*); //counts number of tokens of string passed in
int CountCommands(char*);    //counts number of commands of string passed in
void ClearStr(char*, int);  //Takes in a string and its size; clears it
void PrintArgs(char***); //prints command line arguments
char* FormatCommand(char*); //scans for semicolons and makes sure there a space before and after a semicolon
char* Format(char*); //returns a formmated string prepared to be allocated and executed
void CopyStr(char*, char*); //copies first string to second string
void ShiftRight(char*, int);

#endif