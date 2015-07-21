//Name:     Xinyi Wang
//Course:   COSC 5321
//Lab #:    7
//Assigned: Feb 22, 2011
//Due:      Mar  1, 2011
//Purpose:  Simulate an "instance" of resolving a departure delay problem
//          for an airport runway by categorizing data and then adding the
//          data to the appropriate queue category.
//
//Input:    Get the runway arrival time using file input from lab7.dat. 
//
//Output:   All output directed to lab7.txt.
//
//Program outline:
//           Open a file for input; test for successful open
//           Open a file for output; test for successful open
//           Read from the input file; write to the output file
//           Close both files

#include <iostream>  //cin, cout functions 
#include <fstream>   //ifstream, ofstream functions
#include <iomanip>   //setw()
#include <cstdlib>   //exit function
#include "queueADT.h"
#include "linkedQueue.h"

using namespace std;

//Function prototypes
void OpenInputFile (ifstream&, char[]);
void OpenOutputFile (ofstream&, char[]);
void PrintHeading (ofstream&);
void ReadAndWriteFiles(ifstream&, ofstream&);

struct FlightRecord
	{
		char typeOfFlight[2]; //type of flight
		int flightNum; //a 4-digit airplane flight number
		int arrivalHour, //runway arrival hour
			arrivalMinute; //runway arrival minute
	};

int main()
{
	ifstream dataFileIn;
	ofstream dataFileOut;
	char inputFile[30] = "lab7.dat";
	char outputFile[30] = "lab7.txt";
	
	OpenInputFile(dataFileIn, inputFile);
	OpenOutputFile(dataFileOut, outputFile);
	PrintHeading(dataFileOut);
	ReadAndWriteFiles(dataFileIn, dataFileOut);

	dataFileIn.close();
	dataFileOut.close();

	cout << "The output has been printed directly to lab7.txt! Please check it out!" << endl;

	return 0;
} //End main




//function definitions................................................

//Purpose:        Open an input file and test for successful open
//Pre-condition:  File has been declared as input file stream, and
//                file name is known
//Post-condition: File is open if successful, otherwise terminate the program
void OpenInputFile (ifstream& dataFileIn, char inputFile[])
{
   //Open input file
   dataFileIn.open(inputFile);

   //If not successful open, display message and exit with error
   if (!dataFileIn)
   {
      cout << "\n\n\n\t\t\t Error opening file!"
           << inputFile << endl;
      exit(1);
   }
} //End OpenInputFile


//Purpose:        Open an output file and test for successful open
//Pre-condition:  File has been declared as output file stream, and
//                file name is known
//Post-condition: File is open if successful, otherwise terminate the program
void OpenOutputFile (ofstream& dataFileOut, char outputFile[])
{
   //Open output file
   dataFileOut.open(outputFile);

   //If not successful open, display message and exit with error
   if (!dataFileOut)
   {
      cout << "\n\n\n\t\t\t Error opening file!"
           << outputFile << endl;
      exit(1);
   }
} //End OpenOutputFile


//Purpose:        Print heading for output file
//Pre-condition:  Output file has been opened successfully
//Post-condition: Heading is written to the file
void PrintHeading(ofstream& dataFileOut)
{
   	dataFileOut << "            OUTPUT FOR XINYI WANG LAB7	SPRING 2011" << endl;
} //End PrintHeading


