//Name:      Xinyi Wang
//Course:    COSC 5334
//HW#:       6

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <cmath>


using namespace std;
const int size = 9999;
int pSize;
struct Point
{
	int x;
	int y;
};

void OpenInputFile (ifstream&, char []);
void OpenOutputFile (ofstream&, char []);
int crossProduct(Point, Point, Point);
double dis(Point, Point);
void GrahamScan(ifstream&, ofstream&, Point [], Point [], int &);


int main()
{
	int leng;
	Point set[size];
	Point stack[size];
	ifstream infile;
	ofstream outfile;
	char infileName[50]= "input1.txt";
	char outfileName[50] = "output1.txt";

	OpenInputFile (infile, infileName);
	OpenOutputFile (outfile, outfileName);

	GrahamScan(infile, outfile, set, stack, leng);

	infile.close();
	outfile.close();

	return 0;
}



//function definitions................................................
void OpenInputFile (ifstream& dataFileIn, char inputFile[])
{
	dataFileIn.open(inputFile);
	if (!dataFileIn)
    {
      cout << "\n\n\n\t\t\t Error opening file!"
           << inputFile << endl;
      exit(1);
    }
}

void OpenOutputFile (ofstream& dataFileOut, char outputFile[])
{
	dataFileOut.open(outputFile);
	if (!dataFileOut)
    {
      cout << "\n\n\n\t\t\t Error opening file!"
           << outputFile << endl;
      exit(1);
    }
}

int crossProduct(Point p0, Point p1, Point p2)
{
	return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}

double dis(Point a, Point b)
{
	return (sqrt(double((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y))));
}

void GrahamScan(ifstream& infile, ofstream& outfile, Point set[], Point stack[], int &length)
{
	
	infile >> pSize;
	cout << pSize << endl;
	outfile << pSize << endl;
	for (int in = 0; in < pSize; in++)
	{
		infile >> set[in].x;
		infile >> set[in].y;
		cout << set[in].x << "	" << set[in].y << endl;
		outfile << set[in].x << "	" << set[in].y << endl;
	}
	//Step 1
	int k = 0;
	Point temp;
	for (int i = 1; i < pSize; i++)
		if((set[i].y < set[k].y)||((set[i].y == set[k].y)&&(set[i].x < set[k].x)))
			k = i;

	temp = set[0];
	set[0] = set[k];
	set[k] = temp;

	//Step 2
	for (int i = 1; i < pSize -1; i++)
	{
		k=i;
		for (int j = i+1; j < pSize; j++)
			if ((crossProduct(set[0],set[j],set[k])>0)||((crossProduct(set[0],set[j],set[k])== 0)&&(dis(set[0],set[j])<dis(set[0],set[k]))))
				k=j;
		temp = set[i];
		set[i] = set[k];
		set[k] = temp;
	}

	//Step 3 Create Stack

	//Step 4
	int top = 2;
	stack[0] = set[0];
	stack[1] = set[1];
	stack[2] = set[2];
	
	//Step 5
	for (int i = 3; i < pSize; i++)
	{
		while(crossProduct(stack[top-1],set[i],stack[top]) >= 0)
			top--;
		stack[++top] = set[i];
	}
	length = top + 1;
	
	//Step 6
	cout << length + 4 << endl;
	outfile << length + 4 << endl;
	for (int i = length -1; i >= -4; i--)
	{
		cout << stack[i].x << "	" << stack[i].y << endl;
		outfile << stack[i].x << "	" << stack[i].y << endl;
	}
}


