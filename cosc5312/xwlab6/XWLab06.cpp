//Name:      Xinyi Wang
//Course:    COSC 5312
//Prog#:     6
//Assigned:  March  8, 2011
//Date due:  March 22, 2011
//
//Purpose:   Compare sorting efficiencies of Bubble and Selection sorts

#include <iostream>  //cin, cout functions 
#include <fstream>   //ifstream, ofstream functions
#include <iomanip>   //setw()
#include <cstdlib>   //exit function
using namespace std; //location of classes and functions defined in
                     //standard libraries

//Function prototypes
void OpenInputFile (ifstream&, char[]);
void OpenOutputFile (ofstream&, char[]);
void ReadAndWriteFiles1 (ifstream&, ofstream&);
void ReadAndWriteFiles2 (ifstream&, ofstream&);
void PrintHeading (ofstream&);


const int DEFAULT_SIZE = 70, NAME_SIZE = 13, CITY_SIZE = 16;

struct employeeInfo
{
	int empID;
	char empName[NAME_SIZE];
	char city[CITY_SIZE];
};

int main()
{
   //Input file stream
   ifstream dataFileIn;
   //Output file stream
   ofstream dataFileOut;
   char ch;

   //Input file name
   char inputFile[30] = "XWlab06.dat";
   //Output file name
   char outputFile[30] = "XWlab06.out";

   //Function call to open the output file
   OpenOutputFile(dataFileOut, outputFile);
   //Print heading for output file
   PrintHeading(dataFileOut);

   //Function call to open the input file
   OpenInputFile(dataFileIn, inputFile);
   //Read from input file; write the sorted array using bubble sort to output file
   ReadAndWriteFiles1(dataFileIn, dataFileOut);
   //Close input file
   dataFileIn.close();


   //Function call to open the input file
   OpenInputFile(dataFileIn, inputFile);
   //Read from input file; write the sorted array using selection sort to output file
   ReadAndWriteFiles2(dataFileIn, dataFileOut);
   //Close input file
   dataFileIn.close();

   //Close output file
   dataFileOut.close();

   //enter any key to end program
   cout << "All the ouput has been directed to XWlab06.out! \nPress Enter key to end the program...";
   cin.get(ch);

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
   dataFileOut << "    OUTPUT FOR Xinyi Wang XWLab06 PROGRAM	Spring 2011" << endl;
   dataFileOut << endl;
} //End PrintHeading


//Purpose:        Read from an input file using the bubble sort, then write all the info to an output file
//Pre-condition:  Both files have been successfully opened
//Post-condition: The output file is created with data sorted from the input file
void ReadAndWriteFiles1(ifstream& dataFileIn, ofstream& dataFileOut)
{
   dataFileOut << endl;
   dataFileOut << "1. The Bubble Sort" << endl;
   dataFileOut << "                         the unsorted list" << endl;
   dataFileOut << " |  employee id number |    employee name    |         city        |" << endl;
   dataFileOut << " |                     |                     |                     |" << endl;

   employeeInfo empl[DEFAULT_SIZE];
   //Read blank character then discard
   char blank;
   int count = 0;

   dataFileIn >> empl[count].empID;
   //While not end-of-file
   while(!dataFileIn.eof())
   {
	  //Discard next character
      dataFileIn.get(blank);
	  //Read employee name
      dataFileIn.get(empl[count].empName, NAME_SIZE);
      //Discard next character
      dataFileIn.get(blank);
      //Read city
      dataFileIn.get(empl[count].city, CITY_SIZE);
	  //Read next characters, ie '\n'
	  dataFileIn.ignore(100, '\n');
      //Write to the output file
      dataFileOut << " | " << setw(11) << empl[count].empID << setw(11) << " | " 
		                   << setw(16) << empl[count].empName << setw(6) << " | "
                           << setw(17) << empl[count].city << setw(4) << " |" << endl;
	  count++;
	  dataFileIn >> empl[count].empID;
   } //End While

   dataFileOut << endl;
   dataFileOut << "                   the list by using the bubble sort" << endl;
   dataFileOut << " |  employee id number |    employee name    |         city        |" << endl;
   dataFileOut << " |                     |                     |                     |" << endl;
   //The bubble sort
   bool swap;
   int temp;
   char temp1[NAME_SIZE], temp2[CITY_SIZE];
   int j=0;

   do
   {
		swap = false;
		for (int i = 0; i < (count - 1); i++)
		{
			if (empl[i].empID > empl[i + 1].empID)
			{
				temp = empl[i].empID;
				empl[i].empID = empl[i + 1].empID;
				empl[i + 1].empID = temp;
				for (int m = 0; m < NAME_SIZE; m++)
				{
					temp1[m] = empl[i].empName[m];
					empl[i].empName[m] = empl[i + 1].empName[m];
					empl[i + 1].empName[m] = temp1[m];
				}
				for (int n = 0; n < CITY_SIZE; n++)
				{
					temp2[n] = empl[i].city[n];
					empl[i].city[n] = empl[i + 1].city[n];
					empl[i + 1].city[n] = temp2[n];
				}
				swap = true;
				j++;
			}
		}
   } while (swap);

   //Print the list
   for (int k = 0; k < count; k++)
      dataFileOut << " | " << setw(11) << empl[k].empID << setw(11) << " | " 
		                   << setw(16) << empl[k].empName << setw(6) << " | "
                           << setw(17) << empl[k].city << setw(4) << " |" << endl;
   dataFileOut << " The number of exchanges: " << j << endl;
   dataFileOut << endl;
} //End ReadAndWriteFiles1


