//Name:     Xinyi Wang
//Course:   COSC 5321
//Lab #:    8
//Assigned: Mar 1, 2011
//Due:      Mar 8, 2011
//Purpose:  Create a Hash Table then search for values in the table.
//          Count the number of probes and display the probe sequence.
//
//Input:    Create a Hash Table using file input from lab8.dat.
//          Search the Hash Table using file input from lab8srch.dat.
//
//Output:   The output will be directed to the screen
//          then create a makefile and redirect the output to lab8report.txt.
//
//Program outline:
//           Open "lab8.dat" and "lab8srch.dat" files for input; test for successful open
//           Read from the input file "lab8.dat"
//           Store the data into a hash table which is created according to the modulo division hashing algorithm
//           Then print the output directly to the screen
//           Read from the input file "lab8srch.dat"
//           Search the hash table then print the result of search directly to the screen
//           Close both files

#include <iostream>  //cin, cout functions 
#include <fstream>   //ifstream, ofstream functions
#include <iomanip>   //setw()
#include <cstdlib>   //exit function
#include "queueADT.h"
#include "linkedQueue.h"
#include "hashT.h"

using namespace std;

//Function prototypes
void OpenInputFile (ifstream&, char[]);
int hashFunction(char *);
template <class elemType>
void ReadAndPrintFiles(ifstream&, ifstream&, hashT<elemType>&);

//Global constant
const int HTSize = 45;

int main()
{
   hashT<int> hashtable(HTSize);
   //Input file stream
   ifstream dataFileIn1, dataFileIn2;
   //Input file name 1 for hash table
   char inputharsh[30] = "lab8.dat";
   //Input file name 2 for search
   char inputsearch[30] = "lab8srch.dat";

   //Print heading
   cout << "      OUTPUT FOR XINYI WANG LAB8	SPRING 2011" << endl << endl;

   //Function call to open the input file 1 for hash table
   OpenInputFile(dataFileIn1, inputharsh);
   //Function call to open the input file 2 for search
   OpenInputFile(dataFileIn2, inputsearch);

   //Read from inputs, print the hash table, then search it
   ReadAndPrintFiles(dataFileIn1, dataFileIn2, hashtable);

   //Close input file 1 for hash table
   dataFileIn1.close();
   //Close input file 2 for search
   dataFileIn2.close();

   return 0;
}



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

//Purpose:        Convert the key into a hash index according to the modulo division hashing algorithm
//Pre-condition:  A string has been successfully inserted as a parameter
//Post-condition: The hash index is returned
int hashFunction(char *insertKey)
{
	int sum = 0;

	for (int j = 0; j < 3; j++)
		sum = sum + static_cast<int>(insertKey[j]);

	return (sum % HTSize);
} //End hashFunction

//Purpose:        Read from input files
//                Print the hash table directly to the screen
//                Search the hash table and then print the output directly to the screen
//Pre-condition:  Both input files have been successfully opened
//Post-condition: The hash table is created with data from the input file 1
//                Print the results of search with data from the input file 2
template <class elemType>
void ReadAndPrintFiles(ifstream& dataFileIn1, ifstream& dataFileIn2, hashT<elemType>& hashtable)
{
   char num[4];
   cout << "The hash table is shown as follow (size " << HTSize << "):" << endl;
   cout << "     indexStatusList      HashTable(0 means empty spot)" << endl;
 
   dataFileIn1 >> num;
   while (!dataFileIn1.eof())
   {
	   dataFileIn1.ignore(100, '\n');
	   hashtable.insert(hashFunction(num), atoi(num));
	   dataFileIn1 >> num;
   }
   hashtable.print();


   char num1[4];
   int hashIndex;
   bool found;
   int pCount;
   linkedQueueType<int> probeSequence;
   cout << endl << "Search for values in the hash table using values in lab8srch.dat:";
   cout << endl << " Value" << "   " << "Found?" << "   " << "# of probes" << "   " << "The probe sequence" << endl;

   dataFileIn2 >> num1;
   while (!dataFileIn2.eof())
   {
		hashIndex = hashFunction(num1);
		dataFileIn2.ignore(100, '\n');
		hashtable.search(hashIndex, atoi(num1), found, pCount, probeSequence);

		cout << setw(5) << num1;
		switch(found)
		{
		case 1: cout << setw(8) << "Yes";
			break;
		case 0: cout << setw(8) << "No";
			break;
		}
		cout << setw(11) << pCount << "         ";
	    while (!probeSequence.isEmptyQueue())
	    {
		cout << probeSequence.front() << " ";
		probeSequence.deleteQueue();
	    }
	    cout << endl;

		dataFileIn2 >> num1;
   }
}


