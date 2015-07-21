//********************************************************************
//
// Xinyi Wang
// Advanced Operating Systems
// Programming Project #2: Programming using MPI and RPC
// Project 2_2: the client/server model
// Date Assigned: Thursday, March 7, 2013
// Due Date: Thursday, March 26, 2013 by 9:30 a.m. 
// Instructor: Dr. Ajay K. Katangur
//
//********************************************************************

/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "primefib.h"
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>



//********************************************************************
//
// is Prime function
//
// This function finds out whether the given number is prime or not.
//
//
// Return Value
// ------------
// bool              			True if the number is prime, otherwise False 
//
//
// Value Parameters
// ----------------
// num  			int				the num-th number
//            
//
// Reference Parameters
// -------------------- 
// None    
//
//
// Local Variables
// ---------------
// top      	int              		upper limit for loop
// i	     	int              		loop scan till the "top" value
//
//************************************************************************

bool isPrime(int num) {
	int top = (int)sqrt((double)num);
	int i;
		for(i = 2; i <= top; ++i) {
			if(num % i == 0) return false;
		}
	
	return true;
}



//********************************************************************
//
// Prime number function
//
// This function finds out the num-th prime number.
//
//
// Return Value
// ------------
// int              			the num-th prime number
//
//
// Value Parameters
// ----------------
// num  			int				the num-th number
//            
//
// Reference Parameters
// -------------------- 
// None    
//
//
// Local Variables
// ---------------
// count      	int              		loop count for all the previous num
// test     	int              		test scan all the numbers
//
//************************************************************************

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



//********************************************************************
//
// Fibonacci function
//
// This function finds out the num-th fibonacci number by using recursion.
//
//
// Return Value
// ------------
// int              			the num-th fibonacci number
//
//
// Value Parameters
// ----------------
// num  			int				the num-th number
//            
//
// Reference Parameters
// -------------------- 
// None    
//
//
// Local Variables
// ---------------
// first_fib      	int              		the first number in Fibonacci
// second_fib     	int              		the second number in Fibonacci
//
//************************************************************************

int getFib(int num) {
	int first_fib = 0;
	int second_fib = 1;
	
	if (num == 1)
		return first_fib;
		else if (num == 2)
			return second_fib;
			else
				return getFib(num - 1) + getFib(num - 2);
}



//********************************************************************
//
// Server prime number function
//
// This function is on the server side. It finds out the num-th prime number,
// and will return the result back to client.
//
//
// Return Value
// ------------
// pf_result              			the prime number as demanded
//
//
// Value Parameters
// ----------------
// argp  			int*				the num-th number that the client sent
// rqstp			struct svc_req*		structure containing context information
//            
//
// Reference Parameters
// -------------------- 
// None    
//
//
// Local Variables
// ---------------
// result      	static pf_result       	the result containing the prime number
//
//************************************************************************

pf_result *
prime_1_svc(int *argp, struct svc_req *rqstp)
{
	static pf_result  result;

	result.num = getPrime(*argp);
	result.time = 0;
	
	return &result;
}



//********************************************************************
//
// Server fibonacci number function
//
// This function is on the server side. It finds out the num-th fibonacci number,
// and will return the result back to client.
//
//
// Return Value
// ------------
// pf_result              			the fibonacci number as demanded
//
//
// Value Parameters
// ----------------
// argp  			int*				the num-th number that the client sent
// rqstp			struct svc_req*		structure containing context information
//            
//
// Reference Parameters
// -------------------- 
// None    
//
//
// Local Variables
// ---------------
// result      	static pf_result       	the result containing the fibonacci number
//
//************************************************************************

pf_result *
fib_1_svc(int *argp, struct svc_req *rqstp)
{
	static pf_result  result;

	result.num = getFib(*argp);
	result.time = 0;
	
	return &result;
}
