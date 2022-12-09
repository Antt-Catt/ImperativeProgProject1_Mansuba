WIDTH ?= 5
HEIGHT ?= 4
MANSUBA_FLAGS = -DWIDTH=$(WIDTH) -DHEIGHT=$(HEIGHT)
CFLAGS = -Wall -Wextra -std=c99 -g3 $(MANSUBA_FLAGS)
OBJS = src/geometry.o src/world.o src/neighbors.o src/set.o src/movements.o src/achiev1.o

all: clean project test

%.o: %.c
	gcc -c -I src/ $(CFLAGS) $< -o $@

project: $(OBJS) src/project.o
	gcc $(CFLAGS) $(OBJS) src/project.o -o src/project

test: $(OBJS) tst/test.o
	gcc $(CFLAGS) $(OBJS) tst/test.o -o tst/test_project

clean:
	rm -f tst/test_project src/project */*.o */*~
