CC = gcc
CFLAGS = -Wall

all: ms2401_sim

ms2401_sim: MS2401_main.c MS2401_fun.c
	$(CC) $(CFLAGS) MS2401_main.c MS2401_fun.c -o ms2401_sim

clean:
	rm -f ms2401_sim

