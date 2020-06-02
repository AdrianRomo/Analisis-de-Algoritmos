CC=gcc

CFLAGS=-Wall -Wextra -Werror -std=c99 -O0 -g

all: testall

Multiply: multiply.c
	$(CC) -o Multiply multiply.c  $(CFLAGS)

testall: Multiply
	./Multiply

clean:
	rm -rf *.o Multiply
