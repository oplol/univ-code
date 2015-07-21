//Name:      Xinyi Wang
//Course:    COSC 5312
//Prog#:     5
//Assigned:  February 22, 2011
//Date due:  March 1, 2011

#include <iostream>
#include <cstring>
#include <iomanip>
#include "XWEmployee.h"

void displayEmployee(Employee&);

using namespace std;


int main()
{
	//Create an Employee object to test constructor #1.
	Employee susan("Susan Meyers", 47899, "Accounting", "Vice President");

	//Create an Employee object to test constructor #2.
	Employee mark("Mark Jones", 39119);
	mark.setDepartment("IT");
	mark.setPosition("Programmer");

	//Create an Employee object to test constructor #3.
	Employee joy;
	joy.setName("Joy Rogers");
	joy.setIdNumber(81774);
	joy.setDepartment("Manufacturing");
	joy.setPosition("Engineer");

	//Display each employee's data.
    displayEmployee(susan);
	displayEmployee(mark);
	displayEmployee(joy);

	return 0;
}

void displayEmployee(Employee& objname)
{
	cout << "Display the data for an employee:\n";
	cout << "Name: " << objname.getName() << endl;
	cout << "ID Number: " << objname.getIdNumber() << endl;
	cout << "Department: " << objname.getDepartment() << endl;
	cout << "Position: " << objname.getPosition() << endl << endl;
}


