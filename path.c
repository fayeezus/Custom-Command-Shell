// Progga Chowdhury - CSC 332 Group Project
// Assigned File: path.c 

#include <unistd.h>  
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h> 
#include <string.h>
#include <sys/types.h>
#include <errno.h>    

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
