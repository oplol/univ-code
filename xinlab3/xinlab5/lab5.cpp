//Name:     Xinyi Wang
//Course:   COSC 5321
//Lab #:    5
//Assigned: Feb  8, 2011
//Due:      Feb 15, 2011
//Purpose:  Create a recursive function to convert a decimal (base 10) integer 
//          to another base.


#include <iostream>

using namespace std;

void decToBase(int num, int base);
void cinValues();
void keepConvertingOrNot();

int main()
{
	cout << endl << "1. The outputs for checking: " << endl;
	//To ouput: 753 (base 10) = 1361 (base 8)
	cout << "   753" << " (base 10)" << " = ";
	decToBase(753,8);
	cout << " (base 8)" << endl;
	//To ouput: 753 (base 10) = 2F1 (base 16)
	cout << "   753" << " (base 10)" << " = ";
	decToBase(753,16);
	cout << " (base 16)" << endl;
	//To ouput: 79 (base 10) = 3J (base 20)
	cout << "   79" << " (base 10)" << " = ";
	decToBase(79,20);
	cout << " (base 20)" << endl;


	cout << endl << endl << "2. Convert any non-negative decimal number to any base between 2 and 20: " << endl;
    cinValues();
	keepConvertingOrNot();
	
	return 0;
}



//function definitions................................................

//Purpose:        Convert a (non-negative) decimal number to a given base, which is between 2 and 20
//Pre-condition:  The values of the variables num and base are ready for this conversion
//Post-condition: An inputted decimal number is successfully converted to the base you want
void decToBase(int num, int base)
{
	if (num >0)
	{
	decToBase(num/base, base);

	if (num % base < 10)
		cout << num % base;
	else
	    switch (num % base)
	    {
	    case 10: cout << 'A';
		         break;
	    case 11: cout << 'B';
		         break;
	    case 12: cout << 'C';
		         break;
	    case 13: cout << 'D';
		         break;
	    case 14: cout << 'E';
		         break;
	    case 15: cout << 'F';
		         break;
        case 16: cout << 'G';
		         break;
	    case 17: cout << 'H';
		         break;
	    case 18: cout << 'I';
		         break;
	    case 19: cout << 'J';
		         break;
	   }
	}
}



//Purpose:        Convert any (non-negative) decimal number to any base between 2 and 20
//Pre-condition:  Key in the values of the variables num and base until it is validated that they are in the corret range
//Post-condition: An inputted decimal number is successfully converted to the base you want
void cinValues()
{
	int num, base;
	cout << "  Please enter your non-negative decimal number for this conversion: ";
	cin >> num;
	while (num < 0)
	{
		cout << "   ATTENTION, please enter your NON-NEGATIVE decimal number: ";
		cin >> num;
	}
	cout << "  Please enter your base between 2 and 20 for this conversion: ";
	cin >> base;
	while (base < 2 || base > 20)
	{
		cout << "   ATTENTION, please enter your base BETWEEN 2 AND 20: ";
		cin >> base;
	}
	cout << "    The output is " << num << " (base 10)" << " = ";
	decToBase(num,base);
	cout << " (base " << base << ")" << endl;
}



//Purpose:        Convert any (non-negative) decimal number to any base between 2 and 20 as many times as he/she wishes until he/she says N
//Pre-condition:  A conversion is performed successfully
//Post-condition: After a successful conversion, you will be asked whether or not to perform another conversion (Y means continue; N means end)
void keepConvertingOrNot()
{
	char ch;
	cout << endl << "   Would you like to convert another non-negative decimal number? (Y/N) ";
	cin >> ch;
	while (ch != 'N')
	{
	switch (ch)
	{
	case 'Y': cinValues();
		      break;
	case 'N': ch = 'N';
		      break;
	default: cout << "     You did NOT enter Y or N! Please enter Y or N, and it is CASE-SENSITIVE!\n";
	} //End switch
	cout << endl << "   Would you like to convert another non-negative decimal number? (Y/N) ";
	cin >> ch;
	} //End while
}


