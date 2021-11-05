#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){

    int pid = fork();

    if (pid == -1)
    {
        printf("The call to fork did not work");
        return -1;
    }
    

    if (pid == 0)
    {
    
    FILE *fp=popen("ls -l","r"); //popen() is used so that the program can communicate directly to the
    //shell which will invoke it's ls command and return a file pointer/stream that can be used
    //to read the output of the shell
    char output[100];
    if(fp==NULL) return -1; //In case of error
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
    
    return(0);
    
    

    
}