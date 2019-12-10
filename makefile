all: main

main: main.c manejoarch.o pushrelabel.o slist.o
	gcc -g -o main main.c manejoArchivos.c push-relabel.c slist.c -Wall -pedantic

manejoarch.o: manejoArchivos.c
	gcc -g -c manejoArchivos.c -Wall -pedantic -O

pushrelabel.o: push-relabel.c
	gcc -g -c push-relabel.c -Wall -pedantic -O

slist.o: slist.c
	gcc -c slist.c -Wall -pedantic