OBJS	= Adafruit_TLC5947.o cube_main.o Cube.o
SOURCE	= Adafruit_TLC5947.cpp cube_main.cpp Cube.cpp
HEADER	= Adafruit_TLC5947.h Cube.h
OUT	= output
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = -lwiringPi

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

Adafruit_TLC5947.o: Adafruit_TLC5947.cpp
	$(CC) $(FLAGS) Adafruit_TLC5947.cpp 

cube_main.o: cube_main.cpp
	$(CC) $(FLAGS) cube_main.cpp 

Cube.o: Cube.cpp
	$(CC) $(FLAGS) Cube.cpp 


clean:
	rm -f $(OBJS) $(OUT)
