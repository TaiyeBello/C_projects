CFLAGS= -Wall -g
CC    = gcc $(CFLAGS)

PROGRAMS = bl_server bl_client 

all: $(PROGRAMS)

server_funcs.o: blather.h server_funcs.c
				$(CC) -c server_funcs.c
				
simpio.o: blather.h simpio.c
				$(CC) -c simpio.c

bl_client.o: blather.h bl_client.c 
				$(CC) -c bl_client.c 

bl_server.o: blather.h bl_server.c 
				$(CC) -c bl_server.c

bl_server: blather.h server_funcs.o bl_server.o
			$(CC) -o bl_server server_funcs.o bl_server.o

bl_client: blather.h bl_client.o simpio.o
			$(CC) -o bl_client bl_client.o simpio.o -lpthread

test: test_blather
	./test_blather.sh

clean:
	rm -f *.o *.fifo $(PROGRAMS) 
