//Name:      Xinyi Wang
//Course:    COSC 5312
//Prog#:     9
//Assigned:  April 26, 2011
//Date due:  May    3, 2011

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "Stack.h"

using namespace std;

//Function prototypes
template <class T>
void calc(char*, Stack<T>&);

int main()
{
	//Print heading
    cerr << "     OUTPUT FOR Xinyi Wang XWLAB9 PROGRAM	Spring 2011" << endl  << endl;
	Stack<int> opstack(50);
	char postfix;

	calc(&postfix, opstack);
	
	return 0;
}



//function definitions................................................

//Purpose:        Evaluate the postfix expression unless the user wants to quit
//Pre-condition:  A pointer point to a array, and a stack has been declared
//Post-condition: The result is showed on the screen if successful
template <class T>
void calc(char *item, Stack<T>& opstack)
{
	do
	{
	cout << "==========Evaluate the postfix expression==========" << endl; 
	cout << "Enter the postfix expression below: ";
	
	int num, item1, item2, result;
	cin.get(*item);

	while (*item != '=')
	{
		switch (*item)
		{
		case '#': cout << "The character '#' is entered. Quit the program!" << endl;
			cout << "========================END========================" << endl << endl;
			return;
			break;
		default:
		if (*item != '+' && *item != '-' && *item != '*' && *item != '/')
		{
			num = atoi(item);
			opstack.push(num);
		}
		else
		{
			opstack.pop(item2);
			opstack.pop(item1);

			switch (*item)
			{
			case '+': opstack.push(item1 + item2);
				break;
			case '-': opstack.push(item1 - item2);
				break;
		    case '*': opstack.push(item1 * item2);
				break;
			case '/': if (item2 != 0)
						  opstack.push(item1 / item2);
				break;
			case '#': return;
				break;
			} //End switch
		} //End else
		} //End switch
		cin.get(*item);
	} //End while
	opstack.pop(result);
	cout << "The result is: " << result << endl;
	cout << "========================END========================" << endl << endl;
	} while (*item != '#');
}
