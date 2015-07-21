//Name:     Xinyi Wang
//Course:   COSC 5321
//Lab #:    12
//Assigned: Apr  5, 2011
//Due:      Apr 12, 2011
//Purpose:  Create the class AVLTreeType
//          Create two AVL trees and invoke some of the class functions
//
//Input:    The trees using file input from lab12file1.dat and lab12file2.dat.
//
//Output:   The output will be printed directly to the screen
//          then redirect the screen output to the file "lab12report.txt"
//          then create a makefile.
//
//Program outline:
//           Open "lab12file1.dat" file for input1; test for successful open
//           Open "lab12file2.dat" file for input2; test for successful open
//           Read from the input file1 and file2
//           Create tree1 and tree2 by using the data from input file1 and file2
//           Include the appropriate headings/titles
//           Print all the output directly to the screen, then redirect to the file "lab12report.txt"
//           Close both files


#include <iostream>  //cin, cout functions 
#include <fstream>   //ifstream, ofstream functions
#include <iomanip>   //setw()
#include <cstdlib>   //exit function
#include "avlTree.h"

using namespace std;

//Function prototypes
void OpenInputFile (ifstream&, char[]);
template <class elemT>
void ReadAndWriteFiles(ifstream&, AVLTreeType<elemT>&);

int main()
{
	AVLTreeType<int> tree1, tree2;
	ifstream dataFileIn1, dataFileIn2;
	char inputFile1[30] = "lab12file1.dat";
	char inputFile2[30] = "lab12file2.dat";

	//print heading
	cout << "             OUTPUT FOR XINYI WANG LAB12	SPRING 2011" << endl;

	//diplay tree1
	cout << endl << "1. Displaying the tree1" << endl;
	OpenInputFile(dataFileIn1, inputFile1);
	ReadAndWriteFiles(dataFileIn1,tree1);

	//diplay tree2
	cout << endl << "2. Displaying the tree2" << endl;
	OpenInputFile(dataFileIn2, inputFile2);
	ReadAndWriteFiles(dataFileIn2, tree2);

	//close
	dataFileIn1.close();
	dataFileIn2.close();

	return 0;
}




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


//Purpose:        Read from an input file and create tree, then display the tree
//Pre-condition:  Input file have been successfully opened
//Post-condition: The output for tree is printed to the screen according to data from the input file
template <class elemT>
void ReadAndWriteFiles(ifstream& dataFileIn, AVLTreeType<elemT>& tree)
{
	int num;
	dataFileIn >> num;
    //While not end-of-file
    while(!dataFileIn.eof())
	{
		tree.insert(num);
		dataFileIn.ignore(81, '\n');
		dataFileIn >> num;
	} //End while

	//the three traverasls
	cout << "   1) The three traversals:";
	cout << endl << "       Inorder traversal:" << endl << "        ";
	tree.inorderTraversal();
	cout << endl << "       Preorder traversal:" << endl << "        ";
	tree.preorderTraversal();
	cout << endl << "       Postorder traversal:" << endl << "        ";
	tree.postorderTraversal();
	cout << endl;

	//height
	cout << "   2) The height of the tree: " << tree.treeHeight() << endl;

	//the number of nodes in the tree
	cout << "   3) The number of nodes in the tree: " << tree.treeNodeCount() << endl;

	//the number of leaves in the tree
	cout << "   4) The number of leaves in the tree: " << tree.treeLeavesCount() << endl;
}



