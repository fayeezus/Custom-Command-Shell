#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    // Create Dir0 with
    mkdir("Dir0", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    chdir("Dir0"); //changing directory to Dir0;

    //creating 3 txt files;
    int t1 = open("t1.txt", O_RDWR | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
    int t2 = open("t2.txt", O_RDWR | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
    int t3 = open("t3.txt", O_RDWR | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);

    mkdir("Dir1", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH); //making Dir1 inside Dir0;
    //printf("All the tasks are complete \n");
    return 0;
}
