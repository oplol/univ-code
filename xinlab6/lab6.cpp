//Name:     Xinyi Wang
//Course:   COSC 5321
//Lab #:    6
//Assigned: Feb 15, 2011
//Due:      Feb 22, 2011
//Purpose:  Use a stack (linked implementation) to convert infix notation
//          to postfix notation.
//
//Input:    Create infix notation using file input from lab6.dat. 
//
//Output:   All output directed to the screen.


#include <iostream>  //cin, cout functions
#include <fstream>   //ifstream function
#include <iomanip>   //setw()
#include "stackADT.h"
#include "linkedStack.h"

using namespace std;

//Function prototypes
void OpenInputFile (ifstream&, char[]);
int setopr(char);
template <class Type>
void convertInToPost(char[], linkedStackType<Type> &);

int main()
{
   const int SIZE = 100;
   char infixstring[SIZE];
   linkedStackType<char> opropr;
   //Input file stream
   ifstream dataFileIn;
   //Input file name
   char inputFile[30] = "lab6.dat";
   //Function call to open the input file
   OpenInputFile(dataFileIn, inputFile);
   //Print heading
   cout << endl;
   cout << "       OUTPUT FOR XINYI WANG LAB6    SPRING 2011" << endl;
   cout << endl;
   cout << "           INFIX NOTATION | POSTFIX NOTATION" << endl;
   dataFileIn >> infixstring;
   convertInToPost(infixstring, opropr);
   dataFileIn >> infixstring;
   convertInToPost(infixstring, opropr);
   dataFileIn >> infixstring;
   convertInToPost(infixstring, opropr);
   dataFileIn >> infixstring;
   convertInToPost(infixstring, opropr);
   dataFileIn >> infixstring;
   convertInToPost(infixstring, opropr);
   cout << endl;
   //Close input file
   dataFileIn.close();
   
   return 0;
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


//Set operator priorities
int setopr(char opr)
{
	if (opr == '*' || opr == '/')
		return 2;
	else if (opr == '+' || opr == '-')
		return 1;
	else if (opr == '(')
		return 0;
	else
	{
		cout << "Invalid expresstion!\n";
		exit(0);
	}
}


//Convert infix notation to postfix notation
template <class Type>
void convertInToPost(char infix[], linkedStackType<Type> &oprstack)
{
   char postfixstr[100];
   char operator1;
   //convert infix to postfix
   int slen;
   slen = strlen(infix);
   int i, j;
   j = 0;
   for (i = 0; i < slen; i++)
   {
	   if (infix[i] != '+' && infix[i] != '-' && infix[i] != '*' && infix[i] != '/' && infix[i] != '(' && infix[i] != ')')
	   {
		   postfixstr[j] = infix[i];
		   j++;
	   }
	   else
	   {
		   switch (infix[i])
	   {
		   case '(':
			   oprstack.push(infix[i]);
			   break;
		   case ')':
			   operator1 = oprstack.top();
			   oprstack.pop();
			   while (operator1 != '(')
			       {
				   postfixstr[j] = operator1;
				   j++;
			       if (!oprstack.isEmptyStack())
				   {
					   operator1 = oprstack.top();
				       oprstack.pop();
				   } //End if
				   else break;
			       } //End while
			   break;
		   default:
			   if (oprstack.isEmptyStack())
				   oprstack.push(infix[i]);
			   else
			   {
				   operator1 = oprstack.top();
			       oprstack.pop();
			   while (setopr(operator1) >= setopr(infix[i]))
			       {
				   postfixstr[j] = operator1;
				   j++;
				   if (!oprstack.isEmptyStack())
				   {
					   operator1 = oprstack.top();
				       oprstack.pop();
				   }
				   else break;
			       } //End while
			   if (setopr(operator1) < setopr(infix[i]))
			       {
				   oprstack.push(operator1);
				   oprstack.push(infix[i]);
			       }
			   } //End else
	   } //End swtich
	   } //End else
   } //End for loop
   while (!oprstack.isEmptyStack())
   {
	   postfixstr[j] = oprstack.top();
	   j++;
	   oprstack.pop();
   }
   cout << setw(25) << infix << " = ";
   for (int k = 0; k < j; k++)
   cout << postfixstr[k];
   cout << endl;
}


