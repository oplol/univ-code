//Name:      Xinyi Wang
//Course:    COSC 5312
//Prog#:     5
//Assigned:  February 22, 2011
//Date due:  March 1, 2011

#ifndef H_Employee
#define H_Employee

#include <iostream>
#include <cstring>

using namespace std;


class Employee
{
private:
	char *name;
	int idNumber;
	char *department;
	char *position;
public:
	// Constructor #1
	Employee(char*, int , char*, char*);

	// Constructor #2
	Employee(char*, int);

	// Constructor #3
	Employee();

	// Destructor
	~Employee();

    // Mutator functions
	void setName(char*);
	void setIdNumber(int);
	void setDepartment(char*);
	void setPosition(char*) ;

	// Accessor functions
	const char *getName() const;
	const int getIdNumber() const;
	const char *getDepartment() const;
	const char *getPosition() const;
};

#endif


