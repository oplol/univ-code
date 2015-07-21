//Name:      Xinyi Wang
//Course:    COSC 5312
//Prog#:     8
//Assigned:  April 12, 2011
//Date due:  April 19, 2011

// Specification file for the NumberList class
#ifndef NUMBERLIST_H
#define NUMBERLIST_H

#include <iostream>
#include <fstream>
using namespace std;


class NumberList
{
private:
	// Declare a structure for the list
	struct ListNode
	{
		double value;           // The value in this node
		struct ListNode *next;  // To point to the next node
	};

	ListNode *head;            // List head pointer
	int count;                 // variable to store the number of list elements

public:
	// Constructor
	NumberList()
	{ head = NULL; count = 0;}

	// Destructor
	~NumberList();

    // Lisnked list length
	int length() const;

	// Linked list operations
	void insertNode(double, ofstream&);
	void deleteNode(double, ofstream&);
	void displayList(ofstream&) const;
};
#endif


