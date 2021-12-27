CC = clang 
CFLAGS = -Wall -Werror -Wextra -Wpedantic

all : gen dec err

gen: gen.o 
	$(CC) -o gen generator.c hamming.c bm.c

gen.o: generator.c hamming.c bm.c
	$(CC) $(CFLAGS) -c generator.c
	$(CC) $(CFLAGS) -c bm.c
	$(CC) $(CFLAGS) -c hamming.c
dec: dec.o 
	$(CC) -o dec decoder.c hamming.c bm.c

dec.o: decoder.c hamming.c bm.c
	$(CC) $(CFLAGS) -c decoder.c
	$(CC) $(CFLAGS) -c bm.c
	$(CC) $(CFLAGS) -c hamming.c

err: err.o 
	$(CC) -o err error.c hamming.c bm.c

err.o: error.c hamming.c bm.c
	$(CC) $(CFLAGS) -c error.c
	$(CC) $(CFLAGS) -c bm.c
	$(CC) $(CFLAGS) -c hamming.c
clean:
	rm -f gen *.o
	rm -f dec *.o
	rm -f err *.o

format:
	$ clang-format -i -style=file generator.c
	$ clang-format -i -style=file decoder.c
	$ clang-format -i -style=file error.c
	$ clang-format -i -style=file bm.c
	$ clang-format -i -style=file hamming.c

