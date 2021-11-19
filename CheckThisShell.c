#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdbool.h>

//************************************************************
//List.c by Orlando Saddler Started
//************************************************************
void list()
{
	int status = 0;

	int pid2 = fork();

	if (pid2 == -1)
	{
		printf("The call to fork did not work");
		//return -1;
	}

	if(pid2 == 0)
	{
		execlp("clear", "clear", (char*) NULL);
	}

	if(waitpid(pid2, &status, 0) != pid2)
	{
	    perror("waitpid");
	    //return 1;
	}

	int pid1 = fork();

	if (pid1 == -1)
	{
	printf("The call to fork did not work");
	//return -1;
	}

	if (pid1 == 0)
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

	if(waitpid(pid1, &status, 0) != pid1)
	{
	    perror("waitpid");
	    //return 1;
	}

	
}
//************************************************************
//List.c by Orlando Saddler Finished
//************************************************************


//************************************************************
//exit.c by Farouq Adepetu Started
//************************************************************
int exitFunction(bool* done)
{
	char* scriptFileName = "history.h";

	//open a file call history.h
	//in write only mode
	//and erase all contents of the file
	//if file doesn't exist create the file
	//with user having read and write permission and execute permission
	//group and other only have read permission
	int scriptFD = open(scriptFileName, O_CREAT|O_WRONLY|O_TRUNC, 0744);

	//if error
	//opening or creating
	//history.h exit program
	if(scriptFD < 0)
	{
		printf("Failed to open/create %s\n", scriptFileName);
		perror("open");
		*done = true;
		return 1;
	}

	//history.h is a bash script file
	//contents written to that script file
	//#!/bin/bash
	//export HISTCONTROL="ignorespace"
	//history -r history.txt
	//set -o history
	// history 4
	char* script = "#!/bin/bash\nexport HISTCONTROL=\"ignorespace\"\nhistory -r history.txt\nset -o history\n history 4";
	
	//write contents of script to
	//history.h
	if(write(scriptFD, script, strlen(script)) < 0)
	{
		printf("Failed to write to history.h\n");
		perror("write");
		*done = true;
		return 1;
	}

	//close history.h
	if(close(scriptFD) < 0)
	{
		printf("Failed to close history.h\n");
		perror("close");
		*done = true;
		return 1;
	}

	int status = 0;

	int pid = fork(); //create a child process
	
	//if error creating child process
	//exit program
	if(pid < 0)
	{
		printf("Error in creating a child process\n");
		perror("fork");
		*done = true;
		return 1;
	}
	else if(pid == 0) //in child process
	{
		printf("\nList of last 4 commands:\n");
		//execute bash executable to
		//run script file to show
		//history of last 4 commands
		//if error exit child process
		if(execlp("bash", "bash", scriptFileName, (char*) NULL) < 0)
		{
			//close file b4 exiting
			//child process
			perror("execlp");
			exit(EXIT_FAILURE);
		}
	}

	//wait for child process to finish
	//executing
	//if error exit program
	if(waitpid(pid, &status, 0) != pid)
	{
		perror("waitpid");
		*done = true;
		return 1;
	}

	pid = fork(); //create child process

	if(pid < 0)
	{
		printf("Error in creating a child process\n");
		perror("fork");
		*done = true;
		return 1;
	}
	else if(pid == 0) //in child process
	{
		printf("\n");
		//excute ls -l
		//if error exit child process
		if(execlp("ls", "ls", "-l", (char*) NULL) < 0)
		{
			perror("execlp");
			exit(EXIT_FAILURE);
		}
	}
	
	//wait for child process to finish
	//executing
	//if error exit program
	if(waitpid(pid, &status, 0) != pid)
	{
		perror("waitpid");
		*done = true;
		return 1;
	}

	printf("\nPress ENTER or RETURN to exit shell: ");

	//loop to make sure
	//program exits when ENTER or RETURN is hit
	//from user
	while(getchar() != '\n');

	*done = true; //done = true will exit while loop and in turn program will exit
	return 0;
}
//************************************************************
//exit.c by Farouq Adepetu Finished
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

//char history[8192];

void functions(int historyFD, bool done){ //combining all functions into the shell file
	char n[100];
	//char N;
	//int pid1;
	//pid1 = fork();
	char* arg[100];		 
	while(!done)
	{
		printf("#");			   
		fgets(n, 100, stdin);
		//strcat(history, n);
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
			//write argument to history.txt file
			write(historyFD, arg[0], strlen(arg[0]));
			write(historyFD, "\n", 1);

			//clear();
			list();
			//int ret;
			printf("Renaming t1.txt to tree.txt\n");
			//ret = rename("t1.txt", "tree.txt");
		}
		if(strcmp(arg[0], "exit") == 0)
		{
			//write argument to history.txt file
			write(historyFD, arg[0], strlen(arg[0]));
			write(historyFD, "\n", 1);

			exitFunction(&done);
		}

		/*if(pid1 == -1)
			printf("Error");
		else if(pid1 == 0)	
			execvp(arg[0], arg);
		*/
	}
}
//************************************************************
//Shell.c by Faez Farhad Finished
//************************************************************

int main() 
{ 
	char* historyFileName = "history.txt";

	//open a file called history.txt
	//with read and write flags
	//and erase all contents in the file
	//if file doesn't exit create the file
	//with user having read and write permission
	//and group and other with only read permission
	int historyFD = open(historyFileName, O_CREAT|O_RDWR|O_TRUNC, 0644);

	//if error
	//opening or creating
	//history.txt exit program
	if(historyFD < 0)
	{
		printf("Failed to open/create %s\n", historyFileName);
		perror("open");
		return 1;
	}

	bool done = false;
	//clear();
	shell(); 
	functions(historyFD, done);

	//close history.txt
	//if error exit program
	if(close(historyFD) < 0)
	{
		printf("Failed to close history.txt\n");
		perror("close");
		return 1;
	}
} 
