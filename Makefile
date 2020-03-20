#!/bin/bash

build:
	gcc main.c utils.c LinkedList.c *.h -o rocker

clean:
	rm rocker
	rm media.out
	touch media.out

run:
	./rocker media.in media.out
