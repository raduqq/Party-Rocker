#!/bin/bash

build:
	gcc -g -Wall -Wextra main.c utils.c LinkedList.c *.h -o tema1

clean:
	rm tema1
	rm -r out
	rm *.o
