/* Domn Werner
CS240-01
03/16/2015
Assignment 3 "FormatString.c" */

#include "FormatString.h"   

char* RemoveSpaces(char* s)
{
	char* inStr = s, *outStr = s;
	int prevSpace = 0;
	int firstCharFound = 0;

	while (*inStr)
	{
		if (isspace(*inStr)) //if current char is a space
		{
			if (!firstCharFound) //if first character has not yet been found
			{
				while (isspace(*inStr)) //loop until first char
				{
					if (isspace(*inStr))
						inStr++;
				}
				*outStr++ = *inStr; //assign first char
				firstCharFound = 1; //set first char found to true
			}
			else //first char has been found and current char is a space
			{
				if (!prevSpace) //if previous was not a space 
				{
					*outStr++ = ' '; //add a space
				}
				else
				{
					while (isspace(*inStr)) //loop until first char of next token
					{
						if (isspace(*inStr))
							inStr++;
					}
					*outStr++ = *inStr;
				}
				prevSpace = 1;
			}

		}
		else //current char not a space
		{
			if (!firstCharFound) //if first char hasn't been found this is the first char
			{
				*outStr++ = *inStr;
				firstCharFound = 1;
			}
			else
			{
				*outStr++ = *inStr;
			}
			prevSpace = 0;
		}

		inStr++;
	}

	if (isspace(*(outStr - 1))) //if last char is a space
		*(outStr - 1) = '\0'; //replace last space with nullbyte
	else *outStr = '\0'; //otherwise append null to end

	return s;
}

int CountTokensInCommand(char* s)
{
	int tokens = 0;
	static int i = 0;

	for (i; s[i] != '\0' && s[i] != ';'; i++) //iterates through every character in s
	{
		if (s[i] == ' ' || s[i + 1] == '\0') //when a space is found and next char is not a semicolon or end is found
		{
			tokens++;     //increments token counter
		}
	}

	if (s[i] == '\0') //if at end, reset 'i' for next command
		i = 0;
	else              //otherwise start at next token
		i += 2;

	return tokens;
}

int CountCommands(char* s) //finds and returns the number of commands 
{
	int i;
	int nComms = 1;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] == ';')
			nComms++;
	}

	return nComms;
}

void ClearStr(char* s, int size) //clears string passed in
{
	int i;
	for (i = 0; i < size; i++)
	{
		s[i] = '\0';
	}
}

void PrintArgs(char*** args) //prints the contents of the array passed in
{
	int i, j;

	printf("------Command(s)------\n\n");
	for (i = 0; args[i] != NULL; i++)
	{
		for (j = 0; args[i][j] != NULL; j++)
		{
			printf("args[%d][%d] = %s\n", i, j, args[i][j]);
		}
		printf("\n");
	}
	printf("--------------------\n");
}

char* FormatCommand(char s[]) //removes leading, trailing, duplicate semicolons, adds a space between semicolons
{
	int i = 0, j;

	while ((isspace(s[i]) || s[i] == ';') && s[i] != '\0') //removes leading semicolons
	{
		s[i] = ' ';
		i++;
	}

	while (s[i + 1] != '\0')
		i++;

	//'i' now holds the index of the nullbyte

	while ((isspace(s[i]) || s[i] == ';') && i >= 0) //removes trailing semicolons
	{
		s[i] = ' ';
		i--;
	}

	for (i = 0; s[i] != '\0'; i++, j++) //removes dup semicolons midcommand
	{
		if (s[i] == ';')
		{
			j = i + 1;
			while ((isspace(s[j]) || s[j] == ';') && s[j] != '\0')
			{
				s[j] = ' ';
				j++;
			}
		}

		if (s[i] == ';' && !isspace(s[i - 1]) && s[i + 1] != '\0') //adds a space to the right of ';' if need
		{
			if (strlen(s) > MAX_STR_SIZE)
				return s;
			else
			{
				ShiftRight(s, i);
				s[i] = ' ';
			}
		}

		if (s[i] == ';' && !isspace(s[i + 1]) && s[i + 1] != '\0') //adds a space to the left of ';' if needed
		{
			if (strlen(s) > MAX_STR_SIZE)
				return s;
			else
			{
				ShiftRight(s, i + 1);
				s[i + 1] = ' ';
			}
		}
	}
	return s;
}

char* Format(char* s)
{
    char* tempCommand1;
    char* tempCommand2;
    char* tempCommand3;
    char* finalCommand;

    tempCommand1 = FormatCommand(s);
    tempCommand2 = RemoveSpaces(tempCommand1);
    tempCommand3 = FormatCommand(tempCommand2);
    finalCommand = RemoveSpaces(tempCommand3);

    return finalCommand;  
}

void CopyStr(char* src, char* dest)
{
	int i;

	for (i = 0; src[i] != '\0' && i < (MAX_STR_SIZE - 1); i++)
		dest[i] = src[i];
}

void ShiftRight(char* s, int index) //shifts all chars starting at index i to the right
{
	int j = (strlen(s) - 1); //index of last char

	if (j > MAX_STR_SIZE)
		return;
	else
	{
		s[j + 2] = '\0';
		while (j >= index)
		{
			s[j + 1] = s[j];
			j--;
		}
	}
}
