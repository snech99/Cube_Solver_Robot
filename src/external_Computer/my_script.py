
#
#  Gerrit Hinrichs 01.2025
#  github.com/snech99
#
#  Cube_Solver_Robot
#  Python-Script for the Solving-Algorithm
#  Inter-Process-Communication (IPC) with C Program
#

import os
import struct
import random

FIFO_NAME = "myfifo"

# read from the FIFO (IPC)
def read_from_fifo():
    if not os.path.exists(FIFO_NAME):
        print("FIFO doesn't exist.")
        return

    received_data = []

    with open(FIFO_NAME, 'rb') as fifo:
        while True:
            data = fifo.read(4)
            if len(data) < 4:
                if len(data) != 0:
                    print("Terminating due FIFO read")
                break 

            num = struct.unpack('i', data)[0]
            received_data.append(num)  

# write the solution to the FIFO (IPC)
def write_to_fifo(array):
    with open(FIFO_NAME, 'wb') as fifo:
        for num in array:
            fifo.write(struct.pack('i', num))

# Write your own Solver here (max. 1024 moves)
def solver():
    
    #random array with 1024 moves
    erg=[random.randint(1,12) for x in range(1024)]
    return erg

# main function
if __name__ == "__main__":
    read_from_fifo()
    erg = solver()
    write_to_fifo(erg)