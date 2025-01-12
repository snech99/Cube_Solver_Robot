/*
*   Gerrit Hinrichs 01.2025
*   github.com/snech99
*
*   Cube_Solver_Robot
*   main-file for the USB Communication
*/
#include "serial.h"

int main(int argc, char *argv[]) 
{
  char input[3] = {};
  char c = 0;
  int a = 0;

  //Usage
  if (argc != 2) 
  {
      fprintf(stderr, "Usage: %s <python_script_name>\n", argv[0]);
      return 1;
  }
    
  char *script_name = argv[1];
  int serial_port = open("/dev/ttyUSB0", O_RDWR);

  //Configurate the USB connection with err handling
  if(config_serial(&serial_port) != 0)
  {
    printf("Error in tty config\n");
    return 1;
  };

  int pos = 0;
  int cube_buf [54] = {};
  int erg_buf[1024] = {};
  char buf_solve[1033] = {};
  char read_buf[61] = {};
  char buf_busy[1] = {};

  char buf_read[] = {'$','r','e','a','d','_','c','o','l','o','r','!','%'};
  char buf_send[] = {'$','s','e','n','d','_','c','u','b','e','!','%'};
  char buf_rand[] = {'$','r','a','n','d','o','m','!','%'};
  char buf_change[] = {'$','c','h','a','n','g','e','!','%'};

  buf_solve[0] = '$';
  buf_solve[1] = 's';
  buf_solve[2] = 'o';
  buf_solve[3] = 'l';
  buf_solve[4] = 'v';
  buf_solve[5] = 'e';
  buf_solve[6] = '!';
  buf_solve[1031] = 0;
  buf_solve[1032] = '%';

  printf("Cube scanning: 1\nGet the Cube from Robot: 2\nShow the Cube: 3\nPython-Script: 4\nSend moves and solve: 5\n20 random moves: 6\nChange Cube: 7\nEnd program: 8\n");

  //Super-loop with switch() for the commands
  while(1)
  {
    if(fgets(input, sizeof(input), stdin) != NULL)
    {

      a = atoi(input);

      if (a < 1 || a > 8) 
      {
          printf("Invalid Number! It must be between 1 and 8.\n");
      }

      //Switch() with all the possible Commands for the Robot
      switch(input[0])
      { 
        // Scan Cube
        case '1': write(serial_port, buf_read, sizeof(buf_read));
                  printf("Scanning the Cube...\n");
                  read(serial_port, buf_busy, sizeof(buf_busy));
                  if(buf_busy[0] == 1)
                  {
                    printf("Done with scanning!\n");
                  }
                  else
                  {
                    printf("Error: Handshake Scanning\n");
                  }

                  printf("\n");
                  printf("Cube scanning: 1\nGet the Cube from Robot: 2\nShow the Cube: 3\nPython-Script: 4\nSend moves and solve: 5\n20 random moves: 6\nChange Cube: 7\nEnd program: 8\n");
                  break;

        // Receive the scanned Cube
        case '2': write(serial_port, buf_send, sizeof(buf_send));
                  read(serial_port, read_buf, sizeof(read_buf));   
              
                  for(int i=0; i<54; i++)
                  {
                    cube_buf[i] = (int)read_buf[i+6];
                  } 

                  if(cube_buf[0] == 0)
                  {
                    printf("Error due reading\n");
                  }
                  else 
                  {
                    printf("Cube received!\n");

                  }  

                  read(serial_port, buf_busy, sizeof(buf_busy));

                  printf("\n");
                  printf("Cube scanning: 1\nGet the Cube from Robot: 2\nShow the Cube: 3\nPython-Script: 4\nSend moves and solve: 5\n20 random moves: 6\nChange Cube: 7\nEnd program: 8\n");
                  break;

        // print the received Cube
        case '3': pos = 0;
                  if(cube_buf[0] == 0)
                  {
                      printf("There is no Cube or Error during the scan\n");
                      break;
                  }

                  printf("\n");
                  for(int k=0; k<6; k++)
                  {
                    for(int l=0; l<3; l++)
                    {
                      for(int j=0; j<3; j++)
                      {
                        printf("%d ",cube_buf[pos]);
                        pos++;
                      }
                      printf("\n");
                    }
                    printf("\n");
                  }
                  
                  printf("\n");
                  printf("Cube scanning: 1\nGet the Cube from Robot: 2\nShow the Cube: 3\nPython-Script: 4\nSend moves and solve: 5\n20 random moves: 6\nChange Cube: 7\nEnd program: 8\n");
                  break;

        // Start the Python-Script for Calculation
        case '4': for(int i=0; i<1024; i++)
                  {
                    erg_buf[i] = 0;
                  }

                  printf("Starting Python-Script\n");
                  if( fork_and_send(cube_buf, erg_buf, script_name) != 0)
                  {
                    printf("Error in fork!\n");
                  } 
                  printf("Calculation in Python done!\n");
                
                  for (int i = 0; i < 1024; i++) 
                  {
                    //printf("%d ", erg_buf[i]);
                    buf_solve[i+7] = erg_buf[i];
                  } 

                  printf("\n");
                  printf("Cube scanning: 1\nGet the Cube from Robot: 2\nShow the Cube: 3\nPython-Script: 4\nSend moves and solve: 5\n20 random moves: 6\nChange Cube: 7\nEnd program: 8\n");
                  break;

        // Send the move_array to the Robot
        case '5': write(serial_port, buf_solve, sizeof(buf_solve));
                  printf("Robot is moving ..\n");
                  read(serial_port, buf_busy, sizeof(buf_busy));
                  if(buf_busy[0] == 1)
                  {
                    printf("Solved\n");
                  }
                  else
                  {
                    printf("Error: Handshake Solve\n");
                  }

                  printf("\n");
                  printf("Cube scanning: 1\nGet the Cube from Robot: 2\nShow the Cube: 3\nPython-Script: 4\nSend moves and solve: 5\n20 random moves: 6\nChange Cube: 7\nEnd program: 8\n");                           
                  break;

        // 20 random moves
        case '6': write(serial_port, buf_rand, sizeof(buf_rand));
                  printf("Cube is doing random moves..\n");
                  read(serial_port, buf_busy, sizeof(buf_busy));
                  if(buf_busy[0] == 1)
                  {
                    printf("Done twisting!\n");
                  }
                  else
                  {
                    printf("Error: Handshake random\n");
                  }
                  
                  printf("\n");
                  printf("Cube scanning: 1\nGet the Cube from Robot: 2\nShow the Cube: 3\nPython-Script: 4\nSend moves and solve: 5\n20 random moves: 6\nChange Cube: 7\nEnd program: 8\n");
                  break;  

        // Change Cube
        case '7': write(serial_port, buf_change, sizeof(buf_change));
                  printf("Changing Cube ...\n");
                  printf("Please confirm with the Button at the end!\n");
                  read(serial_port, buf_busy, sizeof(buf_busy));
                  if(buf_busy[0] == 1)
                  {
                    printf("changed and calibrated!\n");
                  }
                  else
                  {
                    printf("Error: Handshake Change\n");
                  }

                  printf("\n");
                  printf("Cube scanning: 1\nGet the Cube from Robot: 2\nShow the Cube: 3\nPython-Script: 4\nSend moves and solve: 5\n20 random moves: 6\nChange Cube: 7\nEnd program: 8\n");                
                  break; 

        // End this program and cole the connection
        case '8': close(serial_port);
                  return 0;

        default:  printf("Invalid Number! It must be between 1 and 8.\n"); 
                  break;
      }

      // deletes queue during a task
      /*
      if (getchar() != NULL)
      {
        while ( getchar() != '\n' )
        {

        }
      }
      */
    }
    //usleep(1000*100); 
  }

  close(serial_port);
  return 0;
};