//Purpose:        Read from an input file using the selection sort, then write all the info to an output file
//Pre-condition:  Both files have been successfully opened
//Post-condition: The output file is created with data sorted from the input file
void ReadAndWriteFiles2(ifstream& dataFileIn, ofstream& dataFileOut)
{
   dataFileOut << endl;
   dataFileOut << "2. The Selection Sort" << endl;
   dataFileOut << "                         the unsorted list" << endl;
   dataFileOut << " |  employee id number |    employee name    |         city        |" << endl;
   dataFileOut << " |                     |                     |                     |" << endl;

   employeeInfo empl[DEFAULT_SIZE];
   //Read blank character then discard
   char blank;
   int count = 0;

   dataFileIn >> empl[count].empID;
   //While not end-of-file
   while(!dataFileIn.eof())
   {
	  //Discard next character
      dataFileIn.get(blank);
	  //Read employee name
      dataFileIn.get(empl[count].empName, NAME_SIZE);
      //Discard next character
      dataFileIn.get(blank);
      //Read city
      dataFileIn.get(empl[count].city, CITY_SIZE);
	  //Read next characters, ie '\n'
	  dataFileIn.ignore(100, '\n');
      //Write to the output file
      dataFileOut << " | " << setw(11) << empl[count].empID << setw(11) << " | " 
		                   << setw(16) << empl[count].empName << setw(6) << " | "
                           << setw(17) << empl[count].city << setw(4) << " |" << endl;
	  count++;
	  dataFileIn >> empl[count].empID;
   } //End While

   dataFileOut << endl;
   dataFileOut << "                 the list by using the selection sort" << endl;
   dataFileOut << " |  employee id number |    employee name    |         city        |" << endl;
   dataFileOut << " |                     |                     |                     |" << endl;
   //The selection sort
   	int startScan, minIndex, minValue;
	int j=0;
	char minName[NAME_SIZE], minCity[CITY_SIZE];

	for (startScan = 0; startScan < (count - 1); startScan++)
	{
		minIndex = startScan;
		minValue = empl[startScan].empID;
		for (int m = 0; m < NAME_SIZE; m++)
		minName[m] = empl[startScan].empName[m];
		for (int n = 0; n < CITY_SIZE; n++)
		minCity[n] = empl[startScan].city[n];
		for(int index = startScan + 1; index < count; index++)
		{
			if (empl[index].empID < minValue)
			{
				minValue = empl[index].empID;
			    for (int m = 0; m < NAME_SIZE; m++)
		        minName[m] = empl[index].empName[m];
				for (int n = 0; n < CITY_SIZE; n++)
		        minCity[n] = empl[index].city[n];
				minIndex = index;
			}
		}
		empl[minIndex].empID = empl[startScan].empID;
		empl[startScan].empID = minValue;
		for (int m = 0; m < NAME_SIZE; m++)
		{
		    empl[minIndex].empName[m] = empl[startScan].empName[m];
		    empl[startScan].empName[m] = minName[m];
		}
		for (int n = 0; n < CITY_SIZE; n++)
		{
			empl[minIndex].city[n] = empl[startScan].city[n];
			empl[startScan].city[n] = minCity[n];
		}
		j++;
	}

   
   //Print the list
   for (int k = 0; k < count; k++)
      dataFileOut << " | " << setw(11) << empl[k].empID << setw(11) << " | " 
		                   << setw(16) << empl[k].empName << setw(6) << " | "
                           << setw(17) << empl[k].city << setw(4) << " |" << endl;
   dataFileOut << " The number of exchanges: " << j << endl;
   dataFileOut << endl;
} //End ReadAndWriteFiles2


