#
# Makefile
#
# Computer Science 50
# Problem Set 6
#


# compiler to use
CC = clang
# CC = gcc

# flags to pass compiler
# CFLAGS = -ggdb3 -O0 -Qunused-arguments -std=c99 -Wall -Werror
CFLAGS = -ggdb3 -O0 -Qunused-arguments -std=c99 -Wall

# name for executable
EXE = server

# space-separated list of header files
HDRS =

# space-separated list of libraries, if any,
# each of which should be prefixed with -l
LIBS = -lc -lm

# space-separated list of source files
SRCS = server.c

# automatically generated list of object files
OBJS = $(SRCS:.c=.o)


# default target
$(EXE): $(OBJS) $(HDRS) Makefile
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

# dependencies 
$(OBJS): $(HDRS) Makefile

# housekeeping
clean:
	@rm -f core $(EXE) *.o
