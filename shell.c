#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

//************************************************************
//List.c by Orlando Saddler Started
//************************************************************
void list()
{
    int pid = fork();

    if (pid == -1)
    {
        printf("The call to fork did not work");
        //return -1;
    }
    

    if (pid == 0)
    {
    
    FILE *fp=popen("ls -l","r"); //popen() is used so that the program can communicate directly to the
    //shell which will invoke it's ls command and return a file pointer/stream that can be used
    //to read the output of the shell
    char output[100];
    //if(fp==NULL) return -1; //In case of error
    int fd = open("t1.txt", O_WRONLY| O_TRUNC);
    printf("\n");
    
    //At a time we are reading 100 chars or till newline if exits
    while(fgets(output,100,fp)!=NULL) { //fgets() reads from the stream the file object
        //points to and stores it within the char array output, 100 characters at a time

        
        printf("%s",output); //printing ls -l results to the command line
        write(fd,output, strlen(output)); //whats written to the file will be the exact length of
        //the output 100 chars at a time
    
    }
    char* param[] = {"mv", "t1.txt", "tree.txt", NULL};
    execvp("/usr/bin/mv", param);
    

    pclose(fp);
    
 }
    else {
        
        execlp("clear", "clear", (char*) NULL);
        
        
    }
      
}
//************************************************************
//List.c by Orlando Saddler Finished
//************************************************************


//************************************************************
//shell.c by Faez Farhad Started
//************************************************************
void shell()
{
	printf("Warrior's Terminal initialized..\n");
	printf("Please use commands: list,exit,path,tree\n");
}
//code to go to previous directory
void cdout()
{
	char paths[100];
	chdir("..");
	printf("%s\n", getcwd(paths,100));
}
//code to go to specific directory
void cdin(char *arg)
{
	char paths[100];
	chdir(arg);
	printf("%s\n", getcwd(paths,100));
}

char history[8192];

void functions(){ //combining all functions into the shell file
	char n[100];
	//char N;
	int pid1;
	pid1 = fork();
	while(1){
		wait(NULL);
		char* arg[100];		 
		printf("#");			   
		fgets(n, 100, stdin);
		strcat(history, n);
		char *s = strchr(n, '\n');
		if(s){			   
			*s = '\0';
		}	   
		arg[0] = strtok(n," "); 
		int i = 0;	 	   
		while(arg[i] != NULL)      
		{			   
					  
			arg[++i] = strtok(NULL, " "); 
		}
		if(arg[0] == NULL)
			exit(0);
		if(strcmp(arg[0], "cd") == 0)
		{
			if(arg[1] != NULL)
			{
				printf("Current Specified Directory: ");
				cdin(arg[1]);
			}
			else
			{
				printf("Previous Specified Directory: ");
				cdout();
			}
		}	
		if(strcmp(arg[0], "list") == 0)
		{
			clear();
			list();
			//int ret;
			printf("Renaming t1.txt to tree.txt\n");
			//ret = rename("t1.txt", "tree.txt");
		}

		if(pid1 == -1)
			printf("Error");
		else if(pid1 == 0)	
			execvp(arg[0], arg);
	} 
}
//************************************************************
//Shell.c by Faez Farhad Finished
//************************************************************

int main() 
{ 
    clear();
    shell(); 
	while(1)
		functions();
} 
