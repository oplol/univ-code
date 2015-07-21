#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>
// Function returns ip address as unsigned long integer
// given DNS name as a character string. it reutns 0 if it fails.
u_long  getIpAddr(char *hostName)
{
   struct hostent *hostPtr;
   u_long *ipAddr;
   hostPtr = gethostbyname(hostName);
   if (hostPtr == NULL)
      return 0;
   else
   {
      ipAddr = (u_long *)*hostPtr->h_addr_list;
      return *ipAddr;
   }
}	
// Function returns ip address in dotted decimal notation
// given ip address as unsigned long integer
char *convertIpToDotted (u_long  ipAddr)
{ 
   struct in_addr y;
   y.s_addr = ipAddr;
   return inet_ntoa (y);
}

// Test run
      
int main()
{
   char dnsName[50];
   char ipDotted[12];
   int i;
   u_long ipAddr;
   int numberOfIpAddrs;
   FILE *fp1, *fp2;
   fp1 = fopen("inputDNS.dat", "r");
   fp2 = fopen("outputIP.out", "w");
   char DNSname[999];
   while (fscanf(fp1, "%s", DNSname) != EOF)
   {
	   ipAddr = getIpAddr(DNSname);
	   if (ipAddr == 0)
	   {fprintf(fp2, "Not Found\n");}
	   else
	   {fprintf(fp2, "%s\n", convertIpToDotted(ipAddr));}
   }

   return 0;
}

