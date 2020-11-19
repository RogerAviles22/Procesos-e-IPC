all: build build/mishell

#target: prerequisites
build: 
	 mkdir -p build

build/mishell: mishell.o
	 gcc mishell.o -o build/mishell 

mishell.o: mishell.c
	 gcc -c mishell.c

clean:
	 rm *.o ./build/*
