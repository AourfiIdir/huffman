all: bin/main.exe

bin/main.exe: main.c huffman.c
	gcc -o bin/main.exe main.c huffman.c

