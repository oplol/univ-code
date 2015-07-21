This folder has the following files:
1. aosproj1_1.c
2. aosproj1_1.pdf
3. aosproj1_1.xlsx
4. aosproj1_2.c
5. aosproj1_2.pdf
6. makefile
7. readme.txt



Project1_1: 

1. Using MPI to find the message latency and the bandwidth of the network
2. Calculate the average message passing time for a message of length "n", and "n" is between 0 and 1 MB
3. Record the data as a table and create a excel file to show a plot of time vs message size
4. Calculate the parameters according to the equation t = a + n/b
5. Show the result in jumpshot


Project1_2:

1. Using MPI to play a rock-paper-scissors tournament
2. Given any number of processes, randomize the choice of each process before the start of first round
3. The winners of these contests compete in pairs, left-to-right, until a final winner emerges victorious
4. Announce the winner of each competition, and the winner of the whole tournament
5. Show the result in jumpshot



to complie this program
$make

to run the project1_1
$mpirun -np 2 aosproj1_1

to run the project1_2
$mpirun -np 5 aosproj1_2

to clean the directory
$make clean