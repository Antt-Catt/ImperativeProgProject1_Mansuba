WIDTH ?= 5
HEIGHT ?= 4
MANSUBA_FLAGS = -DWIDTH=$(WIDTH) -DHEIGHT=$(HEIGHT)
CFLAGS = -Wall -Wextra -std=c99 -g3 $(MANSUBA_FLAGS)

all: project

%.o: %.c
	gcc -c $(CFLAGS) $<

project: # (Add your dependency here, e.g "project.o")
	# (Add your compile command here, e.g "gcc $(CFLAGS) project.o -o project")

test: # (Add your dependency here, e.g "test.o")
	gcc -c $(CFLAGS) src/geometry.c
	gcc -c $(CFLAGS) src/world.c
	gcc -c $(CFLAGS) src/neighbors.c
	gcc -c $(CFLAGS) tst/test.c
	gcc $(CFLAGS) geometry.o world.o neighbors.o test.o -o tst/test_project
	# (Add your compile command here, e.g "gcc $(CFLAGS) test.o -o test_project")

clean:
	rm -f *.o *~ tst/test_project
