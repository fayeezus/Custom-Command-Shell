// CSC 332 Group Project - Warrior's (Section H)
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <unistd.h>  
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>

//clears terminal with previous commands.
#define clear() printf("\033[H\033[J") 

//************************************************************
//tree.c by Moshahid Kallol Started
//************************************************************
void tree()
{
    //printf("---------------------------------------------------------------------------------------------------- \n\n");
    mkdir("Dir0", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    printf("(1) Made directory Dir0 \n\n");
    chdir("Dir0"); //changing directory to Dir0;
    printf("(2) Changed working directory to Dir0 \n\n");

    //creating 3 txt files;
    int t1 = open("t1.txt", O_RDWR | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
    int t2 = open("t2.txt", O_RDWR | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
    int t3 = open("t3.txt", O_RDWR | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
    printf("(3) Created three text files in Dir0 called t1.txt, t2.txt and t3.txt \n\n");

    close(t1);
    close(t2);
    close(t3);
    // printf("(4) Closed all text files\n\n");

    mkdir("Dir1", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH); //making Dir1 inside Dir0;
    printf("(4) Created empty directory Dir1 \n\n");
    //printf("---------------------------------------------------------------------------------------------------- \n\n");
    //printf("All the tasks are complete \n");
}
//************************************************************
//tree.c by Moshahid Kallol Finished
//************************************************************


//************************************************************
//List.c by Orlando Saddler Started
//************************************************************
void list()
{
    //printf("---------------------------------------------------------------------------------------------------- \n\n"); 

	int status = 0;

	int pid = fork();

	if (pid < 0)
	{
		printf("The call to fork did not work");
		//return -1;
	}

	if(pid == 0)
	{
		execlp("clear", "clear", (char*) NULL);
	}
	if(waitpid(pid, &status, 0) != pid)
	{
	    perror("waitpid");
	    //return 1;
	}

	pid = fork();

	if (pid < 0)
	{
		printf("The call to fork did not work");
		//return -1;
	}

	if (pid == 0)
	{
		//printf("---------------------------------------------------------------------------------------------------- \n\n"); 
        printf("(1) Terminal screen has been cleared \n\n");
		printf("(2) Below is a list of all content of current directory: ");
		FILE *fp=popen("ls -l","r"); //popen() is used so that the program can communicate directly to the
		//shell which will invoke it's ls command and return a file pointer/stream that can be used
		//to read the output of the shell
		char output[100];
		//if(fp==NULL) return -1; //In case of error
		int fd = open("t1.txt", O_WRONLY| O_TRUNC);
		printf("\n");

		//At a time we are reading 100 chars or till newline if exits
		while(fgets(output,100,fp)!=NULL) 
		{ 
			//fgets() reads from the stream the file object
			//points to and stores it within the char array output, 100 characters at a time
			printf("%s",output); //printing ls -l results to the command line
			write(fd,output, strlen(output)); //whats written to the file will be the exact length of
			//the output 100 chars at a time
		}

		rename("t1.txt", "tree.txt");
		printf("\n");
        printf("(3) Changed name of t1.txt into tree.txt\n\n");
		//char* param[] = {"mv", "t1.txt", "tree.txt", NULL};
		//execvp("usr/bin/mv", param);

		pclose(fp);
		close(fd);
        //printf("(3) Successfully closed all files.\n\n");
		exit(EXIT_SUCCESS);
	}

	if(waitpid(pid, &status, 0) != pid)
	{
	    perror("waitpid");
	    //return 1;
	
    //printf("---------------------------------------------------------------------------------------------------- \n\n");
    }
}
//************************************************************
//List.c by Orlando Saddler Finished
//************************************************************

//************************************************************
//path.c by Progga Chowdhury Started
//************************************************************
void path ()
{
	//int main (int argc, char **argv) {
	FILE * t2_file = fopen("t2.txt", "w+"); // open the file t2.txt in reading and writing mode

	//printf("---------------------------------------------------------------------------------------------------- \n\n");                                   

	char cont[100]; // this array is used to store the contents of directory 
	if (getcwd(cont, sizeof(cont)) != NULL) // the getcwd() functions gets the path name of the current working directory
	{ 
		fputs(cont, t2_file); // the fputs() function will write an array of characters to a file 
		fclose(t2_file); // close the t2.txt file 

		// *** 1. PRINT CURRENT WORKING DIRECTORY PATH TO t2.txt AND terminal ***
		printf("(1) Wrote the path of the current directory to the terminal & t2.txt \n\n---> PATH OF CURRENT DIRECTORY: %s \n\n", cont); 	
		
		// *** 2. CHANGE THE NAME OF t2.txt INTO path.txt ***
		rename("t2.txt", "path.txt"); 
		printf("(2) Renamed the file t2.txt into path.txt \n\n"); // print that t2.txt file was renamed to path.txt

		FILE *tree_file, *path_file, *t3_file; // open the necessary files to be used in concatenation later
		tree_file = fopen("tree.txt", "r"); 
		path_file = fopen("path.txt", "r"); 
		t3_file = fopen("t3.txt", "a"); 

		// *** 3. CONCATENATE CONTENT OF tree.txt & path.txt INTO t3.txt ***
		char concat; 
		if (tree_file == NULL || t3_file == NULL) // if the files are not found / do not exist
		{
			perror("files access \n\n"); // perror 
			printf("ERROR: COULD NOT ACCESS THE REQUIRED FILES \n\n"); // print error message
			exit(0); // and then exit 
		}

		concat = fgetc(tree_file); // this handles concatenation of tree.txt into t3.txt 
		while (concat != EOF) // until the end of the file
		{ 
			fputc(concat, t3_file); // fputc() will write a single character at a time to the provided file 
			concat = fgetc(tree_file); // fgetc() will to read the content of a file, one character at a time
		}
		
		concat = fgetc(path_file); // this handles concatenation of path.txt into t3.txt
		while (concat != EOF) // until the end of the file
		{ 
			fputc(concat, t3_file); // fputc() will write a single character at a time to the provided file 
			concat = fgetc(path_file); // fgetc() will to read the content of a file, one character at a time
		}

		fclose(tree_file); // close tree.txt
		fclose(path_file); // close path.txt
		fclose(t3_file); // close t3.txt 

		printf("(3) Concatenated the content of tree.txt & path.txt into t3.txt \n\n"); // print that concatenation was successful 

		// *** 4. CHANGE THE NAME OF t3.txt INTO log.txt ***
		rename("t3.txt", "log.txt"); 
		printf("(4) Renamed the file t3.txt into log.txt \n\n"); /// print that t3.txt file was renamed to log.txt

		// *** 5. DELETE tree.txt AND path.txt ***
		remove("tree.txt"); 
		remove("path.txt"); 
		printf("(5) Deleted files tree.txt & path.txt \n\n"); // print that the files tree.txt & path.txt were deleted successfully

		//printf("---------------------------------------------------------------------------------------------------- \n\n");                                   
	}
	
	else // else, if the current directory was unable to be accessed (getcwd error)... 
	{
		perror("dir path \n\n"); // perror
		printf("ERROR: UNABLE TO ACCESS CURRENT DIRECTORY PATH \n\n"); // print error message
	}
}

//************************************************************
//path.c by Progga Chowdhury Finished
//************************************************************


//************************************************************
//exit.c by Farouq Adepetu Started
//************************************************************

int exitFunction(bool* done)
{
   // printf("---------------------------------------------------------------------------------------------------- \n\n");
	int pid = 0;
	int status = 0;

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

	char content[1024]; // this array is used to store the path of the current directory
	char* ret;
	if (getcwd(content, sizeof(content)) != NULL) 
	{
		ret = strstr(content, "Dir0");
		//if in Dir0 go to parent directory where the history.txt
		//file is located
		if(ret != NULL)
		{
			chdir("..");
		}
	}
	
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


	pid = fork(); //create a child process
	
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
        // printf("\n---------------------------------------------------------------------------------------------------- \n\n");
		printf("\n*** Hit RETURN OR ENTER to exit the terminal *** \n");
        //printf("---------------------------------------------------------------------------------------------------- \n\n");

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
    printf("---------------------------------------------------------------------------------------------------- \n\n");
	printf("WARRIOR'S TERMINAL INITIALIZED...\n\n");
    printf("---------------------------------------------------------------------------------------------------- \n\n");
	printf("***** PLEASE USE THE FOLLOWING COMMANDS: tree, list, path or exit ***** \n\n");
}

//printing current working directory
//source: https://www.geeksforgeeks.org/chdir-in-c-language-with-examples/
void currdir()
{
	char s[100];
	chdir("..");
	printf("%s\n", getcwd(s,100));
}

//code to go to specific directory
void specdir(char *arg)
{
	char s[100];
	chdir(arg);
	printf("%s\n", getcwd(s,100));
}

//combining all functions into the shell file
void functions(int historyFD, bool done)
{ 	char n[100];
	char* arg[100];
    char current[100]; 
	while(!done) //runs the following functions until done gets set to true, which happens when user types "exit"
	{
        getcwd(current, sizeof(current)); //function returns the name of the current working directory
        printf("username@username:~%s->", current); // this is what will print when you are in the shell
        printf("# ");	//our command prompt is "#"		   
		fgets(n, 100, stdin); // fgets() function as it applies to reading text input
		char *s = strchr(n, '\n'); //standard character
		if(s){			   
			*s = '\0';
		}	
		arg[0] = strtok(n," "); //set null character in each delimiter indicated
		int i = 0;	 	   
		while(arg[i] != NULL)      
		{			   
					  
			arg[++i] = strtok(NULL, " "); //set null character in each delimiter indicated
		}
		if(arg[0] == NULL)
			exit(0);
		else if(strcmp(arg[0], "cd") == 0) //when user types cd, it will print current directory. and if they do cd .. it will print previous specfied directory
		{
			if(arg[1] != NULL)
			{
				printf("Current Specified Directory: ");
				specdir(arg[1]); //prints current directory
                printf("***** PLEASE USE THE FOLLOWING COMMANDS: tree, list, path or exit ***** \n\n");
			}
			else
			{
				printf("Previous Specified Directory: ");
				currdir(); //prints previous directory
                printf("***** PLEASE USE THE FOLLOWING COMMANDS: tree, list, path or exit ***** \n\n");
			}
		}
        	else if(strcmp(arg[0], "tree") == 0) //when user types "tree", it will execute tree() command and save it to history.txt file
		{
			//write argument to history.txt file
			if(write(historyFD, arg[0], strlen(arg[0])) < 0)
			{
				printf("Error writing to history.txt");
				perror("write");
				return;
			}
			
			if(write(historyFD, "\n", 1) < 0)
			{
				printf("Error writing to history.txt");
				perror("write");
				return;
			}
            printf("---------------------------------------------------------------------------------------------------- \n\n");
			printf("Executing tree command... \n\n");
			tree(); //executing tree() command
             	printf("Tree command tasks completed. Please, check the folder for changes.\n\n");
                printf("---------------------------------------------------------------------------------------------------- \n\n");
                printf("***** PLEASE USE THE FOLLOWING COMMANDS: tree, list, path or exit ***** \n\n");
		}
		else if(strcmp(arg[0], "list") == 0) //when user types "list", it will execute list() command and save it to history.txt file
		{
			//write argument to history.txt file
			if(write(historyFD, arg[0], strlen(arg[0])) < 0)
			{
				printf("Error writing to history.txt");
				perror("write");
				return;
			}
			
			if(write(historyFD, "\n", 1) < 0)
			{
				printf("Error writing to history.txt");
				perror("write");
				return;
			}
            //printf("---------------------------------------------------------------------------------------------------- \n\n");
			list(); //executing list() command
            	printf("List command tasks completed. Please, check the folder for changes.\n\n");
                printf("---------------------------------------------------------------------------------------------------- \n\n");
                 printf("***** PLEASE USE THE FOLLOWING COMMANDS: tree, list, path or exit ***** \n\n");
		}
		else if(strcmp(arg[0], "path") == 0) //when user types "path", it will execute path() command and save it to history.txt file
		{
			//write argument to history.txt file
			if(write(historyFD, arg[0], strlen(arg[0])) < 0)
			{
				printf("Error writing to history.txt");
				perror("write");
				return;
			}
			
			if(write(historyFD, "\n", 1) < 0)
			{
				printf("Error writing to history.txt");
				perror("write");
				return;
			}
			
			printf("---------------------------------------------------------------------------------------------------- \n\n");
			printf("Executing path command...\n\n");
			path(); //executing path() command
			printf("Path command tasks completed. Please, check the folder for changes.\n\n");
			printf("---------------------------------------------------------------------------------------------------- \n\n");
            printf("***** PLEASE USE THE FOLLOWING COMMANDS: tree, list, path or exit ***** \n\n");
		}
		else if(strcmp(arg[0], "exit") == 0) //when user types "exit", it will exit the program and print last 4 commands
		{
			printf("---------------------------------------------------------------------------------------------------- \n\n");
			printf("Executing exit command...\n");
			//printf("(1) List of all content of current directory: ");
			//write argument to history.txt file
			if(write(historyFD, arg[0], strlen(arg[0])) < 0)
			{
				printf("Error writing to history.txt");
				perror("write");
				return;
			}
			
			if(write(historyFD, "\n", 1) < 0)
			{
				printf("Error writing to history.txt");
				perror("write");
				return;
			}

			exitFunction(&done); //executing exit() command
		}

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
	clear(); //executing clear() command
	shell(); //executing shell() command
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
