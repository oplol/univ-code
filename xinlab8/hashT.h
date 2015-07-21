#ifndef H_Htable
#define H_Htable

//****************************************************************
// Author: D.S. Malik
//
// This class specifies the members to implement a hash table as 
// an ADT. It uses quadratic probing to resolve collisions.
//****************************************************************

#include <iostream>
#include <iomanip>
#include <cassert>
#include "linkedQueue.h"

using namespace std;

template <class elemType>
class hashT
{
public:
    void insert(int hashIndex, const elemType& rec);
      //Function to insert an item in the hash table. The first
      //parameter specifies the initial hash index of the item to 
      //be inserted. The item to be inserted is specified by the 
      //parameter rec.
      //Postcondition: If an empty position is found in the hash
      //   table, rec is inserted and the length is incremented 
      //   by one; otherwise, an appropriate error message is
      //   displayed.

    void search(int& hashIndex, const elemType& rec, 
                bool& found) const;
      //Function to determine whether the item specified by the
      //parameter rec is in the hash table. The parameter
      //hashIndex specifies the initial hash index of rec.
      //Postcondition: If rec is found, found is set to true and
      //   hashIndex specifies the position where rec is found;
      //   otherwise, found is set to false.

    bool isItemAtEqual(int hashIndex, const elemType& rec) const;
      //Function to determine whether the item specified by the
      //parameter rec is the same as the item in the hash table 
      //at position hashIndex.
      //Postcondition: Returns true if HTable[hashIndex] == rec;
      //   otherwise, returns false.

    void retrieve(int hashIndex, elemType& rec) const;
      //Function to retrieve the item at position hashIndex.
      //Postcondition: If the table has an item at position
      //   hashIndex, it is copied into rec.

    void remove(int hashIndex, const elemType& rec);
      //Function to remove an item from the hash table.
      //Postcondition: Given the initial hashIndex, if rec is 
      //   found
      //   in the table it is removed; otherwise, an appropriate
      //   error message is displayed.

    void print() const;
      //Function to output the data.

    hashT(int size = 101);
      //constructor
      //Postcondition: Create the arrays HTTable and 
      //   indexStatusList;
      //   initialize the array indexStatusList to 0; length = 0;
      //   HTSize = size; and the default array size is 101.

    ~hashT();
      //destructor
      //Postcondition: Array HTable and indexStatusList are 
      //               deleted.

	void search(int& hashIndex, const elemType& rec, bool& found, 
	            int& pCount, linkedQueueType<elemType>& probeSequence);
	  //Function to determine whether the item specified by the
      //parameter rec is in the hash table. The parameter
      //hashIndex specifies the initial hash index of rec.
	  //The parameter pCount is the number of probe.
	  //The parameter probeSequence is the probe sequence.
      //Postcondition: If rec is found, found is set to true and
      //   hashIndex specifies the position where rec is found;
      //   otherwise, found is set to false.
	  //   Function will print the value, whether or not it was found, 
	  //   the number of probes (key compares), and the probe sequence.

	int getLength() const;
	  //Function to return the number of elements in the hash table.
	  //Postcondition: The value of length is returned.

private:
    elemType *HTable;   //pointer to the hash table
    int *indexStatusList;  //pointer to the array indicating the
                           //status of a position in the hash table
    int length;    //number of items in the hash table
    int HTSize;    //maximum size of the hash table
};

template <class elemType>
void hashT<elemType>::insert(int hashIndex, const elemType& rec)
{
	int pCount;
	int inc;

	pCount = 0;
	inc = 1;

	while (indexStatusList[hashIndex] == 1
		  && HTable[hashIndex] != rec 
		  && pCount < HTSize / 2)
	{
		pCount++;
		hashIndex = (hashIndex + inc ) % HTSize;
		inc = inc + 2;
	}

	if (indexStatusList[hashIndex] != 1)
	{
		HTable[hashIndex] = rec;
		indexStatusList[hashIndex] = 1;
		length++;
	}
	else if (HTable[hashIndex] == rec)
        cerr << "Error: No duplicates are allowed" << endl;
     else
        cerr << "Error: The table is full. "
             <<"Unable to resolve the collision" << endl;
}

template <class elemType>
void hashT<elemType>::search(int& hashIndex, const elemType& rec, 
                             bool& found) const
{
	int pCount;
	int inc;

	pCount = 0;
	inc = 1;

	while (indexStatusList[hashIndex] != 0
		  && HTable[hashIndex] != rec 
		  && pCount < HTSize / 2)
	{
		pCount++;
		hashIndex = (hashIndex + inc ) % HTSize;
		inc = inc + 2;
	}

	if (indexStatusList[hashIndex] == 1 
             && HTable[hashIndex] == rec )
	{
		hashIndex = hashIndex;
		found = true;
	}
	else
		found = false;
}

template <class elemType>
bool hashT<elemType>::isItemAtEqual(int hashIndex, const elemType& rec) const
{ 
	return(HTable[hashIndex] == rec);
}

template <class elemType>
void hashT<elemType>::retrieve(int hashIndex, elemType& rec) const
{	
	if (indexStatusList[hashIndex] == 1)
		rec = HTable[hashIndex];
}

template <class elemType>
void hashT<elemType>::remove(int hashIndex, const elemType& rec)
{
	bool found;

	search(hashIndex, rec, found);

	if (found)
	{
		indexStatusList[hashIndex] = -1;
		length--;
	}
	else
		cerr << "The item to be deleted is not in the list."
             << endl;
}

template <class elemType>
void hashT<elemType>::print() const
{
	int j = 0;
    for (int i = 0; i < HTSize; i++)
	{
        if (indexStatusList[i] == 0)
		{
			j++;
			HTable[i] = 0;
		}
            cout << " [" << setw(2) << i << "]       " << indexStatusList[i]
                 << "         [" << setw(2) << i << "]   " << setw(3) << HTable[i] << endl;
	}
	cout << fixed << showpoint << setprecision(4);
	cout << "The load factor is: " << 1 - static_cast<float>(j)/static_cast<float>(HTSize) << endl;
}

template <class elemType>
hashT<elemType>::hashT(int size)
{
	assert(size > 0);

	HTable = new elemType[size];
	indexStatusList = new int[size];
	length = 0;
	HTSize = size;

	for (int i = 0; i < size; i++)
		indexStatusList[i] = 0;
}

template <class elemType>
hashT<elemType>::~hashT()
{
	delete [] HTable;
	delete [] indexStatusList;
}

template <class elemType>
void hashT<elemType>::search(int& hashIndex, const elemType& rec, bool& found, 
	                         int& pCount, linkedQueueType<elemType>& probeSequence)
{
	int inc;
	inc = 1;

	pCount = 0;
	probeSequence.initializeQueue();

	while (indexStatusList[hashIndex] != 0
		  && HTable[hashIndex] != rec 
		  && pCount < HTSize / 2)
	{
		pCount++;
		hashIndex = (hashIndex + inc ) % HTSize;
		inc = inc + 2;
		probeSequence.addQueue(HTable[hashIndex]);
	}

	if (indexStatusList[hashIndex] == 1 
             && HTable[hashIndex] == rec )
	{
		hashIndex = hashIndex;
		found = true;
	}
	else
		found = false;
	if (pCount == 0)
	{
		pCount++;
		probeSequence.addQueue(HTable[hashIndex]);
	}
}

template <class elemType>
int hashT<elemType>::getLength() const
{
	return length;
}

#endif
