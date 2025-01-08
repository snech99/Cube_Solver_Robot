import os
import struct
import random

FIFO_NAME = "myfifo"

def read_from_fifo():
    if not os.path.exists(FIFO_NAME):
        print("FIFO existiert nicht.")
        return

    received_data = []

    with open(FIFO_NAME, 'rb') as fifo:
        while True:
            data = fifo.read(4)
            if len(data) < 4:
                if len(data) != 0:
                    print("Unvollständige Daten empfangen, Abbruch.")
                break 

            num = struct.unpack('i', data)[0]
            received_data.append(num)  

    #print(received_data)

def write_to_fifo(array):
    with open(FIFO_NAME, 'wb') as fifo:
        for num in array:
            fifo.write(struct.pack('i', num))


#Hier die Lösung einfügen
#Rückgabe maximal 1024 Integer-Werte
def solver():
    #Hier Lösungs Algorithmus
    
    #Random Array mit 1024 Zuegen
    erg=[random.randint(1,12) for x in range(1024)]

    #erg = [1,2,3,4,5,6,7,8,9,10,11,12]
    return erg


if __name__ == "__main__":
    read_from_fifo()

    erg = solver()

    write_to_fifo(erg)

