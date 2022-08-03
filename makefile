OBJS	= TLC_5947.o cube_main.o Cube.o
SOURCE	= TLC_5947.cpp cube_main.cpp Cube.cpp
HEADER	= TLC_5947.h Cube.h
OUT	= output
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = -lwiringPi -lpthread

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

TLC_5947.o: TLC_5947.cpp
	$(CC) $(FLAGS) TLC_5947.cpp 

cube_main.o: cube_main.cpp
	$(CC) $(FLAGS) cube_main.cpp 

Cube.o: Cube.cpp
	$(CC) $(FLAGS) Cube.cpp 


clean:
	rm -f $(OBJS) $(OUT)
