//
//
//  myshell.c
//  myshell
//
//  Created by Arun Prakash Themothy Prabu Vincent on 9/25/16.
//  Copyright © 2016 Arun Prakash Themothy Prabu Vincent. All rights reserved.
//

#include <stdio.h>
#include <sys/types.h> /* pid_t */
#include <unistd.h>  /* _exit, fork */
#include <stdlib.h>  /* exit */

void execute_command(char **cmd) /* function to execute unix command*/
{
    pid_t pid;
    int status,flag;
    pid=fork(); /* Process Creation */
    if(pid<0)   /* Process creation failed */
    {
        printf("\n Forking Process Failed");
        exit(1);
    }
    if(pid==0) /* Child Process Execution */
    {
        flag=execvp(*cmd,cmd); /* Command execution */
        if(flag<0)   /* error in commanad execution */
        {
            printf("\n Execution failed...Terminating");
            exit(0);
        }
    }
    else
         while (wait(&status) != pid); /* Parent process waiting for child to execute */
}

/* Main Function Begins */

int main()
{
    int count=0;
    char str[100];
    char *cmd[50];
    printf("\n\n Command Prompt Shell ->\n");
    while(1)  /* Begining of loop */
    {
        count++;
        printf("\n Enter Command : ");
        gets(str);
        if(strcmp(str,"exit")==0) /* User Terminating program using exit */
        {
            printf("\nCommands Executed : %d \n",count); /* Total Commands executed */
            exit(0);
        }
        *cmd=str;
        execute_command(cmd); /* function call for unix command execution using fork */
        *str="\0";
        *cmd="\0";
    }
    return 1;
    
    }

