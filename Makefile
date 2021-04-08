CFLAGS=-DGL_SILENCE_DEPRECATION $(shell pkg-config --cflags gl) $(shell pkg-config --cflags glut)
LIBS=$(shell pkg-config --libs gl) $(shell pkg-config --libs glut)

all:
	g++ -o geometry ./FemboyGeometry/*.cpp $(CFLAGS) $(LIBS)

clean:
	rm -f geometry
