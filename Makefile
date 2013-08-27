CC = gcc
CFLAGS = -Wall -lncurses
	
main: bbqsystem

install:
	mv bbqsystem /usr/bin/bbqsystem

clean:
	rm /usr/bin/bbqsystem
