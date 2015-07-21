#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/sendfile.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/uio.h>
       
int client_socket(char * serv_name, unsigned short portno)
{
 // create socket
   int sock;
   struct sockaddr_in sin;
   struct hostent * hostPtr;

   sock = socket(PF_INET, SOCK_STREAM, 0);
   if(sock < 0)
   {
      printf("Failed to create a socket\n");
      exit(1);
   }
   // bind socket with remote host address
    
   bzero((char *) &sin, sizeof(sin));
   sin.sin_port = htons(portno);   // set to port number
 
   // Get IP address
   hostPtr = gethostbyname(serv_name);
   if (hostPtr == NULL)
   {
      printf("Failed to resolve host name\n");
      exit(2);
   }
   bcopy(hostPtr->h_addr, (char *) &sin.sin_addr, hostPtr->h_length);
   sin.sin_family = hostPtr->h_addrtype;   // usually AF_INET
   int retcode;
   retcode = connect(sock, (struct sockaddr *) &sin, sizeof(sin));
   if(retcode < 0)
   {
      printf("Failed to connect with the host\n");
      exit(2);
   }
   else
      return sock;
}

/***********************************************************************************/
int main(int argcount, char *argvector[])
{ 
   int sock,n;
   unsigned short portno;  
   char dnsname[81];
   char buffer[8000];
   char filename[256]="start";
   FILE *recv_fp;
   char recvfile[999999]="";
   
   strcpy(dnsname, argvector[1]);
   portno = atoi(argvector[2]);

  
   
   while(1)
   {
   sock=client_socket(dnsname,portno);
   printf("\nFile list as shown below:\n");
   printf("-----------------------------------------------------------------------\n");
   read(sock, buffer, sizeof(buffer));
   printf("%s", buffer);
   printf("-----------------------------------------------------------------------\n");
   printf("Type the filename that you want to download or just type Q to exit: ");
   scanf("%s",filename);
   
    if(strcmp(filename,"Q") ==0)
     break;
   
    n = write(sock,filename,strlen(filename)+1);
    if (n < 0) 
         printf("WARNING: can not write into socket");

   
  
   if( read(sock, recvfile, sizeof(recvfile))>0) 
  {
     recv_fp=fopen(filename,"w+"); 
     fprintf(recv_fp,"%s",recvfile);
	 bzero(recvfile,sizeof(recvfile));
     fclose(recv_fp);
     printf("\nFile \"%s\" has been successfully downloaded!\n", filename);
  }
  else
  {
  printf("\nThere is no file named as \"%s\" above!\n",filename);
  }

  
  bzero(buffer,sizeof(buffer));
  bzero(filename,sizeof(filename)); 
  }
   return 0;

}

