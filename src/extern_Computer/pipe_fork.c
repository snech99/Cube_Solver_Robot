#include "serial.h"

//Funktion zum Auswerten des Status von wait()
void child_status (int status)
{						
	//Normale Terminierung
	if (WIFEXITED(status)==1)
	{
	}
	//Abnormale Terminierung
	else if (WIFSIGNALED(status)==1) 
	{
		printf("Kind abnormal terminiert.\n");
		printf("Signalnummer: %d\n",WTERMSIG(status));
	}
	//Sonstige unbekannte Terminierung
	else 
	{
		printf("Unbekannte Terminierung");
	}
}

int fork_and_send (int array[54], int *erg, char* name)
{
	int fd;
	int status;
    char * myfifo = "myfifo";
	pid_t childpid;
	int ok = 1;
	int idx = 0;

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
		case -1:	perror("forken:");   //Fehlerbehandlung fork
					return 1;

		//Kindprozess	 
		case  0:	if ( execlp("python3", "python3", name, NULL) == -1)
					{
						perror("exec:");
					}	
					exit(EXIT_SUCCESS);

		//Elternprozess
		default:	fd = open(myfifo, O_WRONLY);
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

						// Wenn weniger als 4 Bytes gelesen wurden, ist das Ende der FIFO erreicht
						if (bytes_read < sizeof(num)) 
						{
							if (bytes_read == 0) 
							{
								ok = 0;
							} 
							else 
							{
								printf("Unvollständige Daten empfangen, Abbruch.\n");
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
