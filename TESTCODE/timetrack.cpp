#include <iostream>
#include <cstdlib>
#include <ctime>


using namespace std;

int main()
{
	clock_t startc = clock();
	cout << clock() << endl;
	time_t end, start;
	int a = 0 , b = 0;
	double dif_total = 0.00;
	time (&start);
	while (a < 100000)
	{
		for (int i=0;i<100000;i++)
		{	
			b = a * i;
		}
		a++;
	}
	time (&end);
	dif_total = dif_total + difftime(end,start);

	cout << dif_total << endl;
	
	cout << ((double)clock() - startc)/CLOCKS_PER_SEC << endl;
}
