//Name:     Xinyi Wang
//Course:   COSC 5321
//Lab #:    3
//Assigned: Feb 1, 2011
//Due:      Feb 8, 2011
//Purpose:  Complete and modify functions in the doubly linked list class.
//          Add new functions to the class.
//
//Input:    Create doubly linked lists using file input from lab2.dat. 
//
//Output:   All output directed to the screen.
//
//Program Outline/Design:
//          1. Forward order using the print function
//          2. Reverse order using the reversePrint function
//          3. Forward order using the getItemForward function
//          4. Reverse order using the getItemReverse function
//          5. Copy the list, and repeat the step 3 and 4


#include <iostream>  //cin, cout functions
#include <fstream>   //ifstream function
#include <iomanip>   //setw()
#include "doublyLinkedList.h"
using namespace std;

//Function prototypes
void OpenInputFile (ifstream&, char[]);
template<class Type>
void ReadFilesandCreateList(ifstream& dataFileIn, doublyLinkedList<Type> &);
template<class Type>
void PrintDoublyLinkedListForward(doublyLinkedList<Type> &);
template <class Type>
void PrintDoublyLinkedListReverse(doublyLinkedList<Type> &);
template <class Type>
void getItemDoublyLinkedListForward(doublyLinkedList<Type> &);
template <class Type>
void getItemDoublyLinkedListReverse(doublyLinkedList<Type> &);


int main()
{
   doublyLinkedList<int> list1, list2;
   //Input file stream
   ifstream dataFileIn;
   //Input file name
   char inputFile[30] = "lab2.dat";

   //Create a doubly linked list without a duplicate
   //
   //Function call to open the input file
   OpenInputFile(dataFileIn, inputFile);
   ReadFilesandCreateList(dataFileIn,list1);
   cout << endl;

   //Forward order using the print function
   cout << "1. The doubly linked list with forward order using the print function is: " << endl;
   PrintDoublyLinkedListForward(list1);
   //Reverse order using the reversePrint function
   cout << "2. The doubly linked list with reverse order using the reversePrint function is: " << endl;
   PrintDoublyLinkedListReverse(list1);
   //Forward order using the getItemForward function
   cout << "3. The doubly linked list with forward order using the getItemForward function is: " << endl;
   getItemDoublyLinkedListForward(list1);
   //Reverse order using the getItemReverse function
   cout << "4. The doubly linked list with reverse order using the getItemReverse function is: " << endl;
   getItemDoublyLinkedListReverse(list1);
   
   //Create a sencond list that is a copy of the original list
   list2=list1;
   //Print the copied list in forward order and in reverse order using the getItemForward and getItemReverse function as before
   cout << "5. The copied doubly linked list with forward order using the getItemForward function is: " << endl;
   getItemDoublyLinkedListForward(list2);
   cout << "6. The copied doubly linked list with reverse order using the getItemReverse function is: " << endl;
   getItemDoublyLinkedListReverse(list2);
}




//function definitions................................................

//Purpose:        Open an input file and test for successful open
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

//Read from an input file, then create a doubly linked list
template <class Type>
void ReadFilesandCreateList(ifstream& dataFileIn, doublyLinkedList<Type> &dList)
{
   int num;
   //Read from input file
   dataFileIn >> num;
   //While not end-of-file
   while(!dataFileIn.eof())
   {
	  //Read next characters, ie '\n'
	  dataFileIn.ignore(81, '\n');
      //forming a unorderedlinkedlist
      dList.insert(num);
      //Read from input file
      dataFileIn >> num;
   } //End while
}

//Forward order using the print function
template <class Type>
void PrintDoublyLinkedListForward(doublyLinkedList<Type> &dList)
{
   dList.print();
   cout << endl << endl;
}

//Reverse order using the reversePrint function
template <class Type>
void PrintDoublyLinkedListReverse(doublyLinkedList<Type> &dList)
{
   dList.reversePrint();
   cout << endl << endl;
}

//Forward order using the getItemForward function
template <class Type>
void getItemDoublyLinkedListForward(doublyLinkedList<Type> &dList)
{
   int indexnum = 20;
   for (int a = 1; a <= indexnum; a++)
   {
   cout << setw(3) << a << ". ";
   dList.getItemForward(a);
   cout << endl;
   }
   cout << endl;
}

//Reverse order using the getItemReverse function
template <class Type>
void getItemDoublyLinkedListReverse(doublyLinkedList<Type> &dList)
{
   int indexnum = 20;
   for (int a = 1; a <= indexnum; a++)
   {
   cout << setw(3) << a << ". ";
   dList.getItemReverse(a);
   cout << endl;
   }
   cout << endl;
}


