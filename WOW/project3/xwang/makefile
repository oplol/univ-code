#********************************************************************
#
# Xinyi Wang
# Advanced Operating Systems
# Programming Project #3: Logical and Vector Clocks
# Date Assigned: Thursday, March 28, 2013
# Due Date: Due Date: Thursday, April 11, 2013 by 9:30 a.m. 
# Instructor: Dr. Ajay K. Katangur
#
#********************************************************************
CC=mpicc
CFLAGS=-mpe=mpilog
all: aosproj3_1 aosproj3_2
	@echo "	All files have been compiled!"
aosproj3_1: aosproj3_1.c
	$(CC) $(CFLAGS) -o aosproj3_1 aosproj3_1.c
aosproj3_2: aosproj3_2.c
	$(CC) $(CFLAGS) -o aosproj3_2 aosproj3_2.c
clean:
	rm -f *.o *.core core aosproj3_1 aosproj3_2 *.clog2 *.slog2
	@echo "	The directory have been cleaned!"
