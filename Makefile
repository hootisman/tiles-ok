CC = gcc
CFLAGS = -g -Wall -std=c99
LDLIBS = -I. -I../src -L. -L../release/linux -lraylib -lGL  -lm -lpthread -ldl -lX11 -lXrandr -lXinerama -lXi -lXxf86vm -lXcursor 

main: main.o tiles.o

clean:
	rm -rf *.o main
	
