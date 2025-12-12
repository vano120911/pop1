CC = gcc
CFLAGS = -Wall -Wextra -std=c11

all: bakery_app

bakery_app: main.o bakery.o
	$(CC) $(CFLAGS) -o bakery_app main.o bakery.o

main.o: main.c bakery.h
	$(CC) $(CFLAGS) -c main.c

bakery.o: bakery.c bakery.h
	$(CC) $(CFLAGS) -c bakery.c

clean:
	rm -f *.o bakery_app bakery_data.bin
