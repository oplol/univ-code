//Name:     Xinyi Wang
//Course:   COSC 5321
//Lab #:    10
//Assigned: Mar 22, 2011
//Due:      Mar 29, 2011
//Purpose:  Add to the previous lab by creating a second array-based list
//          and applying the heap sort algorithm to sort the list. Count
//          the number of key compares and the number of record moves.
//
//Input:    The original list using file input from lab9.dat.
//
//Output:   The output will be directed to the file "lab10.txt"
//          then create a makefile.
//
//Program outline:
//           Open "lab9.dat" file for input; test for successful open
//           Open "lab10.txt" file for output; test for successful open
//           Read from the input file "lab9.dat"
//           Insert the data at the end and checks for duplicates, then print the original list
//           Sort the data by using the quick sort, then print the sorted list
//           Sort the data by using the heap sort, then print the sorted list
//           Include the appropriate headings/titles and the counts for key compares and record moves for both sorts
//           Print all the output directly to the file "lab10.txt"
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
void ReadAndWriteFiles(ifstream&, arrayListType<elemType>&, arrayListType<elemType>&, ofstream&);

int main()
{
	const int DEFAULT_SIZE = 110;
	arrayListType<int> alist(DEFAULT_SIZE), blist(DEFAULT_SIZE);
	ifstream dataFileIn;
	ofstream dataFileOut;
	char inputFile[30] = "lab9.dat";
	char outputFile[30] = "lab10.txt";

	OpenInputFile(dataFileIn, inputFile);
	OpenOutputFile(dataFileOut, outputFile);
	PrintHeading(dataFileOut);
	ReadAndWriteFiles(dataFileIn, alist, blist, dataFileOut);

    dataFileIn.close();
    dataFileOut.close();
	
	cout << "The output has been printed directly to lab10.txt! Please check it out!" << endl;

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
   	dataFileOut << "             OUTPUT FOR XINYI WANG LAB10	SPRING 2011" << endl;
} //End PrintHeading


//Purpose:        Read from an input file and sort the list by using the quick and heap sort, then write to an output file
//Pre-condition:  Both files have been successfully opened
//Post-condition: The output file is created with data from the input file
template <class elemType>
void ReadAndWriteFiles(ifstream& dataFileIn, arrayListType<elemType>& arraylist1, arrayListType<elemType>& arraylist2, ofstream& dataFileOut)
{
	int num;
	dataFileIn >> num;
    //While not end-of-file
    while(!dataFileIn.eof())
	{
		arraylist1.insert(num);
		arraylist2.insert(num);
		dataFileIn.ignore(81, '\n');
		dataFileIn >> num;
	} //End while
	
	int num1, num3, cou = 0;
	dataFileOut << endl << endl;
	dataFileOut << "1. The orignal list without duplicates" << endl;
	dataFileOut << "  index    number  " << endl;
	//Print the original list
	while ( cou < arraylist1.listSize())
	{
		arraylist1.retrieveAt(cou, num1);
		arraylist2.retrieveAt(cou, num3);
		dataFileOut << "  [" << setw(3) << ++cou << "]"<< setw(8) << num1 << endl;
	} //End while

	int num2, count = 0;
	dataFileOut << endl << endl;
	dataFileOut << "2. The list sorted by the quick sort" << endl;
	dataFileOut << "  index    number  " << endl;
	//Quicksort
	int count1 = 0, count2 = 0;
	arraylist1.quickSort(count1, count2);
	while ( count < arraylist1.listSize())
	{
	    arraylist1.retrieveAt(count, num2);
	    dataFileOut << "  [" << setw(3) << ++count << "]"<< setw(8) << num2 << endl;
	} //End while

	int num4, acount = 0;
	dataFileOut << endl << endl;
    dataFileOut << "3. The list sorted by the heap sort" << endl;
	dataFileOut << "  index    number  " << endl;
	//Heapsort
	int count3 = 0, count4 = 0;
	arraylist2.heapSort(count3, count4);
	while ( acount < arraylist2.listSize())
	{
		arraylist2.retrieveAt(acount, num4);
		dataFileOut << "  [" << setw(3) << ++acount << "]"<< setw(8) << num4 << endl;
	} //End while

	//the table with counts
	dataFileOut << endl << endl;
	dataFileOut << "4. The table with the counts for both sorts" << endl << endl;
	dataFileOut << "                              Quicksort  Heapsort" << endl; 
	dataFileOut << "  the number of key compares" << setw(8) << count1 << setw(11) << count2 << endl;
	dataFileOut << "  the number of record moves" << setw(8) << count3 << setw(11) << count4 << endl;
}


