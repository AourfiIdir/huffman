all:bin/main.exe



bin/main.exe:huffman.c main.c
	gcc huffman.c main.c -o bin/main     -Iinclude     -I$(HOME)/c/libs/raylib/installed/include     -L$(HOME)/c/libs/raylib/installed/lib     -lraylib -lm -ldl -lrt -pthread -lGL -lX11 -lXrandr -lXi
