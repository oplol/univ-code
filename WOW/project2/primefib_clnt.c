/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include <memory.h> /* for memset */
#include "primefib.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

pf_result *
prime_1(int *argp, CLIENT *clnt)
{
	static pf_result clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, prime,
		(xdrproc_t) xdr_int, (caddr_t) argp,
		(xdrproc_t) xdr_pf_result, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

pf_result *
fib_1(int *argp, CLIENT *clnt)
{
	static pf_result clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, fib,
		(xdrproc_t) xdr_int, (caddr_t) argp,
		(xdrproc_t) xdr_pf_result, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}
