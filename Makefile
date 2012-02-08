INC = `sdl-config --cflags` -I/usr/local/include
LIB = `sdl-config --libs` -lpng -L/usr/local/lib
FLAGS = -Wall -g 
CPP=g++
CC=gcc

PROG = sdl-pong
OUT=sdlpong.o \
	SDL_prim.o \
	stars.o  \
	utils.o \
	ball.o \
	board.o \
	stick.o \
	collision.o \
	load_png.o \
	video.o \
	FileObject.o \
	FileFactory.o \
	VirtScreen.o \
	led.o \
	led_panel.o

.SUFFIXES : .c .o .cpp

all: $(OUT)
	$(CPP) $(OUT) $(FLAGS) $(INC) $(LIB) -o $(PROG)
.c.o:
	$(CC) $(INC) $(FLAGS) -c $<
.cpp.o:
	$(CPP) $(INC) $(FLAGS) -c $<

count:
	wc -l *.cpp *.h *.c

clean:
	rm $(OUT) sdl-pong
