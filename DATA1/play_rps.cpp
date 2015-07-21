#include <cstdlib>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <iostream>
#include <sys/wait.h>
#include <string.h>

using namespace std;


void execFunction(char fileName[], char parms[]);

bool isInteger(char *num);

/*
 * Function Name: Main
 * Description: Main creates the forked processes that 
 *		create the referree and the two players.
 *		
 * Return Value Parameter Data Dictionary
 * -----------------------------------
 * 0
 *
 * Reference Parameter Data Dictionary
 * -----------------------------------
 * argc         int	length or number of arguments
 * argv         char** 		pointer to an array of pointers 
 *				to null-terminated character strings
 *
 * Local Variable Data Dictionary
 * -----------------------------------
 * mainPid	pid_t	file descriptor 
 * status	int	reference used for wait function
 *
 */


int main(int argc, char** argv) {

   if(!isInteger(argv[1])) //terminates program if value entered isn't 
			   //an integer
   {
        cout<<"Please enter an integer value greater than zero.\n";
        cout<<"------------terminating program------------------\n";
        return 0;
   }

  if(atoi(argv[1])<=0) //terminates program if value is less than zero
   {
        cout<<"Please enter an integer greater than zero.\n";
        cout<<"------------terminating program------------------\n";
        return 0;
   }
//  The function never go to this check so changed only isInteger above



    // cout <<playtimes<<endl; 
    pid_t mainPid;
    int status;
    mainPid = fork();
    if (mainPid > 0) { //main process
        //cout << "I am the Main\n";
	pid_t pidChildTwo;

        pidChildTwo = fork();
        if (pidChildTwo == 0) { //second process: player one
            //cout << "I am the second child\n";
            char fileName[] = "./player";
            char playerName[] = "Player One";
            execFunction(fileName, playerName);

        } else {
           // sleep(5);
            pid_t pidChildThree;

            pidChildThree = fork();
            if (pidChildThree == 0) { //third process: player two
                //cout << "I am the third child\n";
                char fileName[] = "./player";
                char playerName[] = "Player Two";
                execFunction(fileName, playerName);
                
            }
        }

        } else if (mainPid == 0) { // first child: referee
            //cout << "I am the first child\n";
            char fileName[] = "./referee";
            char playTimes[100];
            strcpy(playTimes, argv[1]);
            execFunction(fileName, playTimes);
        }
        wait(&status);
        //sleep(5);
        return 0;
    }

/*
 * Funtion Name: isInteger
 * Description: this function verifies that the iterations 
 *		entered is a digit and not a letter
 *              
 * Return Value Parameter Data Dictionary
 * -----------------------------------
 * true/false	bool	value assigned if user
 *			entered correct integer value
 *
 * Reference Parameter Data Dictionary
 * -----------------------------------
 * *num	  char	 aaray of characters
 *
 * Local Variable Data Dictionary
 * -----------------------------------
 * i	int	incrementer
 */


 bool isInteger(char *num)
        {
                for(int i=0;i<(int)strlen(num); i++)
                {
                        if(!isdigit(num[i])) 
		              return false;
                }
                return true;
        }



/*
 * Funtion Name: execFunction
 * Description: replaces the calling process image with 
 * 		a new process image
 * Return Value Parameter Data Dictionary
 * -----------------------------------
 * No return value
 *
 * Reference Parameter Data Dictionary
 * -----------------------------------
 * fileName     char	array of fileNames
 * parms        char	array of parameters
 *
 * Local Variable Data Dictionary
 * -----------------------------------
 *
 */


void execFunction(char fileName[], char parms[]) {

	char *argu[] = {parms, NULL};
	execve(fileName, argu, NULL);
    }
