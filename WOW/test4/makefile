#********************************************************************
#
# Xinyi Wang
# Advanced Operating Systems
# Programming Project #4: Chandy-Misra-Haas's Edge Chasing Algorithm
# Date Assigned: Thursday, April 18, 2013
# Due Date: Thursday, May 2, 2013 by 9:30 a.m. 
# Instructor: Dr. Ajay K. Katangur
#
#********************************************************************
CC=mpicc
CFLAGS=-mpe=mpilog
all: aosproj4
	@echo "	All files have been compiled!"
aosproj4: aosproj4.c
	$(CC) $(CFLAGS) -o aosproj4 aosproj4.c
clean:
	rm -f *.o *.core core aosproj4 *.clog2 *.slog2
	@echo "	The directory have been cleaned!"
