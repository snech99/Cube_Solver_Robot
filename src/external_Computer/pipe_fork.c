/*
*   Gerrit Hinrichs 01.2025
*   github.com/snech99
*
*   Cube_Solver_Robot
*   fork() for the Python-Script and Inter-Processs-Communication (IPC)
*/

#include "serial.h"

// function to get the child-status from fork()
void child_status (int status)
{						
	if (WIFEXITED(status)==1)
	{
	}

	else if (WIFSIGNALED(status)==1) 
	{
		printf("abnormal termination\n");
		printf("Signalnumber: %d\n",WTERMSIG(status));
	}

	else 
	{
		printf("unknown termination\n");
	}
}

// fork for Python-Script and IPC
int fork_and_send (int array[54], int *erg, char* name)
{
	int fd;
	int status;
    char * myfifo = "myfifo";
	pid_t childpid;
	int ok = 1;
	int idx = 0;

	// open FIFO
    if (mkfifo(myfifo, 0666) == -1)
    {
        if (errno != EEXIST)
        {
            perror("fifo");
			return 1;
        }
    }

	childpid=fork();	//Prozess dublizieren

	switch (childpid)
	{
		case -1:	perror("forken:");  
					return 1;

		// child Process 
		case  0:	if ( execlp("python3", "python3", name, NULL) == -1)
					{
						perror("exec:");
					}	
					exit(EXIT_SUCCESS);

		// parent Process
		default:	// write to the FIFO
					fd = open(myfifo, O_WRONLY);
					if (fd == -1) 
					{
						perror("open");
						return 1;
					}

					if (write(fd, array, 54 * sizeof(int)) == -1) 
					{
						perror("write array");
						close(fd);
						return 1;
					}
					close(fd);

					// read the solution from the FIFO (max 1024 Integer)
					fd = 0;
					fd = open(myfifo, O_RDONLY);
					if (fd == -1) 
					{
						perror("open");
						return 1;
					}

					while(ok)
					{
						int num;
						ssize_t bytes_read = read(fd, &num, sizeof(num));

						if (bytes_read < sizeof(num)) 
						{
							if (bytes_read == 0) 
							{
								ok = 0;
							} 
							else 
							{
								printf("Incomplete data received, abort\n");
								ok = 0;
							}
							break;
						}

						if(idx < 1024)
						{
							erg[idx] = num;
							idx++;
						}		
						else
						{
							printf("To many numbers where send by Python-Script!");
						}				
					}

					close(fd);	
					wait(&status);
					child_status(status);
	}	
	return 0;
}
