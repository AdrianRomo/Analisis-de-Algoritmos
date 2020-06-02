CC=gcc

CFLAGS=-Wall -Wextra -Werror -std=c99 -O0 -g

all: testall

search: Search.c
	$(CC) -o search Search.c  $(CFLAGS)

testall: search
	./search

clean:
	rm -rf *.o search
