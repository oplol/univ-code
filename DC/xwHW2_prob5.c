#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>

// Function retuns DNS name given ip address in dotted decimal
// It returns null string if it fails
char *getDNSName(char *ipAddrDotted)
{
   struct hostent *hostPtr;
   u_long ip_addr_long;
   char* addr_ptr;
   ip_addr_long = inet_addr(ipAddrDotted);
   hostPtr = gethostbyaddr((char *) &ip_addr_long, 4, AF_INET);
   if (hostPtr == NULL)
       return "";
   else 
       return  hostPtr->h_name;
}
// Test run
int main()
{
   char dnsName[50];
   char ipDotted[12];
   int i;
   u_long ipAddr;
   int numberOfIpAddrs;


   FILE *fp3, *fp4;
   fp3 = fopen("inputIP.dat", "r");
   fp4 = fopen("outputDNS.out", "w");
   char IPname[999];
   while (fscanf(fp3, "%s", IPname) != EOF)
   {
	   if (getDNSName(IPname) == "")
	   {fprintf(fp4, "Not Found\n");}
	   else
	   {fprintf(fp4, "%s\n", getDNSName(IPname));}
   }
   return 0;
}
