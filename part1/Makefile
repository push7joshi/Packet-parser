cc		= gcc
#flags
cflags 	= -g

all: data bit
	
data:
	$(cc) $(cflags) data_sizes.c -o data
bit:
	$(cc) $(cflags) bit_wise.c -o bit

clean:
	rm -rf *.o headers 

