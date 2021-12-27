CC = clang 
CFLAGS = -Wall -Werror -Wextra -Wpedantic

all : encode decode

encode: encode.o 
	$(CC) -o encode encode.c trie.c word.c io.c -lm

encode.o: encode.c trie.c word.c io.c
	$(CC) $(CFLAGS) -c encode.c
	$(CC) $(CFLAGS) -c trie.c
	$(CC) $(CFLAGS) -c word.c
	$(CC) $(CFLAGS) -c io.c

decode: decode.o 
	$(CC) -o decode decode.c trie.c word.c io.c -lm

decode.o: decode.c trie.c word.c io.c
	$(CC) $(CFLAGS) -c decode.c
	$(CC) $(CFLAGS) -c trie.c
	$(CC) $(CFLAGS) -c word.c
	$(CC) $(CFLAGS) -c io.c
 
clean:
	rm -f encode *.o
	rm -f decode *.o

format:
	$ clang-format -i -style=file encode.c
	$ clang-format -i -style=file decode.c
	$ clang-format -i -style=file trie.c
	$ clang-format -i -style=file word.c
	$ clang-format -i -style=file io.c
