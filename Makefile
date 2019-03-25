CC = gcc

PREFIX = /usr
INCLUDE = $(PREFIX)/include
CFLAGS = -D_SHARED_MEMORY -D_REENTRANT -D_THREAD_SAFE -I$(INCLUDE) -I$(INCLUDE)/SDL2 -I. -lSDL2 -lSDL2_ttf


pong: pong.o
	$(CC) $(CFLAGS) -o pong pong.o


debug: pong.o
	$(CC) $(CFLAGS) -g -o pong pong.c


clean:
	rm -f pong.o pong; $(MAKE) pong
