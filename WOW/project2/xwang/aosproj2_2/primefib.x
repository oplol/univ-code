struct pf_result{
	int num;
	int time;
	};

program primefib_PROG {
	version primefib_VERS {
		pf_result prime(int) = 1;
		pf_result fib(int) = 2;
	} = 1 ;
} = 0x23456789;
