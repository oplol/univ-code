//Name:      Xinyi Wang
//Course:    COSC 5312
//Prog#:     8
//Assigned:  April 12, 2011
//Date due:  April 19, 2011

#include <iostream>
#include <fstream>
#include "NumberList.h"

using namespace std;


void NumberList::displayList(ofstream& dataFileOut) const
{
	ListNode *nodePtr;  // To move through the list
	
	// Position nodePtr at the head of the list
	nodePtr = head;

	// While nodePtr points to a node, traverse
	// the list.
	while (nodePtr)
	{
		// Display the value in this node.
		dataFileOut << nodePtr->value << " ";

		// Move to the next node.
		nodePtr = nodePtr->next;
	}
}


void NumberList::insertNode(double num, ofstream& dataFileOut)
{
	ListNode *newNode;             // A new node
	ListNode *nodePtr;             // To traverse the list
	ListNode *previousNode = NULL; // The previous node
	bool found;

	// Allocate a new node and store num there.
	newNode = new ListNode;
	if (newNode == NULL)
	{
		dataFileOut << "INSERT Failed (OVERFLOW)" << endl;
		return;
	}
	newNode->value = num;

	// If there are no nodes in the list
	// make newNode the first node
	if (!head)
	{
		head = newNode;
		newNode->next = NULL;
		count++;
		dataFileOut << "INSERT Successful" << endl;
	}
	else   // Otherwise, insert newNode
	{
		found = false;
		// Position nodePtr at the head of list.
		nodePtr = head;

		// Initialize previuousNode to NULL.
		previousNode = NULL;

		// Skip all nodes whose value is less than num.
		while (nodePtr != NULL && !found)
			if (nodePtr->value >= num)
				found = true;
			else
		{
			previousNode = nodePtr;
			nodePtr = nodePtr->next;
		}
		if (found && nodePtr->value == num)
			dataFileOut << "INSERT Failed (DUPLICATE key)" << endl;
		else
		{
		// If the new node is to be the 1st in the list,
		// insert it before all other nodes.
		if (previousNode == NULL)
		{
			head = newNode;
			newNode->next = nodePtr;
			dataFileOut << "INSERT Successful" << endl;
		}
		else
			// Otherwise insert after the previous node.
		{
			previousNode->next = newNode;
			newNode->next = nodePtr;
			dataFileOut << "INSERT Successful" << endl;
		}
		count++;
		}
	}
}


void NumberList::deleteNode(double num, ofstream& dataFileOut)
{
	ListNode *nodePtr;       // To traverse the list
	ListNode *previousNode;  // To point to the previous node

	// If the list is empty, do nothing.
	if (!head)
		return;

	// Determine if the first node is the one.
	if (head->value == num)
	{
		nodePtr = head->next;
		delete head;
		head = nodePtr;
		dataFileOut << "DELETE Successful" << endl;
		count--;
	}
	else
	{
		// Initialize nodePtr to head of list
		nodePtr = head;

		// Skip all nodes whose value member is
		// not equal to num.
		while (nodePtr != NULL && nodePtr->value != num)
		{
			previousNode = nodePtr;
			nodePtr = nodePtr->next;
		}

		// If nodePtr is not at the end of the list,
		// link the previous node to the node after
		// nodePtr, then delete nodePtr.
		if (nodePtr)
		{
			previousNode->next = nodePtr->next;
			delete nodePtr;
			dataFileOut << "DELETE Successful" << endl; 
			count--;
		}
		else
			dataFileOut << "DELETE Failed (NOT in list)" << endl;
	}
}


NumberList::~NumberList()
{
	ListNode *nodePtr;   // To traverse the list
	ListNode *nextNode;  // To point to the next node

	// Position nodePtr at the head of the list.
	nodePtr = head;

	// While nodePtr is not at the end of the list...
	while (nodePtr != NULL)
	{
		// Save a pointer to the next node.
		nextNode = nodePtr->next;

		// Delete the current node.
		delete nodePtr;

		// Position nodePtr at the next node.
		nodePtr = nextNode;
	}

	count = 0;
}


int NumberList::length() const
{
	return count;
}


