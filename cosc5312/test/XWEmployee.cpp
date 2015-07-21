//Name:      Xinyi Wang
//Course:    COSC 5312
//Prog#:     5
//Assigned:  February 22, 2011
//Date due:  March 1, 2011

#include <iostream>
#include <cstring>
#include "XWEmployee.h"

using namespace std;

const int DEFAULT_SIZE = 100;


Employee::Employee(char *nam, int idn, char *dpt, char *pos)
{
	name = new char [strlen(nam) + 1];
	strcpy(name, nam);

	idNumber = idn;

	department = new char [strlen(dpt) + 1];
	strcpy(department, dpt);

	position = new char [strlen(pos) + 1];
	strcpy(position, pos);
}

Employee::Employee(char *nam, int idn)
{
	name = new char [strlen(nam) + 1];
	strcpy(name, nam);

	idNumber = idn;

	department = new char [DEFAULT_SIZE];
	*department = '\0';

	position = new char [DEFAULT_SIZE];
	*position = '\0';
}

Employee::Employee()
{
	name = new char [DEFAULT_SIZE];
	*name = '\0';

	idNumber = 0;

	department = new char [DEFAULT_SIZE];
	*department = '\0';

	position = new char [DEFAULT_SIZE];
	*position = '\0';
}

Employee::~Employee()
{
	delete [] name;
	delete [] department;
	delete [] position;
}

void Employee::setName(char *nam)
{
	strcpy(name, nam);
}

void Employee::setIdNumber(int idn)
{
	idNumber = idn;
}

void Employee::setDepartment(char *dpt)
{
	strcpy(department, dpt);
}

void Employee::setPosition(char *pos)
{
	strcpy(position, pos);
}

const char *Employee::getName() const
{
	return name;
}

const int Employee::getIdNumber() const
{
	return idNumber;
}

const char *Employee::getDepartment() const
{
	return department;
}

const char *Employee::getPosition() const
{
	return position;
}


