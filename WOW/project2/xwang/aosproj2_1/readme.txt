This folder has the following files:
1. aosproj2_1.c
2. aosproj2_1.pdf
3. makefile
4. readme.txt



Project2_1: 

1. Using MPI to simulate the tokenring
2. Sending two tokens from rank 0 in the clock-wise and the counter clock-wise directions
3. In the clock-wise direction, token increases from 0 to rounds*size-1
4. In the counter clock-wise direction, token decreases from rounds*size to 1
5. Show the result in jumpshot



to complie this program
$make

to run the project2_1
$mpirun -np 4 aosproj2_1 n(number of rounds)

to clean the directory
$make clean