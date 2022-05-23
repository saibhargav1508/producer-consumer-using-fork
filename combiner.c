// Sai Bhargav Mandavilli
// University of Florida

// Combiner code using sample codes from 'The Linux Programming Interface'.
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void errExit(char *errorstr)
{
	printf("%s",errorstr);
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    // Pipe file descriptors for readind and writing
	// fd[0] id read end and fd[1] is write end
	int fd[2]; 

    // Create pipe
	if (pipe(fd) == -1)
        errExit("pipe");

    // defining a fork call to handle mapper on the write end of the pipe
	switch (fork()) 
	{
        case -1:
            errExit("fork");

        case 0:  
            if (close(fd[0]) == -1)
                errExit("close read end first");

            if (dup2(fd[1], STDOUT_FILENO) == -1)
                errExit("dup2");

            execlp("./mapper", "./mapper", NULL);
            errExit("execlp mapper");

        default:
            break;
    }

    switch (fork()) 
	{	
		case -1:
            errExit("fork");

        case 0:
            if (close(fd[1]) == -1)
                errExit("close write end first");
            
            if (dup2(fd[0], STDIN_FILENO) == -1) 
                errExit("dup2");

            execlp("./reducer", "./reducer", "-l", (char *) NULL);
            errExit("execlp reducer");

        default:
            break;
    }

    // Parent closes unused file descriptors for pipe
    if (close(fd[0]) == -1)
        errExit("close");
    
    if (close(fd[1]) == -1)
        errExit("close");
    
	// parent waits for children
    if (wait(NULL) == -1)
        errExit("wait");

	if (wait(NULL) == -1)
        errExit("wait");
        
    exit(EXIT_SUCCESS);
}
