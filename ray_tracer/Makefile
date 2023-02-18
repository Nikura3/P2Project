CC = g++
CFLAGS = -Wall -g
OBJS = tracer.o smartP.o point.o node.o list.o point.o shape.o sphere.o realistic_sphere.o toon_sphere.o realistic_cube.o toon_cube.o cube.o math_utilities.o

Ray_tracer: main.o $(OBJS)
	$(CC) $^ -o $@ $(CFLAGS)
main.o: main.cpp
	$(CC) -c $< $(CFLAGS)
%.o: %.cpp %.h
	$(CC) -c $< $(CFLAGS)

.PHONY: clean
clean:
	rm *.o
