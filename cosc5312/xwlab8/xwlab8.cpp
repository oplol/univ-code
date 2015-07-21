//Name:      Xinyi Wang
//Course:    COSC 5312
//Prog#:     8
//Assigned:  April 12, 2011
//Date due:  April 19, 2011

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include "NumberList.h"

using namespace std;


//Function prototypes
void OpenInputFile (ifstream&, char[]);
void OpenOutputFile (ofstream&, char[]);
void PrintHeading (ofstream&);
void ReadAndWriteFiles1(ifstream&, NumberList&, ofstream&);
void ReadAndWriteFiles2(ifstream&, NumberList&, ofstream&);

int main()
{
   NumberList olist;
   //Input files stream
   ifstream dataFileIn1, dataFileIn2;
   //Output file stream
   ofstream dataFileOut;
   char ch;

   //Input files name
   char inputFile1[30] = "lab8.dat";
   char inputFile2[30] = "lab8up.dat";
   //Output file name
   char outputFile[30] = "xwlab8.out";

   //Function call to open the input file1
   OpenInputFile(dataFileIn1, inputFile1);
   //Function call to open the input file2
   OpenInputFile(dataFileIn2, inputFile2);
   //Function call to open the output file
   OpenOutputFile(dataFileOut, outputFile);
   //Print heading for output file
   PrintHeading(dataFileOut);

   ReadAndWriteFiles1(dataFileIn1, olist, dataFileOut);

   ReadAndWriteFiles2(dataFileIn2, olist, dataFileOut);

   //Close input file1
   dataFileIn1.close();
   //Close input file2
   dataFileIn2.close();
   //Close output file
   dataFileOut.close();

   //enter any key to end program
   cout << "All the ouput has been directed to xwlab8.out! \nPress Enter key to end the program...";
   cin.get(ch);

   return 0;
}




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
   dataFileOut << "     OUTPUT FOR Xinyi Wang XWLAB8 PROGRAM	Spring 2011" << endl;
   dataFileOut << endl;
} //End PrintHeading


//Purpose:        Read from an input file, then write to an output file
//Pre-condition:  Both files have been successfully opened
//Post-condition: The output file is created with data from the input file
void ReadAndWriteFiles1(ifstream& dataFileIn, NumberList& olist, ofstream& dataFileOut)
{
   int num;

   dataFileIn >> num;
   dataFileOut << "     KEY  |    MESSAGE" << endl;
   while (!dataFileIn.eof())
   {
	   dataFileOut << "    " << num << "  |  ";
	   olist.insertNode(num, dataFileOut);
	   dataFileIn.ignore(81, '\n');
	   dataFileIn >> num;
   }
   dataFileOut << endl << "1. The original list: ";
   olist.displayList(dataFileOut);
   dataFileOut << endl << "   The number of elements in the original list: " << olist.length() << endl;
   dataFileOut << endl << endl;
}


//Purpose:        Read from an input file, then write to an output file
//Pre-condition:  Both files have been successfully opened
//Post-condition: The output file is created with data from the input file
void ReadAndWriteFiles2(ifstream& dataFileIn, NumberList& olist, ofstream& dataFileOut)
{
   int num1, num2;
   char blank;

   dataFileOut << "2. The audit trail with update code, key, and audit message: " << endl;
   dataFileOut << "   CODE  |  KEY  |    MESSAGE" << endl;

   dataFileIn >> num1;
   while (!dataFileIn.eof())
   {
	   dataFileIn.get(blank);
	   dataFileIn >> num2;
	   dataFileOut << "    " << num1 << "    |  " << num2 << " |  ";
	   switch (num1)
	   {
	   case 0: olist.deleteNode(num2, dataFileOut);
		   break;
	   case 1: olist.insertNode(num2, dataFileOut);
		   break;
	   }
	   dataFileIn.ignore(81, '\n');
	   dataFileIn >> num1;
   }
   dataFileOut << endl << endl;
   dataFileOut << "3. The updated list: ";
   olist.displayList(dataFileOut);
   dataFileOut << endl << "   The number of elements in the uplist: " << olist.length() << endl;
   dataFileOut << endl << endl;
}


