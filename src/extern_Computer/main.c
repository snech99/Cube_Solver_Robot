#include "serial.h"

#define MAX_INPUT 2

int main(int argc, char *argv[]) 
{

  if (argc != 2) 
  {
      fprintf(stderr, "Usage: %s <python_script_name>\n", argv[0]);
      return 1;
  }
    
  char *script_name = argv[1];

  int serial_port = open("/dev/ttyUSB0", O_RDWR);

  if(config_serial(&serial_port) != 0)
  {
      printf("Error in config!\n");
      return 1;
  };

  char buf_input[MAX_INPUT] = {};
  int cube_buf [54] = {};
  int erg_buf[1024] = {};
  char buf_read[] = {'$','r','e','a','d','_','c','o','l','o','r','!','%'};
  char buf_send[] = {'$','s','e','n','d','_','c','u','b','e','!','%'};
  char buf_rand[] = {'$','r','a','n','d','o','m','!','%'};

  char buf_solve[1033] = {};

  buf_solve[0] = '$';
  buf_solve[1] = 's';
  buf_solve[2] = 'o';
  buf_solve[3] = 'l';
  buf_solve[4] = 'v';
  buf_solve[5] = 'e';
  buf_solve[6] = '!';
  buf_solve[1031] = 0;
  buf_solve[1032] = '%';

  char read_buf[61] = {};

  int pos = 0;

  printf("Cube einlesen: 1\nGelesenen Cube empfangen: 2\nEmpfangenen Cube anzeigen: 3\nPython-Berechnung: 4\nLoesung senden und ausfuehren: 5\nZufaellig verdrehen: 6\nBeenden: 7\n");

  while(1)
  {
    fgets(buf_input, MAX_INPUT, stdin);

    switch(buf_input[0])
    {
      case '1':   write(serial_port, buf_read, sizeof(buf_read));
                  break;

      case '2':   write(serial_port, buf_send, sizeof(buf_send));
                  read(serial_port, read_buf, sizeof(read_buf));   
              
                  for(int i=0; i<61; i++)
                  {
                      printf("%d,", (int)read_buf[i]);
                  } 
                  printf("\n");
                  
                  for(int i=0; i<54; i++)
                  {
                    cube_buf[i] = (int)read_buf[i+6];
                  }            

                  break;

      case '3':   if(cube_buf[0] == 0)
                  {
                      printf("There is no Cube!\n");
                      break;
                  }

                  printf("\n");
                  for(int k=0; k<6; k++)
                  {
                    for(int l=0; l<3; l++)
                    {
                      for(int j=0; j<3; j++)
                      {
                        printf("%d",cube_buf[pos]);
                        pos++;
                      }
                      printf("\n");
                    }
                    printf("\n");
                  }
                  break;

      case '4':   for(int i=0; i<1024; i++)
                  {
                    erg_buf[i] = 0;
                  }

                  fork_and_send(cube_buf, erg_buf, script_name); 

          	      for (int i = 0; i < 1024; i++) 
		              {
        	          printf("%d ", erg_buf[i]);
                    buf_solve[i+7] = erg_buf[i];
    	            }  

   		            printf("\n"); 
                  break;

      case '5':   write(serial_port, buf_solve, sizeof(buf_solve));
                  break;

      case '6':   write(serial_port, buf_rand, sizeof(buf_rand));
                  break;  

      case '7':   close(serial_port);
                  return 0;

      default:    
                  break;
    }

    usleep(1000*100); 
  }

  close(serial_port);

  return 0;
};