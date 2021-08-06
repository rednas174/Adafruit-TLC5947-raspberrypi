output: example.o Adafruit_TLC5947.o
	g++ example.o Adafruit_TLC5947.o -o output -lwiringPi

tlc5947.o: Adafruit_TLC5947.cpp Adafruit_TLC5947.h
	g++ -c Adafruit_TLC5947.cpp

start.o: example.cpp
	g++ -c example.cpp

clean:
	rm *.o output
