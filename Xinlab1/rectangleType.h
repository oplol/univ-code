//Name:      Xinyi Wang
//Course:    COSC 5321
//Semester:  Spring 2011
//the source code is from Malik, chapter 2

#ifndef H_rectangleType
#define H_rectangleType
 
#include <iostream>
  
using namespace std;

class rectangleType
{
      //Overload the stream insertion and extraction operators
    friend ostream& operator << (ostream&, const rectangleType &);  //function prototype
    friend istream& operator >> (istream&, rectangleType &);        //function prototype
public:
// After these two overloaded functions below moved from rectangleTypeImp.cpp to here and had them to be friend functions, the output stays the same.
// That's because...although a friend functions is not a member of this class rectangleType, the function can be declared as a friend of the class 
// so that the functions have access to all the members.
friend ostream& operator << (ostream& osObject, 
                      const rectangleType& rectangle)
{
    osObject << "Length = "  << rectangle.length 
             << "; Width = " << rectangle.width;

    return osObject;
}

friend istream& operator >> (istream& isObject, 
                      rectangleType& rectangle)
{
    isObject >> rectangle.length >> rectangle.width;

    return isObject;
}

    void setDimension(double l, double w);
    double getLength() const;
    double getWidth() const;
    double area() const;
    double perimeter() const;
    void print() const;

    rectangleType operator+(const rectangleType&) const;
      //Overload the operator +
    rectangleType operator*(const rectangleType&) const;
      //Overload the operator *

    bool operator==(const rectangleType&) const;
      //Overload the operator ==
    bool operator!=(const rectangleType&) const;
      //Overload the operator !=

    rectangleType();
    rectangleType(double l, double w);

private:
    double length;
    double width;
};



#endif

//
