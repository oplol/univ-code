//Name:     Xinyi Wang
//Course:   COSC 5321
//Lab #:    9
//Assigned: Mar  8, 2011
//Due:      Mar 22, 2011
//Purpose:  Create an array-based list and apply the quick sort algorithm
//          to sort the list. Count the number of key compares and the
//          number of record moves.
//
//Input:    The original list using file input from lab9.dat.
//
//Output:   The output will be directed to the file "lab9.txt"
//          then create a makefile.
//
//Program outline:
//           Open "lab9.dat" file for input; test for successful open
//           Open "lab9.txt" file for output; test for successful open
//           Read from the input file "lab9.dat"
//           Insert the data at the end and checks for duplicates, then print the original list
//           Sort the data by using the quick sort, then print the sorted list
//           Include the appropriate headings/titles and the counts for key compares and record moves
//           Print all the output directly to the file "lab9.txt"
//           Close both files

#include <iostream>  //cin, cout functions 
#include <fstream>   //ifstream, ofstream functions
#include <iomanip>   //setw()
#include <cstdlib>   //exit function
#include "arrayListType.h"

using namespace std;

//Function prototypes
void OpenInputFile (ifstream&, char[]);
void OpenOutputFile (ofstream&, char[]);
void PrintHeading (ofstream&);
template <class elemType>
void ReadAndWriteFiles(ifstream&, arrayListType<elemType>&, ofstream&);

int main()
{
	const int DEFAULT_SIZE = 110;
	arrayListType<int> alist(DEFAULT_SIZE);
	ifstream dataFileIn;
	ofstream dataFileOut;
	char inputFile[30] = "lab9.dat";
	char outputFile[30] = "lab9.txt";

	OpenInputFile(dataFileIn, inputFile);
	OpenOutputFile(dataFileOut, outputFile);
	PrintHeading(dataFileOut);
	ReadAndWriteFiles(dataFileIn, alist, dataFileOut);

    dataFileIn.close();
    dataFileOut.close();
	
	cout << "The output has been printed directly to lab9.txt! Please check it out!" << endl;

	return 0;
} //end main



//Purpose:        Open an input file and test for successful open
//Pre-condition:  File has been declared as input file stream, and
//                file name is known
//Post-condition: File is open if successful, otherwise terminate the program
void OpenInputFile(ifstream& dataFileIn, char inputFile[])
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
void OpenOutputFile(ofstream& dataFileOut, char outputFile[])
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
   	dataFileOut << "            OUTPUT FOR XINYI WANG LAB9	SPRING 2011" << endl;
} //End PrintHeading


//Purpose:        Read from an input file and sort the list, then write to an output file
//Pre-condition:  Both files have been successfully opened
//Post-condition: The output file is created with data from the input file
template <class elemType>
void ReadAndWriteFiles(ifstream& dataFileIn, arrayListType<elemType>& arraylist, ofstream& dataFileOut)
{
	int num, num1;

    dataFileOut << endl << endl;
	dataFileOut << "1. The orignal list without duplicates" << endl;
	dataFileOut << "  index    number  " << endl;

	dataFileIn >> num;
    //While not end-of-file
    while(!dataFileIn.eof())
	{
		arraylist.insert(num);
		arraylist.retrieveAt(arraylist.listSize() - 1, num1);
		dataFileIn.ignore(81, '\n');
		dataFileOut << "  [" << setw(3) << arraylist.listSize() << "]"<< setw(8) << num1 << endl;
		dataFileIn >> num;
	} //End while

	int num2, count = 0;
	dataFileOut << endl << endl;
	dataFileOut << "2. The list sorted by the quick sort" << endl;
	dataFileOut << "  index    number  " << endl;
	//Quicksort
	int count1 = 0, count2 = 0;
	arraylist.quickSort(count1, count2);
	while ( count < arraylist.listSize())
	{
	arraylist.retrieveAt(count, num2);
	dataFileOut << "  [" << setw(3) << ++count << "]"<< setw(8) << num2 << endl;
	} //End while
	dataFileOut << "The number of key compares is: " << count1 << endl;
	dataFileOut << "The number of record moves is: " << count2 << endl;
}


