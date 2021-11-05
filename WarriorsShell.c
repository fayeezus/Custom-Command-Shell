***************************************************************************************************************************************************************
  FAROUQ ADEPETU fadepet000@citymail.cuny.edu
               EXIT

	char* scriptFileName = "history.h";
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
		return 1;
	}

	//close history.h
	if(close(scriptFD) < 0)
	{
		printf("Failed to close history.h\n");
		perror("close");
		return 1;
	}

******************************************************************************************************************************************




***********************************************************************
 FAROUQ ADEPETU fadepet000@citymail.cuny.edu
               EXIT
	These two write functions need to be put
	after a sucessfull command is read from user
	input so it can be written to the history.txt
	file 

	//write command to history.txt file
	write(historyFD, command, strlen(command));
	write(historyFD, "\n", 1);

**********************************************************************







**********************************************************************************************************
FAROUQ ADEPETU fadepet000@citymail.cuny.edu
               EXIT

	//if command is exit then
	//exit loop
	if(strcmp(command, "exit") == 0)
	{
		int pid = fork(); //create a child process
		int status = 0;
		
		//if error creating child process
		//exit program
		if(pid < 0)
		{
			//close file
			//b4 exiting program
			close(historyFD);
			printf("Error in creating a child process\n");
			perror("fork");
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
				close(historyFD);
				perror("execlp");
				exit(EXIT_FAILURE);
			}
		}

		//wait for child process to finish
		//executing
		//if error exit program
		if(waitpid(pid, &status, 0) != pid)
		{
			//close file b4 exiting child process
			close(historyFD);
			perror("waitpid");
			return 1;
		}

		pid = fork(); //create child process

		if(pid < 0)
		{
			//close file
			//b4 exiting program
			close(historyFD);
			printf("Error in creating a child process\n");
			perror("fork");
			return 1;
		}
		else if(pid == 0) //in child process
		{
			printf("\n");
			//excute ls -l
			//if error exit child process
			if(execlp("ls", "ls", "-l", (char*) NULL) < 0)
			{
				//close file b4 exiting
				//child process
				close(historyFD);
				perror("execlp");
				exit(EXIT_FAILURE);
			}
		}
		
		//wait for child process to finish
		//executing
		//if error exit program
		if(waitpid(pid, &status, 0) != pid)
		{
			//close file b4 exiting child process
			close(historyFD);
			perror("waitpid");
			return 1;
		}

		//close history.txt
		//if error exit program
		if(close(historyFD) < 0)
		{
			printf("Failed to close history.txt\n");
			perror("close");
			return 1;
		}

		printf("\nPress ENTER or RETURN to exit shell: ");

		//loop to make sure
		//program exits when ENTER or RETURN is hit
		//from user
		while(getchar() != '\n');

		done = true; //done = true will exit while loop and in turn program will exit
*****************************************************************************************************************************

