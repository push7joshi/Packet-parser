cc		= /usr/bin/gcc
#flags
cflags 	= -g
LIBS 	= -lpcap

all:
	$(cc) $(cflags) $(LIBS) packet_headers.c -o headers

clean:
	rm -rf *.o headers 

