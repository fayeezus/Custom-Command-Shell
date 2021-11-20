// Progga Chowdhury - CSC 332 Group Project
// Assigned File: path.c 

#include <unistd.h>  
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h> 
#include <string.h>
#include <sys/types.h>
#include <errno.h>    

int main (int argc, char **argv) {
  FILE * t2_file = fopen("t2.txt", "w+"); // open the file t2.txt in reading and writing mode
  printf("---------------------------------------------------------------------------------------------------- \n\n");                                   
  
  char content[1024]; // this array is used to store the contents of directory 
   if (getcwd(content, sizeof(content)) != NULL) { // the getcwd() functions gets the path name of the current working directory
      fputs(content, t2_file); // the fputs() function will write an array of characters to a file 
      fclose(t2_file); // close the t2.txt file 
      printf("(1) Wrote the path of the current directory to the terminal & t2.txt \n\n---> PATH OF CURRENT DIRECTORY: %s \n\n", content); // 1. print current working directory path to txt2.c & ternimal 
      
      rename("t2.txt", "path.txt"); // 2. change name of text file "t2.txt" into "path.txt"
      printf("(2) Renamed the file t2.txt into path.txt \n\n"); // print that t2.txt file was renamed to path.txt

      // open the necessary files to be used in concatenation later
      FILE* tree_file = fopen("tree.txt", "r"); // open tree.txt 
	    FILE* path_file = fopen("path.txt", "r"); // open path.txt 
	    FILE* t3_file = fopen("t3.txt", "a"); // open t3.txt 
      
      char concatenate; // 3. concatenate content of tree.txt & path.txt into t3.txt
      if (tree_file == NULL || t3_file == NULL) { // if the files are not found / do not exist
      perror("ERROR: OPENING FILES \n\n"); // print this error message 
      exit(0); // and then exit 
      }
      concatenate = fgetc(tree_file); // this handles concatenation of tree.txt into t3.txt 
      while (concatenate != EOF) { // EOF implies until the end of the file
        fputc(concatenate, t3_file); // fputc() will write a single character at a time to the provided file 
        concatenate = fgetc(tree_file); // fgetc() will to read the content of a file, one character at a time
      }
      concatenate = fgetc(path_file); // this handles concatenation of path.txt into t3.txt
      while (concatenate != EOF) { // EOF implies until the end of the file
        fputc(concatenate, t3_file); // fputc() will write a single character at a time to the provided file 
        concatenate = fgetc(path_file); // fgetc() will to read the content of a file, one character at a time
      }
      
      printf("(3) Concatenated the content of tree.txt & path.txt into t3.txt \n\n"); // print that concatenation was successful 
      rename("t3.txt", "log.txt"); // 4. change the neme of t3.txt into log.txt 
      printf("(4) Renamed the file t3.txt into log.txt \n\n"); /// print that t3.txt file was renamed to log.txt
      remove("tree.txt"); // 5. delete tree.txt
      remove("path.txt"); // 5. delete path.txt
      printf("(5) Deleted files tree.txt & path.txt \n\n"); // print that the files tree.txt & path.txt were deleted successfully
      printf("---------------------------------------------------------------------------------------------------- \n\n");                                   

   } else { // else, if the current directory was unable to be accessed (getcwd error)... 
       perror("ERROR: CURRENT DIRECTORY PATH \n\n"); // print this error message
       return 1;
   }

   return 0;
}