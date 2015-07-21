// Stack template
#ifndef H_Stack
#define H_Stack

#include <iostream>

using namespace std;

template <class T>
class Stack
{
private:
   T *stackArray;
   int stackSize;
   int top;

public:
   Stack(int);
   void push(T);
   void pop(T &);
   bool isFull();
   bool isEmpty();
};
   
//***************************************************
//  Constructor                                     *
//***************************************************

template <class T>
Stack<T>::Stack(int size)
{
   stackArray = new T[size]; 
   stackSize = size; 
   top = -1;
}


//*************************************************************
// Member function push pushes the argument onto              *
// the stack.                                                 *
//*************************************************************

template <class T>
void Stack<T>::push(T num)
{
   if (isFull())
   {
      cout << "The stack is full.\n";
      return;
   }
   else
   {
      top++;
      stackArray[top] = num;
   }
}
 
//*************************************************************
// Member function pop pops the value at the top              *
// of the stack off, and copies it into the variable          *
// passed as an argument.                                     *
//*************************************************************

template <class T>
void Stack<T>::pop(T &num)
{
   if (isEmpty())
   {
      cout << "The stack is empty.\n";
      return;
   }
   else
   {
      num = stackArray[top];
      top--;
   }
}

//*************************************************************
// Member function isFull returns true if the stack           *
// is full, or false otherwise.                               *
//*************************************************************

template <class T>
bool Stack<T>::isFull()
{
   if (top == stackSize - 1)
      return true;
   else return false;
}

//*************************************************************
// Member function isEmpty returns true if the stack          *
// is empty, or false otherwise.                              *
//*************************************************************

template <class T>
bool Stack<T>::isEmpty()
{
   if (top == -1)
      return true;
   else return false;
}

#endif