//Purpose:        Read from an input file, then write to an output file
//Pre-condition:  Both files have been successfully opened
//Post-condition: The output file is created with data from the input file
void ReadAndWriteFiles(ifstream& dataFileIn, ofstream& dataFileOut)
{
	FlightRecord rec;
	char blank;
	linkedQueueType<FlightRecord> International, National, Local;

	International.initializeQueue();
	National.initializeQueue();
	Local.initializeQueue();

	dataFileOut << endl << endl;
	dataFileOut << "1) THE ORDER IN WHICH THE AIRPLANES ARRIVE AT THE RUNWAY" << endl;
	dataFileOut << "| type of flight | flight number | hr:min runway arrival time |" << endl;
    dataFileOut << "|                |               |                            |" << endl;
	dataFileIn.get(rec.typeOfFlight, 2);
	//While not end-of-file
    while(!dataFileIn.eof())
	{
		dataFileIn.get(blank);
		dataFileIn >> rec.flightNum;
		dataFileIn.get(blank);
		dataFileIn >> rec.arrivalHour;
		dataFileIn.get(blank);
		dataFileIn >> rec.arrivalMinute;
		dataFileIn.ignore(100, '\n');
		dataFileOut << "| " << setw(8) << rec.typeOfFlight << setw(9) 
			        << " | " << setw(9) << rec.flightNum << setw(7) 
					<< " | " << setw(13) << rec.arrivalHour << ":" << setw(2) << rec.arrivalMinute << setw(12) << " |" << endl;
		if(rec.typeOfFlight[0] == 'I')
			International.addQueue(rec);
		else if (rec.typeOfFlight[0] == 'N')
			National.addQueue(rec);
		else if (rec.typeOfFlight[0] == 'L')
			Local.addQueue(rec);
		else cout << "The type of flight can NOT be found.\n";
		
		dataFileIn.get(rec.typeOfFlight, 2);
	} //End while

	int departhr = 10, departmin = 55;
	int delayhr, delaymin;
	dataFileOut << endl << endl;
	dataFileOut << "2) THE ORDER IN WHICH THE PLANES DEPART FROM THE AIRPORT" << endl;
	dataFileOut << "| type of flight | flight number | hr:min runway arrival time | hr:min departure time | hr:min delay time |" << endl;
    dataFileOut << "|                |               |                            |                       |                   |" << endl;
	//While internation queue is not empty
	while(!International.isEmptyQueue())
	{
		delaymin = departmin - International.front().arrivalMinute;
		delayhr = departhr - International.front().arrivalHour;
		if (delaymin < 0)
		{
			delaymin = delaymin + 60;
			delayhr = delayhr - 1;
		}
		dataFileOut << "| " << setw(8) << International.front().typeOfFlight << setw(9) 
			        << " | " << setw(9) << International.front().flightNum << setw(7) 
					<< " | " << setw(13) << International.front().arrivalHour << ":" << setw(2) << International.front().arrivalMinute << setw(13) 
					<< " | " << setw(10) << departhr << ":" << setw(2) << departmin << setw(11)
					<< " | " << setw(8) << delayhr << ":" << setw(2) << delaymin << setw(8) << " |" << endl;
		departmin +=5;
		if (departmin >=60)
		{
			departmin = departmin - 60;
			departhr = departhr + 1;
			if (departhr >= 24)
				departhr = 0;
		}
		International.deleteQueue();
	} //End while

	//While national queue is not empty
	while(!National.isEmptyQueue())
	{
		delaymin = departmin - National.front().arrivalMinute;
		delayhr = departhr - National.front().arrivalHour;
		if (delaymin < 0)
		{
			delaymin = delaymin + 60;
			delayhr = delayhr - 1;
		}
		dataFileOut << "| " << setw(8) << National.front().typeOfFlight << setw(9) 
			        << " | " << setw(9) << National.front().flightNum << setw(7) 
					<< " | " << setw(13) << National.front().arrivalHour << ":" << setw(2) << National.front().arrivalMinute << setw(13) 
					<< " | " << setw(10) << departhr << ":" << setw(2) << departmin << setw(11)
					<< " | " << setw(8) << delayhr << ":" << setw(2) << delaymin << setw(8) << " |" << endl;
		departmin +=5;
		if (departmin >=60)
		{
			departmin = departmin - 60;
			departhr = departhr + 1;
			if (departhr >= 24)
				departhr = 0;
		}
		National.deleteQueue();
	} //End while

	//While local queue is not empty
	while(!Local.isEmptyQueue())
	{
		delaymin = departmin - Local.front().arrivalMinute;
		delayhr = departhr - Local.front().arrivalHour;
		if (delaymin < 0)
		{
			delaymin = delaymin + 60;
			delayhr = delayhr - 1;
		}
		dataFileOut << "| " << setw(8) << Local.front().typeOfFlight << setw(9) 
			        << " | " << setw(9) << Local.front().flightNum << setw(7) 
					<< " | " << setw(13) << Local.front().arrivalHour << ":" << setw(2) << Local.front().arrivalMinute << setw(13) 
					<< " | " << setw(10) << departhr << ":" << setw(2) << departmin << setw(11)
					<< " | " << setw(8) << delayhr << ":" << setw(2) << delaymin << setw(8) << " |" << endl;
		departmin +=5;
		if (departmin >=60)
		{
			departmin = departmin - 60;
			departhr = departhr + 1;
			if (departhr >= 24)
				departhr = 0;
		}
		Local.deleteQueue();
	} //End while
}


