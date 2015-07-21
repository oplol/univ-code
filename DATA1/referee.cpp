#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/un.h>
#include <stdio.h>
#include<iostream>
#include<sstream>

using namespace std;

void error(const char *);
void SetReadyState(string s);
void parsingMessage(string s, int newsockfd);
void ScissorRockPaper(string s);

void formatDisplay(string s);
void splitString(string s);
void setAllPlayersInReadyState(string s);
void getWinner();


bool firstPlayerReady; //bool check if server receive request from client
bool secondPlayerReady;

string firstPlayerSRP; //string variable holds first player's guess.
string secondPlayerSRP; // string variable holds second player's guess
int playerOneWinCounter; //count player one win times
int playerTwoWinCounter;//count player two win times
int drawCounter;  //count draw time
int playCounter; //count play times so far
int playTimes;  //total play times
char buf[80];    //for reading and writing of go, ready, rock...etc

/*
 * Function Name: Main
 * Description: Main function for the program that creates the 
 * 		domain socket and initializes the counters
 *              
 * Return Value Parameter Data Dictionary
 * -----------------------------------
 * 0	int	
 *
 * Reference Parameter Data Dictionary
 * -----------------------------------
 * argc	   int
 * argv	   char
 *
 * Local Variable Data Dictionary
 * -----------------------------------
 * sockfd, newsockfd, servlen, n	int
 * isDisplayed	bool	used to display score only once
 * playerOneWinCounter, playerTwoCounter, drawcounter, playcounter	int counters  
 * firstsPlayerReady, secondPlayerReady		bool	sets whether 
 * 							players are ready or not
 *
 */

