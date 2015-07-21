//Name:     Xinyi Wang
//Course:   COSC 5321
//Lab #:    15
//Assigned: Apr 26, 2011
//Due:      May  3, 2011
//Purpose:  Illustrate the shortest path algorithm
//
//Input:    The graphs using file input from wgraphSet1.dat and wgraphSet2.dat.
//
//Output:   The output will be printed directly to the screen
//          then create a makefile.
//
//Program outline:
//           Open "wgraphSet1.dat" file for input1; test for successful open
//           Open "wgraphSet2.dat" file for input2; test for successful open
//           Create graph1 and graph2 by using the data from input file1 and file2
//           Find the shortest path from the vertex 0 to all of the other vertices
//           Include the appropriate headings/titles
//           Print all the output directly to the screen
//           Close input files



#include <iostream>  //cin, cout functions 
#include <fstream>   //ifstream, ofstream functions
#include <iomanip>   //setw()
#include <cstdlib>   //exit function
#include <cfloat>
#include "weightedGraph.h"

using namespace std;

//Function prototypes
void OpenInputFile (ifstream&, char[]);
void Choices(ifstream&, ifstream&, weightedGraphType&, weightedGraphType&);
void PrintGraphs(ifstream&, weightedGraphType&);

int main()
{
    //print heading
	cout << "             OUTPUT FOR XINYI WANG LAB15	SPRING 2011" << endl << endl;

	weightedGraphType wgraph1(50), wgraph2(50);
	ifstream graphFile1, graphFile2;
	char inputFile1[30] = "wgraphSet1.dat";
	char inputFile2[30] = "wgraphSet2.dat";

    //check for successful open
	OpenInputFile(graphFile1, inputFile1);
	OpenInputFile(graphFile2, inputFile2);
	
    //Create graphs
	wgraph1.createWeightedGraph(graphFile1);
	wgraph2.createWeightedGraph(graphFile2);
	
	//Create the smallestWeight matrix
	wgraph1.shortestPath(0);
	wgraph2.shortestPath(0);
	
	//Print which graph or exit
	Choices(graphFile1, graphFile2, wgraph1, wgraph2);

	//close
	graphFile1.close();
	graphFile2.close();

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
void Choices(ifstream& graphFile1, ifstream& graphFile2, 
	         weightedGraphType& graph1, weightedGraphType& graph2)
{
	char ch;
	do
	{
	cout << "====================================================" << endl;
	cout << "Which wgraphSet do you want to process? (e for exit)" << endl;
	cout << "  a. wgraphSet1" << endl;
	cout << "  b. wgraphSet2" << endl;
	cout << endl << "  e. EXIT" << endl;
	cout << "====================================================" << endl;
	cout << "Please enter the corresponding letter here: ";
	
	cin >> ch; cout << endl;
	switch (tolower(ch))
	{
	case 'a': cout << "Displaying the wgraphSet1: " << endl;
		PrintGraphs(graphFile1, graph1);
		break;
	case 'b': cout << "Displaying the wgraphSet2: " << endl;
		PrintGraphs(graphFile2, graph2);
		break;
	case 'e': return;
		break;
	default: cout << endl << "The valid choices are a or A and b or B, e or E for exit! " << endl;
	}
	} while (tolower(ch) != 'e');
}


//Purpose:        Display the graph by the three methods
//Pre-condition:  File has been declared as input file stream, and object graph has been created
//Post-condition: Print the graph directly to the screen if successful
void PrintGraphs(ifstream& graphFile, weightedGraphType& graph)
{
	cout << "1) Display the graph by calling printGraph: " << endl;
	graph.printGraph();
	cout << "2) Display the depth first traversal: " << endl << "   ";
	graph.depthFirstTraversal();
	cout << endl;
	cout << "3) Display the breadth first traversal: " << endl << "   ";
	graph.breadthFirstTraversal();
	cout << endl;
	cout << "4) Display the shortest distance from the vertex 0: " << endl << "   ";
	graph.printShortestDistance(0);
	cout << endl << endl;
}

