WIDTH ?= 5
HEIGHT ?= 4
MANSUBA_FLAGS = -DWIDTH=$(WIDTH) -DHEIGHT=$(HEIGHT)
CFLAGS = -Wall -Wextra -std=c99 -g3 $(MANSUBA_FLAGS)
TFLAGS = -Wall -Wextra -std=c99 -g3 -DWIDTH=5 -DHEIGHT=4
OBJS = src/geometry.o src/world.o src/neighbors.o src/set.o src/movements.o src/victory.o src/game.o src/achiev1.o src/achiev3.o src/achiev4.o src/interface.o

all: clean project test

%.o: %.c
	gcc -c -I src/ $(CFLAGS) $< -o $@

project: clean $(OBJS) src/project.o
	gcc $(CFLAGS) $(OBJS) src/project.o -o src/project

test_project: $(OBJS) tst/test.o
	gcc $(TFLAGS) $(OBJS) tst/test.o -o tst/test_project

test: clean test_project
	./tst/test_project

clean:
	rm -f tst/test_project src/project */*.o */*~