int main(int argc, char *argv[]) {
    
    playTimes = atoi(argv[0]);  //get the play times
    int sockfd, newsockfd, servlen, n;
    socklen_t clilen;
    struct sockaddr_un cli_addr, serv_addr;
    bool isDisplayed = false;
    
   
    firstPlayerReady = false;
    secondPlayerReady = false;
    playerOneWinCounter = 0;
    playerTwoWinCounter = 0;
    drawCounter = 0;
    playCounter =0;
    
    if ((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
        error("creating socket");
    unlink("foo.Socket");
    bzero((char *) &serv_addr, sizeof (serv_addr));
    serv_addr.sun_family = AF_UNIX;
    strcpy(serv_addr.sun_path, "foo.Socket"); 
	//set path to "foo.Socket"
    servlen = strlen(serv_addr.sun_path) +
            sizeof (serv_addr.sun_family);
    if (bind(sockfd,(struct sockaddr *) &serv_addr, servlen) < 0) 
	//bind address to socket as a server
        error("binding socket");

     
    // running until play times equals to counter
     for (;;) { //same as while(1)
       //get connection from clients
       listen(sockfd, 5);
        clilen = sizeof (cli_addr);
        //cout<<"haha"<<endl;
        newsockfd = accept(
                sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0)
            error("accepting");
        //read buffer
        n = read(newsockfd, buf, 80);
       
        //printf("A connection has been established\n");
        string s = buf;
        //cout <<"-----------"<<s<<"----------"<<endl;
        //parse buffer
        parsingMessage(s, newsockfd);
        bzero(buf, 80);
        close(newsockfd);
        //display final result
        if(!isDisplayed)// the purpose for isDisplay bool variable is to 
			//only plays this score information one time
        {
            if(playCounter >= playTimes)
            {
                isDisplayed = true;  
                cout<<"Final Score:\n"
                        <<"\tPlayer 1: "<<playerOneWinCounter<<"\n"
                        <<"\tPlayer 2: " <<playerTwoWinCounter <<endl
                        <<"\tDraw :" <<drawCounter<<endl;
                close(newsockfd);  //close client socket
            }
        }
     }
      close(sockfd);  // close server socket, but will never get here, just in case
    
    return 0;
}

/*
 * Function Name: parsingMessage
 * Description: gets the string message from the players on whether
 * 		they are ready, their choices and the "GO" or "ST" for stop
 *
 * Return Value Parameter Data Dictionary
 * -----------------------------------
 * No return value
 *
 * Reference Parameter Data Dictionary
 * -----------------------------------
 * newsockfd	int
 * s		string
 *
 * Local Variable Data Dictionary
 * -----------------------------------
 *  
 */


//Get the string, according to content make the decision  
void parsingMessage(string s, int newsockfd) {
    //client sent ready information when it starts to run
    if (s == "Player One Ready" || s == "Player Two Ready") {
        SetReadyState(s);
        if (firstPlayerReady && secondPlayerReady) {//if get "Ready" request from both clients 
            cout << "Player 1: Ready\n" << "Player 2: Ready\n";
            firstPlayerReady = false;
            secondPlayerReady = false;
        }
        write(newsockfd, "GO",3);
    } 
    else   //"Scissors Rocks or Paper message from player"
    {
        if((!firstPlayerReady &&!secondPlayerReady)&&(playCounter < playTimes))
            cout <<"Go Players   [ "<<playCounter+1<<" ]" <<endl;
        //set player's state
        ScissorRockPaper(s);
        if(playCounter == playTimes)
        {
            write(newsockfd, "ST", 3); //finish playing
        }
        else
        {
            //sleep(1);
           write(newsockfd, "GO",3);
        }
    }
   
}

/*
 * Function Name: ScissorsRockPaper
 * Description: This is the function that checks for the states of 
 *              each player
 *
 * Return Value Parameter Data Dictionary
 * -----------------------------------
 * No return value
 *
 * Reference Parameter Data Dictionary
 * -----------------------------------
 * s            string		buffer golding playerName and choice
 *
 * Local Variable Data Dictionary
 * -----------------------------------
 * 
 */


void ScissorRockPaper(string s) {

    if (s == "Player One Scissors") {
        if(!firstPlayerReady && (playCounter != playTimes))
                formatDisplay(s);
                           
        firstPlayerReady = true;
        firstPlayerSRP = "Scissors";
        if (firstPlayerReady && secondPlayerReady&& (playCounter != playTimes))
            setAllPlayersInReadyState(s);
        

    } else if (s == "Player One Rock" ) {
        if(!firstPlayerReady&& (playCounter != playTimes))
                  formatDisplay(s);
        firstPlayerReady = true;
        firstPlayerSRP = "Rock";
        if (firstPlayerReady && secondPlayerReady&& (playCounter != playTimes))
            setAllPlayersInReadyState(s);
    } else if (s == "Player One Paper" ) {
        if(!firstPlayerReady&& (playCounter != playTimes))
                formatDisplay(s);
        firstPlayerReady = true;
        firstPlayerSRP = "Paper";
        if (firstPlayerReady && secondPlayerReady&& (playCounter != playTimes))
            setAllPlayersInReadyState(s);
    } else if (s == "Player Two Scissors" ) {
        if(!secondPlayerReady&& (playCounter != playTimes))
                formatDisplay(s);
        secondPlayerReady = true;
        secondPlayerSRP = "Scissors";
        if (firstPlayerReady && secondPlayerReady&& (playCounter != playTimes))
            setAllPlayersInReadyState(s);
    } else if (s == "Player Two Rock" ) {
        if(!secondPlayerReady&& (playCounter != playTimes))
        formatDisplay(s);
        secondPlayerReady = true;
        secondPlayerSRP = "Rock";
        if (firstPlayerReady && secondPlayerReady&& (playCounter != playTimes))
            setAllPlayersInReadyState(s);
    } else if (s == "Player Two Paper") {
        if(!secondPlayerReady && (playCounter != playTimes))
                formatDisplay(s);
        secondPlayerReady = true;
        secondPlayerSRP = "Paper";
        if (firstPlayerReady && secondPlayerReady&& (playCounter != playTimes))
            setAllPlayersInReadyState(s);
    }
    

}

/*
 * Function Name: getWinner
 * Description: Compares the states of each player to decide whether 
 *              it was a win lose or a draw and increments the counters
 *		for the next round.
 *
 * Return Value Parameter Data Dictionary
 * -----------------------------------
 * No return value
 *
 * Reference Parameter Data Dictionary
 * -----------------------------------
 * none
 *
 * Local Variable Data Dictionary
 * -----------------------------------
 * none           
 */


void getWinner() {
    //draw cases:
    if (firstPlayerSRP == "Rock" && secondPlayerSRP == "Rock") {
        cout << "Players draw" << endl;
        drawCounter++;
        playCounter++;
        
    } else if (firstPlayerSRP == "Scissors" && secondPlayerSRP == "Scissors") {
        cout << "Players draw" << endl;
        drawCounter++;
        playCounter++;
       
    } else if (firstPlayerSRP == "Paper" && secondPlayerSRP == "Paper") {
        cout << "Players draw" << endl;
        drawCounter++;
        playCounter++;
        
    }//player one wins cases:
    else if (firstPlayerSRP == "Rock" && secondPlayerSRP == "Scissors") {
        cout << "Player 1 wins" << endl;
        playCounter++;
        playerOneWinCounter++;
       
    } else if (firstPlayerSRP == "Scissors" && secondPlayerSRP == "Paper") {
        cout << "Player 1 wins" << endl;
        playerOneWinCounter++;
        playCounter++;
        
    } else if (firstPlayerSRP == "Paper" && secondPlayerSRP == "Rock") {
        cout << "Player 1 wins" << endl;
        playerOneWinCounter++;
        playCounter++;
       
    }//player two wins cases
    else if (secondPlayerSRP == "Rock" && firstPlayerSRP == "Scissors") {
        cout << "Player 2 wins" << endl;
        playerTwoWinCounter++;
        playCounter++;
        
    } else if (secondPlayerSRP == "Scissors" && firstPlayerSRP == "Paper") {
        cout << "Player 2 wins" << endl;
        playerTwoWinCounter++;
        playCounter++;
    } else if (secondPlayerSRP == "Paper" && firstPlayerSRP == "Rock") {
        cout << "Player 2 wins" << endl;
        playCounter++;
        playerTwoWinCounter++;
       
    }
    
  // sleep(1);
    //firstPlayerSRP = NULL;
    //secondPlayerSRP = NULL;

}

/*
 * Function Name: setAllPlayersInReadyState
 * Description: Resets all of the players into ready state 
 *              after each win
 *
 * Return Value Parameter Data Dictionary
 * -----------------------------------
 * No return value
 *
 * Reference Parameter Data Dictionary
 * -----------------------------------
 * s            string
 *
 * Local Variable Data Dictionary
 * -----------------------------------
 *            
 */


void setAllPlayersInReadyState(string s) {
    
    
    getWinner();
      
    firstPlayerReady = false;
    secondPlayerReady = false;
    //cout <<"Go Players   [ "<<playCounter+1<<" ]" <<endl;
   //  sleep(1);

}

/*
 * Function Name: formatDisplay
 * Description: This function formats the values on the playing board
 *              inserting the colon to split the name of the player 
 *		and the choice each player has selected.
 *
 * Return Value Parameter Data Dictionary
 * -----------------------------------
 * No return value
 *
 * Reference Parameter Data Dictionary
 * -----------------------------------
 * s    string	buffer holding selections
 *
 * Local Variable Data Dictionary
 * -----------------------------------
 * sub   string   holds the name of the players    
 */


void formatDisplay(string s) {

    istringstream iss(s);
    cout <<"\t";
    do {
        string sub;
        iss >> sub;
        if(sub =="One")
            sub = "1";
        if(sub == "Two")
            sub = "2";
        cout << sub << " ";
        if (sub == "One" || sub == "Two")
            cout << ":  ";
    } while (iss);
    cout << endl;
}

/*
 * Function Name: setReadyState
 * Description: This function sets the ready state only the first time
 *
 * Return Value Parameter Data Dictionary
 * -----------------------------------
 * No return value
 *
 * Reference Parameter Data Dictionary
 * -----------------------------------
 * s    string  buffer holding selections
 *
 * Local Variable Data Dictionary
 * -----------------------------------
 *
 */

void SetReadyState(string s) {

    if (s == "Player One Ready")
        firstPlayerReady = true;
    else
        secondPlayerReady = true;
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
 * *msg	   const char	pointer to msg
 *
 * Local Variable Data Dictionary 
 * ------------------------------------
 * 
 */

void error(const char *msg) {
	perror(msg);
	exit(0);
}


























