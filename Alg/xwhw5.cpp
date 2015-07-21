//Name:      Xinyi Wang
//Course:    COSC 5334
//HW#:       5

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <queue>


using namespace std;
void OpenInputFile (ifstream&, char []);
void OpenOutputFile (ofstream&, char []);
void ReadAndWriteFiles1(ifstream&, ofstream&);
void ReadAndWriteFiles2(ifstream&, ofstream&);
int findset(int);
void unionnode(int, int);
void Kruskal();

const int ArraySize = 999;
char adjmatrix[ArraySize][ArraySize];
char vertexfrom[ArraySize], vertexto[ArraySize], weighted[ArraySize];
char MSTvertexfrom[ArraySize], MSTvertexto[ArraySize], MSTweighted[ArraySize], MSTnode[ArraySize];
char nodes, blank, vertex1, vertex2;
int gSize, edges;

struct EdgeNode
{
	int v1;
	int v2;
	int value;

	bool operator<(const EdgeNode &a) const
	{
		return a.value<value;
	}
};

int *root;
priority_queue<EdgeNode> pq;


int main()
{
	ifstream infile;
	ofstream outfile1, outfile2;

	char infileName[50]/*= "graphfile.dat"*/;

	cout << "Please enter the input file name: ";
	cin >> infileName;
	cout << endl;

	char outfileName1[50] = "input.gv";
	char outfileName2[50] = "output.gv";

	OpenInputFile (infile, infileName);
	OpenOutputFile (outfile1, outfileName1);
	OpenOutputFile (outfile2, outfileName2);
	
	ReadAndWriteFiles1(infile, outfile1);
	ReadAndWriteFiles2(infile, outfile2);

	infile.close();
	outfile1.close();
	outfile2.close();

	/*int n = 0, m = 0;
	cout << "enter how many nodes: " << endl;
	cin >> n;
	root = new int[gSize+1];
	for (int i = 1; i <= gSize; i++)
		root[i] = i;

	cout << "enter how many edges: " << endl;
	cin >> m;

	EdgeNode a;

	cout << "enter v1 and v2 and weight: " << endl;
	while (m--)
	{
		cin >> a.v1 >> a.v2 >> a.value;
		pq.push(a);
	}
	Kruskal();*/


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

void ReadAndWriteFiles1(ifstream& infile, ofstream& outfile)
{
	infile >> gSize;
	infile.ignore(81, '\n');
	
	for (int i = 0; i <= gSize; i++)
		for (int j = 0; j <= gSize; j++)
			adjmatrix[i][j] = '0';

	adjmatrix[0][0] = '\0';

	for (int i = 0; i < gSize; i++)
	{
		infile >> adjmatrix[0][i+1];
		adjmatrix[i+1][0] = adjmatrix[0][i+1];
		infile.get(blank);
	}
	
	infile >> edges;
	infile.ignore(81, '\n');
	
	for (int i = 0; i < edges; i++)
	{
		int m,n;
		infile >> vertexfrom[i];
		for (int j = 1; j <= gSize; j++)
		{
			if (adjmatrix[0][j] == vertexfrom[i])
				m = j;
		}
		infile.get(blank);
		infile >> vertexto[i];
		for (int k = 1; k <= gSize; k++)
		{
			if (adjmatrix[k][0] == vertexto[i])
				n = k;
		}
		infile.get(blank);
		infile >> weighted[i];
		adjmatrix[m][n] = weighted[i];
		infile.ignore(81, '\n');
	}

	//print out the adjacency matrix to the screen
	cout << "The adjacency-matrix representation of graph is: " << endl;
	for (int i = 0; i <= gSize; i++)
	{
		for (int j = 0; j <= gSize; j++)
			cout << setw(3) << adjmatrix[i][j];
	cout << endl;
	}

	//write input.gv
	outfile << "graph G" << endl;
    outfile << "{" << endl;

    for (int i = 0; i < edges; i++)
		outfile << "\t" << vertexfrom[i] << " -- " << vertexto[i] << " [label=\"" << weighted[i] << "\"];" << endl;

	outfile << "}" << endl;
}

void ReadAndWriteFiles2(ifstream& infile, ofstream& outfile)
{
	//MST-KRUSKAL
	bool swap;
	int temp;
	char temp1, temp2;

	 //sort the edges of G.E into nondecreasing order by weight
	do
	{
		swap = false;
		for (int count = 0; count < edges-1; count ++)
		{
			if (weighted[count] > weighted [count + 1])
			{
				temp = weighted[count];
				weighted[count] = weighted [count + 1];
				weighted[count + 1] = temp;

				temp1 = vertexfrom[count];
				vertexfrom[count] = vertexfrom[count + 1];
				vertexfrom[count + 1] = temp1;

				temp2 = vertexto[count];
				vertexto[count] = vertexto[count + 1];
				vertexto[count + 1] = temp2;

				swap = true;
			}
		}
	} while (swap);


	cout << endl << "The minimum spanning tree is: " << endl;
	

	root = new int[gSize+1];
	for (int i = 1; i <= gSize; i++)
		root[i] = i;
	
	cout << "There are " << gSize << " nodes and " << edges << " edges in this graph!" << endl;

	EdgeNode a;

	for (int count = 0; count < edges; count++)
	{
		a.v1 = static_cast<int>(vertexfrom[count])-96;
		//cout << static_cast<int>(vertexfrom[count]) -64 << " ";
		a.v2 = static_cast<int>(vertexto[count])-96;
		//cout << static_cast<int>(vertexto[count]) -64 << " ";
		a.value = static_cast<int>(weighted[count]) -48;
		//cout << static_cast<int>(weighted[count]) -48 << endl;

		pq.push(a);
	}
	/*Kruskal*/
	outfile << "graph G" << endl;
    outfile << "{" << endl;
	cout << "  Edges     Weight: " << endl;
	while(!pq.empty())
	{
		a = pq.top();
		pq.pop();

		if (findset(a.v1) != findset(a.v2))
		{
			outfile << "\t" << static_cast<char>(a.v1+96) << " -- " << static_cast<char>(a.v2+96) << " [label=\"" << a.value << "\"];" << endl;
			cout << "   " << static_cast<char>(a.v1+96) << "--" << static_cast<char>(a.v2+96) << "        " << a.value << endl;

			unionnode(a.v1, a.v2);
		}
	}
	outfile << "}" << endl;
}

int findset(int x)
{
	int i = x;

	while (i != root[i])
		i = root[i];
	while (i != root[x])
	{
		x = root[x];
		root[x] = i;
	}
	return i;
}

void unionnode(int a, int b)
{
	a = findset(a);
	b = findset(b);

	if (a!=b)
		root[a] = b;
}

//void Kruskal()
//{
//	EdgeNode b;
//
//	cout << "MST edge: " << endl;
//
//	while(!pq.empty())
//	{
//		b = pq.top();
//		pq.pop();
//
//		if (findset(b.v1) != findset(b.v2))
//		{
//			cout << b.v1 << "----" << b.v2 << endl;
//
//			unionnode(b.v1, b.v2);
//		}
//	}
//}

