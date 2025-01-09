#include "serial.h"

int main(int argc, char *argv[]) 
{
  char eingabe[3] = {};
  char c = 0;
  int a = 0;

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

  int cube_buf [54] = {};
  int erg_buf[1024] = {};
  char buf_read[] = {'$','r','e','a','d','_','c','o','l','o','r','!','%'};
  char buf_send[] = {'$','s','e','n','d','_','c','u','b','e','!','%'};
  char buf_rand[] = {'$','r','a','n','d','o','m','!','%'};
  char buf_change[] = {'$','c','h','a','n','g','e','!','%'};


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
  char buf_busy[1] = {};


  int pos = 0;

  printf("Cube einlesen: 1\nGelesenen Cube empfangen: 2\nEmpfangenen Cube anzeigen: 3\nPython-Berechnung: 4\nLoesung senden und ausfuehren: 5\nZufaellig verdrehen: 6\nCube tauschen: 7\nBeenden: 8\n");

  while(1)
  {
    if(fgets(eingabe, sizeof(eingabe), stdin) != NULL)
    {

      a = atoi(eingabe);
      if (a < 1 || a > 8) 
      {
          printf("Ungültige Zahl! Die Zahl muss zwischen 1 und 8 liegen.\n");
      }

      switch(eingabe[0])
      {
        case '1':   write(serial_port, buf_read, sizeof(buf_read));

                  printf("Cube wird eingelesen ...\n");
                  read(serial_port, buf_busy, sizeof(buf_busy));
                  if(buf_busy[0] == 1)
                  {
                    printf("Fertig mit einlesen!\n");
                  }
                  else
                  {
                    printf("Error: Handshake Einlesen\n");
                  }

                  printf("\n");
                  printf("Cube einlesen: 1\nGelesenen Cube empfangen: 2\nEmpfangenen Cube anzeigen: 3\nPython-Berechnung: 4\nLoesung senden und ausfuehren: 5\nZufaellig verdrehen: 6\nCube tauschen: 7\nBeenden: 8\n");

                  break;

        case '2':   write(serial_port, buf_send, sizeof(buf_send));
                  read(serial_port, read_buf, sizeof(read_buf));   
              
                  for(int i=0; i<54; i++)
                  {
                    cube_buf[i] = (int)read_buf[i+6];
                  } 

                  if(cube_buf[0] == 0)
                  {
                    printf("Fehler beim Einlesen oder kein Cube vorhanden\n");
                  }
                  else 
                  {
                    printf("Cube_Array erhalten\n");

                  }  

                  read(serial_port, buf_busy, sizeof(buf_busy));

                  printf("\n");
                  printf("Cube einlesen: 1\nGelesenen Cube empfangen: 2\nEmpfangenen Cube anzeigen: 3\nPython-Berechnung: 4\nLoesung senden und ausfuehren: 5\nZufaellig verdrehen: 6\nCube tauschen: 7\nBeenden: 8\n");

                  break;

        case '3': pos = 0;
                  if(cube_buf[0] == 0)
                  {
                      printf("Kein Cube vorhanden oder fehlerhaft eingelesen!\n");
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

                  fflush(stdin);
                  
                  printf("\n");
                  printf("Cube einlesen: 1\nGelesenen Cube empfangen: 2\nEmpfangenen Cube anzeigen: 3\nPython-Berechnung: 4\nLoesung senden und ausfuehren: 5\nZufaellig verdrehen: 6\nCube tauschen: 7\nBeenden: 8\n");
                  break;

        case '4': for(int i=0; i<1024; i++)
                  {
                    erg_buf[i] = 0;
                  }

                  printf("Berechnung startet..\n");
                  fork_and_send(cube_buf, erg_buf, script_name); 
                  printf("Berechnung beendet!\n");
                
                  for (int i = 0; i < 1024; i++) 
                  {
                    //printf("%d ", erg_buf[i]);
                    buf_solve[i+7] = erg_buf[i];
                  } 

                  printf("\n");
                  printf("Cube einlesen: 1\nGelesenen Cube empfangen: 2\nEmpfangenen Cube anzeigen: 3\nPython-Berechnung: 4\nLoesung senden und ausfuehren: 5\nZufaellig verdrehen: 6\nCube tauschen: 7\nBeenden: 8\n");

                  break;

        case '5':   write(serial_port, buf_solve, sizeof(buf_solve));

                  printf("Roboter dreht ...\n");
                  read(serial_port, buf_busy, sizeof(buf_busy));
                  if(buf_busy[0] == 1)
                  {
                    printf("Fertig geloest!\n");
                  }
                  else
                  {
                    printf("Error: Handshake Solve\n");
                  }

                  printf("\n");
                  printf("Cube einlesen: 1\nGelesenen Cube empfangen: 2\nEmpfangenen Cube anzeigen: 3\nPython-Berechnung: 4\nLoesung senden und ausfuehren: 5\nZufaellig verdrehen: 6\nCube tauschen: 7\nBeenden: 8\n");
                            
                  break;

        case '6':   write(serial_port, buf_rand, sizeof(buf_rand));

                  printf("Cube wird verdreht...\n");
                  read(serial_port, buf_busy, sizeof(buf_busy));
                  if(buf_busy[0] == 1)
                  {
                    printf("Fertig verdreht!\n");
                  }
                  else
                  {
                    printf("Error: Handshake Random\n");
                  }
                  

                  printf("\n");
                  printf("Cube einlesen: 1\nGelesenen Cube empfangen: 2\nEmpfangenen Cube anzeigen: 3\nPython-Berechnung: 4\nLoesung senden und ausfuehren: 5\nZufaellig verdrehen: 6\nCube tauschen: 7\nBeenden: 8\n");

                  break;  

        case '7': write(serial_port, buf_change, sizeof(buf_change));

                  printf("Cube wird getauscht\n");
                  printf("Bitte am Roboter freigeben!\n");
                  read(serial_port, buf_busy, sizeof(buf_busy));
                  if(buf_busy[0] == 1)
                  {
                    printf("Getauscht und Kalibriert!\n");
                  }
                  else
                  {
                    printf("Error: Handshake Change\n");
                  }

                  printf("\n");
                  printf("Cube einlesen: 1\nGelesenen Cube empfangen: 2\nEmpfangenen Cube anzeigen: 3\nPython-Berechnung: 4\nLoesung senden und ausfuehren: 5\nZufaellig verdrehen: 6\nCube tauschen: 7\nBeenden: 8\n");
                  
                  break; 

        case '8':   close(serial_port);
                  return 0;

        default:  printf("Ungültige Eingabe! Bitte geben Sie eine Zahl ein.\n");  
                  break;
      }
    }
    usleep(1000*100); 
  }

  close(serial_port);
  return 0;
};

/*
void clear_and_printf()
{
  system("clear");
  printf("Cube einlesen: 1\nGelesenen Cube empfangen: 2\nEmpfangenen Cube anzeigen: 3\nPython-Berechnung: 4\nLoesung senden und ausfuehren: 5\nZufaellig verdrehen: 6\nCube tauschen: 7\nBeenden: 8\n");
}
*/