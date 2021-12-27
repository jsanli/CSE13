CC = clang 
CFLAGS = -Wall -Werror -Wextra -Wpedantic

all : banhammer 

banhammer: banhammer.o 
	$(CC) -o banhammer banhammer.c speck.c hash.c ll.c node.c bf.c bv.c parser.c

banhammer.o: banhammer.c speck.c hash.c ll.c node.c bf.c bv.c parser.c
	$(CC) $(CFLAGS) -c banhammer.c
	$(CC) $(CFLAGS) -c speck.c
	$(CC) $(CFLAGS) -c hash.c
	$(CC) $(CFLAGS) -c ll.c
	$(CC) $(CFLAGS) -c node.c
	$(CC) $(CFLAGS) -c bf.c
	$(CC) $(CFLAGS) -c bv.c
	$(CC) $(CFLAGS) -c parser.c
clean:
	rm -f banhammer *.o

format:
	$ clang-format -i -style=file banhammer.c
	$ clang-format -i -style=file speck.c
	$ clang-format -i -style=file hash.c
	$ clang-format -i -style=file ll.c
	$ clang-format -i -style=file node.c
	$ clang-format -i -style=file bf.c
	$ clang-format -i -style=file bv.c
	$ clang-format -i -style=file parser.c

