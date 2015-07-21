#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include<iostream>
#include <ctime>

using namespace std;


string playerName;

void error(const char *);
void sendReadyRequest(char *name);
void parsingMessage(string msg);
string ScissorRockPaperGenerator();
void connect();
void ScissorRockPaperRequest(string SRP);
void ToCharArray(char c[], string s);


char buffer[80];
int sockfd;

/*
 * Function Name: Main
 * Description: 
 *              
 * Return Value Parameter Data Dictionary
 * -----------------------------------
 * 0
 *
 * Reference Parameter Data Dictionary
 * -----------------------------------
 * argc	   int		argument count
 * argv	   char		array of character pointers to the arguments
 *
 * Local Variable Data Dictionary
 * -----------------------------------
 *
 */

int main(int argc, char *argv[]) {

    playerName = argv[0];
    sendReadyRequest(argv[0]);
    return 0;
}

/*
 * Function Name:sendReadyRequest
 * Description: every 1 second the buffer data from the socket is 
 *		requested accepted and received
 *
 * Return Value Parameter Data Dictionary
 * -----------------------------------
 * no return value
 *
 * Reference Parameter Data Dictionary
 * -----------------------------------
 * *name	char	pointer to next in buffer
 *
 * Local Variable Data Dictionary
 * -----------------------------------
 * n	int	level in the buffer array
 * msg  string	value in the buffer
 */

void sendReadyRequest(char *name) {
   //char buffer[80];
    int n;
    //sleep(0.5);
    connect();  //connects to a new server socket

    bzero(buffer, 80); //initializes buffer to zero
    
    strcpy(buffer, name); 
    
    //puts player along with ready state together in buffer
    strncat(buffer, " Ready", strlen(buffer));
    write(sockfd, buffer, strlen(buffer) + 1);
    bzero(buffer, 80);
      // close(sockfd);
    while (1) {
           sleep(1);
     n = read(sockfd, buffer, 80);
       // cout <<buffer <<endl;
        string msg = buffer;
        
            parsingMessage(msg);         
     
    }
    //  write(1, buffer, n);
        close(sockfd);
}

/*
 * Function Name: connect
 * Description: Creates a new socket and connects to the socket
 *
 * Return Value Parameter Data Dictionary
 * -----------------------------------
 * no return value
 *
 * Reference Parameter Data Dictionary
 * -----------------------------------
 *
 * Local Variable Data Dictionary
 * -----------------------------------
 * servlen	int	path address to the socket
 */


void connect() {
	sleep(1);
    struct sockaddr_un serv_addr;
    int servlen;
    //unlink("foo.Socket");
    bzero((char *) &serv_addr, sizeof (serv_addr));
    serv_addr.sun_family = AF_UNIX;
    strcpy(serv_addr.sun_path, "foo.Socket");
    servlen = strlen(serv_addr.sun_path) +
            sizeof (serv_addr.sun_family);
    if ((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
        error("Creating socket");

    if (connect(sockfd, (struct sockaddr *)
            &serv_addr, servlen) < 0)
        error("Connecting");

}

/*
 * Function Name: ScissorsRockPaperRequest
 * Description: Connects to the server and initializes the buffer
 *              to zero in order to insert choice
 *
 * Return Value Parameter Data Dictionary
 * -----------------------------------
 * no return value
 *
 * Reference Parameter Data Dictionary
 * -----------------------------------
 * SRP	string	choice that will be placecd into the array
 *
 * Local Variable Data Dictionary
 * -----------------------------------
 * n    	int     level in the buffer array
 * pName	char	character array to hold name of the player
 * SRPCArray	char	character array to hold RPS choice
 * 
 */


void ScissorRockPaperRequest(string SRP) {
     
    connect();
    bzero(buffer, 80);

    char pName[50];
    char SRPCArray[50];
    ToCharArray(pName, playerName);
    ToCharArray(SRPCArray, SRP);
    //cout <<cArr<<endl;
    strcpy(buffer, pName);
    strcat(buffer, " ");
    strcat(buffer, SRPCArray);
    write(sockfd, buffer, strlen(buffer) + 1);
    // cout <<buffer<<endl;
    //close(sockfd);
}


/*
 * Function Name: ToCharArray
 * Description: formats the string to a char
 *
 * Return Value Parameter Data Dictionary
 * -----------------------------------
 * no return value
 *
 * Reference Parameter Data Dictionary
 * -----------------------------------
 * c	char	array of characters
 * s 	string	buffer items
 *
 * Local Variable Data Dictionary
 * -----------------------------------
 * i   int     incrementing value in buffer s
 *
 */

void ToCharArray(char c[], string s) {

    for (int i = 0; i < (int)s.length(); i++)
        c[i] = s[i];
    c[s.length()] = '\0';
}

/*
 * Function Name: parsingMessage
 * Description: Function that allows the client to get the "go"
 *              or "stop" value
 *
 * Return Value Parameter Data Dictionary
 * -----------------------------------
 * no return value
 *
 * Reference Parameter Data Dictionary
 * -----------------------------------
 * msg	string	Go or Stop request from referee
 *
 * Local Variable Data Dictionary
 * -----------------------------------
 * SRP   string    rock paper or scissors choice
 *
 */

void parsingMessage(string msg) {
    string SRP;
    if (msg == "GO") {
        // cout <<"This is go message"<<endl;
        SRP = ScissorRockPaperGenerator();
        ScissorRockPaperRequest(SRP);
        //cout << SRP << endl;
    } 
    else if(msg == "ST")
    {
        close(sockfd);
       exit(0);
    }
        

}


/*
 * Function Name: ScissorsRockPaperGenerator
 * Description: This function uses a random number generator to 
 *              choose 1 for scissors, 2 for rock and 3 for paper
 *
 * Return Value Parameter Data Dictionary
 * -----------------------------------
 * Rock, Paper, Scissors	string    choice generated randomly	
 *
 * Reference Parameter Data Dictionary
 * -----------------------------------
 *
 * Local Variable Data Dictionary
 * -----------------------------------
 *
 */

string ScissorRockPaperGenerator() {

    struct timeval start;
    gettimeofday(&start, NULL);

    srand(start.tv_usec);
    // cout<<start.tv_usec<<endl;

    int random_integer;
    random_integer = rand() % 3 + 1;
    //cout <<random_integer<<endl;

    if (random_integer == 1)
        return "Scissors";
    if (random_integer == 2)
        return "Rock";
    if (random_integer == 3)
        return "Paper";

return ("a");	
}

/*
 * Function Name: error
 * Description: Funtion used for error checking of pointer to msg
 *
 * Return Value Parameter Data Dictionary
 * --------------------------------------
 * No Return Value
 *
 * Reference Parameter Data Dictionary
 * -------------------------------------
 * *msg    const char   pointer to msg
 *
 * Local Variable Data Dictionary
 * ------------------------------------
 *
 */

void error(const char *msg) {
        perror(msg);
        exit(0);
}
