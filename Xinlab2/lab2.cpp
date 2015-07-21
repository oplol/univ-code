//Name:     Xinyi Wang
//Course:   COSC 5321
//Lab #:    2
//Assigned: Jan 25, 2011
//Due:      Feb  1, 2011
//Purpose:  To create and access an unordered linked list and an ordered linked list.
//
//Input:    create lists using file input from lab2.dat. Use keyboard input for
//          search values.
//
//Output:   All output directed to the screen.
//
//Program Outline/Design:
//        1. the "forward" unordered linked list 1
//           1) Open a file for input; test for successful open
//           2) Read from the input file using the ignore function
//           3) Using insertLast() to create the "forward" unordered linked list and print it
//           4) Using an iterator display the list
//           5) Display the length of the list and its first and last nodes
//           6) Destroy the list
//        2. the "backward" unordered linked list 2
//           Repeat the step 1) through 6) above, except 3) Using insertFirst() to create the "backward" unordered linked list instead
//        3. the ordered linked list
//           Repeat the step 1) through 5) above, except 3) Using insert() to create the order lined list instead
//


#include <iostream>  //cin, cout functions
#include <fstream>   //ifstream function
#include <iomanip>   //setw()
#include "linkedList.h"
#include "orderedLinkedList.h"
#include "unorderedLinkedList.h"
using namespace std;

//Function prototypes
void OpenInputFile (ifstream&, char[]);

int main()
{
	unorderedLinkedList<int> ulist1, ulist2;
	orderedLinkedList<int> olist;
	linkedListIterator<int> it;
	int num1, num2, num3, searchnum, i;
	char ch;

   //Input file stream
   ifstream dataFileIn;
   //Input file name
   char inputFile[30] = "lab2.dat";
   

   //Forward order of unordered linked list
   //
   //Function call to open the input file
   OpenInputFile(dataFileIn, inputFile);

   //Read from input file
   dataFileIn >> num1;
   //While not end-of-file
   while(!dataFileIn.eof())
   {
	  //Read next characters, ie '\n'
	  dataFileIn.ignore(81, '\n');
      //forming a unorderedlinkedlist
      ulist1.insertLast(num1);
      //Read from input file
      dataFileIn >> num1;
   } //End while
   //Display the list on the screen using the print() function
   cout << endl << "The unordered linked list 1 is: " << endl;
   ulist1.print();
   cout << endl << endl;

   //Display the list again using an iterator. (Display each element on one line with an index.)
   cout << "Show the unordered linked list 1 by using an iterator: " << endl;
   it = ulist1.begin();
   i=1;
   while(it != ulist1.end())
   {
	   cout << setw(2) << i << ". " << *it << endl;
	   ++it;
	   i++;
   }

   //the length of the list
   cout << endl << "The length of the list 1 is " << ulist1.length() << endl;

   //the info field from the first and last nodes
   cout << "The info field from the first and last nodes are " << ulist1.front() << " and " << ulist1.back() << endl;

   //Search the list
   cout << endl << "Enter the number to be searched: ";
   cin >> searchnum;
   if (ulist1.search(searchnum))
	   cout << searchnum << " is found in the list." << endl;
   else
	   cout << searchnum << " is NOT found in the list." << endl;

   //Distroy the list 1
   ulist1.destroyList();
   //Close input file
   dataFileIn.close();
   //press any key to continue
   cout << endl; system("PAUSE"); 

   //Backward order of unordered linked list
   //
   //Function call to open the input file
   OpenInputFile(dataFileIn, inputFile);

   //Read from input file
   dataFileIn >> num2;
   //While not end-of-file
   while(!dataFileIn.eof())
   {
	  //Read next characters, ie '\n'
	  dataFileIn.ignore(81, '\n');
      //forming a unorderedlinkedlist
      ulist2.insertFirst(num2);
      //Read from input file
      dataFileIn >> num2;
   } //End while
   //Display the list on the screen using the print() function
   cout << endl << "The unordered linked list 2 is: " << endl;
   ulist2.print();
   cout << endl << endl;

   //Display the list again using an iterator. (Display each element on one line with an index.)
   cout << "Show the unordered linked list 2 by using an iterator: " << endl;
   it = ulist2.begin();
   i=1;
   while(it != ulist2.end())
   {
	   cout << setw(2) << i << ". " << *it << endl;
	   ++it;
	   i++;
   }

   //the length of the list
   cout << endl << "The length of the list 2 is " << ulist2.length() << endl;

   //the info field from the first and last nodes
   cout << "The info field from the first and last nodes are " << ulist2.front() << " and " << ulist2.back() << endl;

   //Search the list
   cout << endl << "Enter the number to be searched: ";
   cin >> searchnum;
   if (ulist2.search(searchnum))
	   cout << searchnum << " is found in the list." << endl;
   else
	   cout << searchnum << " is NOT found in the list." << endl;

   //Distroy the list 2
   ulist2.destroyList();
   //Close input file
   dataFileIn.close();
   //press any key to continue
   cout << endl; system("PAUSE"); 

   //ordered linked list
   //
   //Function call to open the input file
   OpenInputFile(dataFileIn, inputFile);

   //Read from input file
   dataFileIn >> num3;
   //While not end-of-file
   while(!dataFileIn.eof())
   {
	  //Read next characters, ie '\n'
	  dataFileIn.ignore(81, '\n');
      //forming a unorderedlinkedlist
      olist.insert(num3);
      //Read from input file
      dataFileIn >> num3;
   } //End while
   //Display the list on the screen using the print() function
   cout << endl << "The ordered linked list is: " << endl;
   olist.print();
   cout << endl << endl;

   //Display the list again using an iterator. (Display each element on one line with an index.)
   cout << "Show the ordered linked list by using an iterator: " << endl;
   it = olist.begin();
   i=1;
   while(it != olist.end())
   {
	   cout << setw(2) << i << ". " << *it << endl;
	   ++it;
	   i++;
   }

   //the length of the list
   cout << endl << "The length of the list is " << olist.length() << endl;

   //the info field from the first and last nodes
   cout << "The info field from the first and last nodes are " << olist.front() << " and " << olist.back() << endl;

   //Search the list
   cout << endl << "Enter the number to be searched: ";
   cin >> searchnum;
   if (olist.search(searchnum))
	   cout << searchnum << " is found in the list." << endl;
   else
	   cout << searchnum << " is NOT found in the list." << endl;

   //Close input file and end the program
   dataFileIn.close();
   cout << endl;
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


