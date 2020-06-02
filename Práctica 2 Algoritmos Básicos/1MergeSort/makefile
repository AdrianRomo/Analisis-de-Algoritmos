CC=gcc

CFLAGS=-Wall -Wextra -Werror -std=c99 -O0 -g

all: testall

Merge: merge.c
	$(CC) -o Merge merge.c  $(CFLAGS)

testall: Merge
	./Merge

clean:
	rm -rf *.o Merge
