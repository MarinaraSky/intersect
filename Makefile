CC = gcc
PROGRAMS = intersect
CFLAGS = $(CF) -Wall -Wextra -Wpedantic 
DEBUG_FLAGS = -g
PROFILE_FLAGS = -pg


intersect: intersect.a driver.c
	$(CC) $(CFLAGS) -o $(PROGRAMS) *.c

profile: intersect.a driver.c
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(PROFILE_FLAGS) -o $(PROGRAMS) *.c
intersect_bst.o: intersect_bst.h intersect_bst.c

intersect.a: intersect_bst.o
	ar r intersect.a intersect_bst.o

debug:
	$(CC) $(DEBUG_FLAGS) $(CFLAGS) -o $(PROGRAMS) *.c
clean:
	@rm -f $(PROGRAMS) *.o *.a *.h.gch *.out


