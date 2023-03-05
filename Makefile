OBJS	= client.o communication.o serialization.o server.o serialization.o interface.o
OUT	= client, server

OBJS0	= client.o communication.o serialization.o interface.o
SOURCE0	= client.c communication.c serialization.c interface.o
HEADER0	= communication.h serialization.h interface.h
OUT0	= client

OBJS1	= server.o serialization.o
SOURCE1	= server.c serialization.c
HEADER1	= serialization.h
OUT1	= server

CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: client server

client: $(OBJS0) $(LFLAGS)
	$(CC) -g $(OBJS0) -o $(OUT0)

server: $(OBJS1) $(LFLAGS)
	$(CC) -g $(OBJS1) -o $(OUT1)

client.o: client.c
	$(CC) $(FLAGS) client.c 

communication.o: communication.c
	$(CC) $(FLAGS) communication.c 

server.o: server.c
	$(CC) $(FLAGS) server.c 

serialization.o: serialization.c
	$(CC) $(FLAGS) serialization.c 

interface.o: interface.c
	$(CC) $(FLAGS) interface.c

clean:
	rm -f $(OBJS) $(OUT)
