/* Domn Werner
   CS240-01
   Assignment 3 "Setup.c"
   03/16/2015 */  

#include "Setup.h"
  
void ShellSetup()
{
	FILE* fp = fopen(SETUP_FILE, "r");

	if (!fp)
	{
		printf("Could not open file: %s\n", SETUP_FILE);
		return;
	}

	char str[MAX_STR_SIZE];
	char* command;

	while (fgets(str, MAX_STR_SIZE, (FILE*)fp))
	{
		command = Format(str);
		ExecuteNoHist(command);
	}
	fclose(fp);
}

void ChangePath(char** args) //called with command 'export'
{
	char* appendToPATH;
	char* tempPATH;
	int appendLen;
	int appendStart;
	int newPATHSize;
	int i;
	int j;

	if (args[1] == NULL) //no argument after export
	{
		printf("Error: 'export' must be followed by an argument\n");
		return;
	}
	else if (!ExportSyntaxCorrect(args[1])) //checks export syntax
	{
		printf("Error: incorrect syntax for 'export' command\n");
		return;
	}

	appendToPATH = GetAppendToPath(args[1]); //gets string to append to PATH

	if (strstr(varPATH, appendToPATH) != NULL) //check if appendToPATH already exists in PATH
		printf("PATH already contains '%s'\n", appendToPATH);
	else
	{
		newPATHSize = strlen(varPATH) + strlen(appendToPATH) + 1;

		tempPATH = malloc(newPATHSize);

		strcpy(tempPATH, varPATH);

		for (i = strlen(varPATH), j = 0; i < newPATHSize && newPATHSize < PATH_SIZE; i++, j++)
			tempPATH[i] = appendToPATH[j];

		varPATH = tempPATH;
		
		setenv(PATH, varPATH, 1); //overwrites PATH variable 
		varPATH = getenv(PATH);
		printf("varPATH: %s\n", varPATH);
	}
}

char* GetAppendToPath(char* s) //extracts string to append to the end of PATH
{
	int start;
	int len;
	int colonFound = 0;

	char* append;

	for (len = 0; s[len] != '\0'; len++)
	{
		if (s[len] == ':' && !colonFound)
		{
			colonFound = 1;
			start = len;
		}
	}

	len++;

	append = malloc(len - start);

	strncpy(append, s + start, len - start);

	append[len - start] = '\0';

	return append;
}

int ExportSyntaxCorrect(char* s) //checks if the user entered the proper syntax for the 'export' command
{
	char* properSyntax = "PATH=$PATH:/";
	char* substr;
	int i;

	for (i = 0; s[i] != '/' && s[i] != '0'; i++);

	i++;

	substr = malloc(i);

	strncpy(substr, s, i);

	substr[i] = '\0';

	return (strcmp(substr, properSyntax) == 0);
}