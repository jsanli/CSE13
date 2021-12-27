CC = clang 
CFLAGS = -Wall -Werror -Wextra -Wpedantic

all : sorting

sorting: sorting.o 
	$(CC) -o sorting sorting.c bubble.c shell.c quick.c stack.c heap.c set.c

sorting.o: sorting.c bubble.c shell.c quick.c stack.c heap.c set.c
	$(CC) $(CFLAGS) -c sorting.c
	$(CC) $(CFLAGS) -c bubble.c
	$(CC) $(CFLAGS) -c shell.c
	$(CC) $(CFLAGS) -c quick.c
	$(CC) $(CFLAGS) -c stack.c
	$(CC) $(CFLAGS) -c heap.c
	$(CC) $(CFLAGS) -c set.c
clean:
	rm -f sorting *.o

format:
	$ clang-format -i -style=file sorting.c
	$ clang-format -i -style=file bubble.c
	$ clang-format -i -style=file shell.c
	$ clang-format -i -style=file quick.c
	$ clang-format -i -style=file stack.c
	$ clang-format -i -style=file heap.c
	$ clang-format -i -style=file set.c

