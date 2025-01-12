/*
*   Gerrit Hinrichs 01.2025
*   github.com/snech99
*
*   Cube_Solver_Robot
*   Header for the USB/UART configuration
*/
#ifndef _SERIAL_H
#define _SERIAL_H

// C library headers
#include <stdio.h>
#include <string.h>
#include <stdint.h> 
#include <stdlib.h>

// Linux headers
#include <fcntl.h>
#include <errno.h> 
#include <termios.h> 
#include <unistd.h> 
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

int config_serial(int*);
int fork_and_send(int[54], int*, char*);

#endif