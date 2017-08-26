#ifndef PIPE_H
#define PIPE_H

/* Domn Werner
   CS240-01
   03/16/2015 
   Assignment 3 "Pipe.h" */
   
/* This is the header file pertaining to the implementation of msh's piping feature. */
   
int IsPipeCommand(char**); //returns true if one of the strings of the array is "|", else 0
void BuildPipeComm(char**); //builds a string of the commands before and after the "|" operator
void ExecPipe(char*, char*); //takes in array of strings and pipes

#endif