CC=gcc

CFLAGS=-Wall -Wextra -Werror -std=c99 -O0 -g

all: testall

ClosestPoints: ClosestPoints.c
	$(CC) -o ClosestPoints ClosestPoints.c  $(CFLAGS)

testall: ClosestPoints
	./ClosestPoints

clean:
	rm -rf *.o ClosestPoints
