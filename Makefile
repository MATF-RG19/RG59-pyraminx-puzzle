CXX=g++
CFLAGS=-c
LDLIBS=-lglut -lGL -lGLU

PROGRAM=Pyraminx
OBJECTS=main.o Pyramid.o Color.o Triangle.o Point.o RotationConfiguration.o Pyramidix.o

all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(CXX) -o $(PROGRAM) $(OBJECTS) $(LDLIBS)

main.o: main.cpp
	$(CXX) $(CFLAGS) $(LDLIBS) main.cpp
Point.o: Point.cpp
	$(CXX) $(CFLAGS) $(LDLIBS) Point.cpp 
Triangle.o: Triangle.cpp
	$(CXX) $(CFLAGS) $(LDLIBS) Triangle.cpp
Color.o: Color.cpp
	$(CXX) $(CFLAGS) $(LDLIBS) Color.cpp
Pyramid.o: Pyramid.cpp
	$(CXX) $(CFLAGS) $(LDLIBS) Pyramid.cpp
RotationConfiguration.o: RotationConfiguration.cpp
	$(CXX) $(CFLAGS) $(LDLIBS) RotationConfiguration.cpp
Pyramidix.o: Pyramidix.cpp
		$(CXX) $(CFLAGS) $(LDLIBS) Pyramidix.cpp
clean:
	rm -rf *o program

