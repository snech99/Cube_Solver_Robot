#ifndef _SERIAL_H
#define _SERIAL_H

// C library headers
#include <stdio.h>
#include <string.h>
#include <stdint.h> 
#include <stdlib.h>

// Linux headers
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

int config_serial(int*);
int fork_and_send(int[54], int*, char*);

#endif