#Copyright 2020 Radu-Stefan Minea 314CA

CC=gcc
FLAGS = -Wall -Wextra
SRC=playlist.c LinkedList.c utils.c add.c del.c show.c move.c
LIB=*.h
TARGET=tema1

build:
	$(CC) $(FLAGS) $(SRC) $(LIB) -o $(TARGET)
clean:
	rm -f $(TARGET)
	rm *.o
