//Name:     Xinyi Wang
//Course:   COSC 5321
//Lab #:    14
//Assigned: Apr 19, 2011
//Due:      Apr 26, 2011
//Purpose:  Illustrate the depth first traversal and the breadth first
//          traversal for three graphs.
//
//Input:    The trees using file input from lab12file1.dat and lab12file2.dat.
//
//Output:   The output will be printed directly to the screen
//          then redirect the screen output to the file "lab13report.txt"
//          then create a makefile.
//
//Program outline:
//           Open "graphSet1.dat" file for input1; test for successful open
//           Open "graphSet2.dat" file for input2; test for successful open
//           Open "graphSet3.dat" file for input3; test for successful open
//           Create graph1, graph2 and graph3 by using the data from input file1, file2 and file3
//           Include the appropriate headings/titles
//           Print all the output directly to the screen
//           Close input files



#include <iostream>  //cin, cout functions 
#include <fstream>   //ifstream, ofstream functions
#include <iomanip>   //setw()
#include <cstdlib>   //exit function
#include "graphType.h"

using namespace std;

//Function prototypes
void OpenInputFile (ifstream&, char[]);
void Choices(ifstream&, ifstream&, ifstream&, graphType&, graphType&, graphType&);
void PrintGraphs(ifstream&, graphType&);

int main()
{
    //print heading
	cout << "             OUTPUT FOR XINYI WANG LAB14	SPRING 2011" << endl << endl;

	graphType graph1(50), graph2(50), graph3(50);
	ifstream graphFile1, graphFile2, graphFile3;
	char inputFile1[30] = "graphSet1.dat";
	char inputFile2[30] = "graphSet2.dat";
	char inputFile3[30] = "graphSet3.dat";

    //check for successful open
	OpenInputFile(graphFile1, inputFile1);
	OpenInputFile(graphFile2, inputFile2);
	OpenInputFile(graphFile3, inputFile3);

    //Create graphs
	graph1.createGraph(graphFile1);
	graph2.createGraph(graphFile2);
	graph3.createGraph(graphFile3);

	//Print which graph or exit
	Choices(graphFile1, graphFile2, graphFile3, graph1, graph2, graph3);

	//close
	graphFile1.close();
	graphFile2.close();
	graphFile3.close();

	return 0;
}




//Purpose:        Open an input file and test for successful open
//Pre-condition:  File has been declared as input file stream, and file name is known
//Post-condition: File is open if successful, otherwise terminate the program
void OpenInputFile(ifstream& graphFile, char inputFile[])
{
   //Open input file
   graphFile.open(inputFile);

   //If not successful open, display message and exit with error
   if (!graphFile)
   {
      cout << "\n\n\n\t\t\t Error opening file!"
           << inputFile << endl;
      exit(1);
   }
} //End OpenInputFile


//Purpose:        Display a menu of choices to select the file name
//Pre-condition:  Files have been declared as input files stream, and and object graphs have been created
//Post-condition: Select the choice to diplay the graph if successful until enter "e" or "E" to exit the program
void Choices(ifstream& graphFile1, ifstream& graphFile2, ifstream& graphFile3, 
	         graphType& graph1, graphType& graph2, graphType& graph3)
{
	char ch;
	do
	{
	cout << "===================================================" << endl;
	cout << "Which graphSet do you want to process? (e for exit)" << endl;
	cout << "  a. graphSet1" << endl;
	cout << "  b. graphSet2" << endl;
	cout << "  c. graphSet3" << endl;
	cout << endl << "  e. EXIT" << endl;
	cout << "===================================================" << endl;
	cout << "Please enter the corresponding letter here: ";
	
	cin >> ch; cout << endl;
	switch (tolower(ch))
	{
	case 'a': cout << "Displaying the graphSet1: " << endl;
		PrintGraphs(graphFile1, graph1);
		break;
	case 'b': cout << "Displaying the graphSet2: " << endl;
		PrintGraphs(graphFile2, graph2);
		break;
	case 'c': cout << "Displaying the graphSet3: " << endl;
		PrintGraphs(graphFile3, graph3);
		break;
	case 'e': return;
		break;
	default: cout << endl << "The valid choices are a or A, b or B, and c or C, e or E for exit! " << endl;
	}
	} while (tolower(ch) != 'e');
}


//Purpose:        Display the graph by the three methods
//Pre-condition:  File has been declared as input file stream, and object graph has been created
//Post-condition: Print the graph directly to the screen if successful
void PrintGraphs(ifstream& graphFile, graphType& graph)
{
	cout << "1) Display the graph by calling printGraph: " << endl;
	graph.printGraph();
	cout << "2) Display the depth first traversal: " << endl << "   ";
	graph.depthFirstTraversal();
	cout << endl;
	cout << "3) Display the breadth first traversal: " << endl << "   ";
	graph.breadthFirstTraversal();
	cout << endl << endl;
}

