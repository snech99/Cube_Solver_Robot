import os
import struct

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

    print(received_data)

def write_to_fifo(array):
    with open(FIFO_NAME, 'wb') as fifo:
        for num in array:
            fifo.write(struct.pack('i', num))


#Hier die Lösung einfügen
#Rückgabe maximal 245 Integer-Werte
def solver():

    #Hier Lösungs Algorithmus
    erg = [11,12,13,14,15,16,17,18,19,20,21,22,23]
    return erg


if __name__ == "__main__":
    read_from_fifo()

    erg = solver()

    write_to_fifo(erg)

