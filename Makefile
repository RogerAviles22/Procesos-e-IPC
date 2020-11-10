all: build build/main

#target: prerequisites
build: 
	 mkdir -p build

build/main: main.o
	 gcc main.o -o build/main 

main.o: main.c
	 gcc -c main.c

clean:
	 rm *.o ./build/*
