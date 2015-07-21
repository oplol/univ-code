#include <stdio.h>
#include <math.h>
#include <stdbool.h>

//bool isPrime(int num); // Test whether the given integer is a prime or not
//int getPrime(int num); // Yields the x-th prime number

bool isPrime(int num) {
	int top = (int)sqrt((double)num);
	int i;
		for(i = 2; i <= top; ++i) {
			if(num % i == 0) return false;
		}
	
	return true;
}

int getPrime(int num) {
	int count = 0;
	int test = 2;
	
	while (count < num) {
		if (isPrime(test)) {
			++count;
		}
		++test;
	}
	
	return test - 1;
}

int main()
{
int i = 6;
printf("The %d-th prime number is %d. \n", i, getPrime(i));
return 0;
}


