struct Prime_Fibonacci {
	int a;
	int b;
};

program ADD_PROG {
	version ADD_VERS {
		int ADD(Prime_Fibonacci) = 1;
	} = 1 ;
} = 0x23456789;
