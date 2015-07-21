#********************************************************************
#
# Xinyi Wang
# Advanced Operating Systems
# Programming Project #1: Basic MPI Communication
# Date Assigned: Thursday, February 21, 2013
# Due Date: Thursday, March 7, 2013 by 9:30 a.m.
# Instructor: Dr. Ajay K. Katangur
#
#********************************************************************
CC=mpicc
CFLAGS=-mpe=mpilog
all: aosproj1_1 aosproj1_2
	@echo "	All files have been compiled!"
aosproj1_1: aosproj1_1.c
	$(CC) $(CFLAGS) -o aosproj1_1 aosproj1_1.c
aosproj1_2: aosproj1_2.c
	$(CC) $(CFLAGS) -o aosproj1_2 aosproj1_2.c
clean:
	rm -f *.o *.core core aosproj1_1 aosproj1_2 aosproj1_1.txt *.clog2 *.slog2
	@echo "	The directory have been cleaned!"
