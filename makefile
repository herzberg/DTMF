CC = gcc
CFLAGS = -wall

all: dtmf
	./dtmf
	
dtmf: dtmf.o dsplib.o
	$(CC) $(CFLAGS) -o dtmf dtmf.o dsplib.o
	
dtmf.o: dtmf.c dsplib.h
	$(CC) $(CFLAGS) -c dtmf.c
	
dsplib.o: dsplib.c dsplib.h
	$(CC) $(CFLAGS) -c dsplib.c

	