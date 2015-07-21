This folder has the following files:
1. makefile
2. primefib.h
3. primefib.x
4. primefib_client.c
5. primefib_server.c
6. readme.txt



Project2_2:

1. Using RPC to build up the client/server model
2. On the client side, give any positive number to the server side
3. On the server side, calculate the num-th prime number and fibonacci number by the given number
4. Client gets the returned value, and calculate the time take by the server
5. Show the result on client's screen



to generate sample template files for the server and client programs, and a makefile
rpcgen -C -a primefib.x

to complie this program
$make


use two computers penguin.tamucc.edu and clst.tamucc.edu to run the program
Server Side (clst.tamucc.edu)
$primefib_server &

Client Side (penguin.tamucc.edu)
$ primefib_client clst.tamucc.edu x(any positive number)


to clean the directory
$make clean