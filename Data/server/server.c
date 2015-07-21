#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sendfile.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define MAXLINE 999999

const int Q_LEN = 5;  // number of waiting clients

/*************************************************************************************/
int server_socket(unsigned short port)
{
   struct sockaddr_in serv_sin;
   int sock_listen;

   // Setup address structure
   bzero((char *) &serv_sin, sizeof(serv_sin));
   serv_sin.sin_family = AF_INET;
   serv_sin.sin_addr.s_addr = INADDR_ANY;
   serv_sin.sin_port = htons(port);

   // Setup listening socket
   sock_listen = socket(PF_INET, SOCK_STREAM, 0);
   if (sock_listen < 0)
   {
      printf("Failed to create listening (server) socket\n");
      exit(1);
   }

  int opt = 1;
     setsockopt(sock_listen, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

   if (bind(sock_listen, (struct sockaddr *) &serv_sin,
                       sizeof(serv_sin)) < 0)
   {
      printf(" Failed to bind listening socket to address\n");
      exit(1);
   }

   if (listen(sock_listen, Q_LEN) < 0)
   {
      printf("Failed to listen\n");
      exit(1);
   }
   return sock_listen;
}


/***********************************************************************************/
int main(int argcount, char *argvector[])
{
   struct sockaddr_in cli_sin;
   unsigned int addrLen;
   unsigned short portno;
   int sock_listen;
   int sock;
   int rc,fd;
   char filename[100];   /* filename to send */

   FILE *tmpfile,*send_fp;
   char response[128];
   char buffer[8000]="",sendfile[MAXLINE]="";

   portno = atoi(argvector[1]);
   sock_listen = server_socket(portno);

while(1)
{
      sock = accept(sock_listen,(struct sockaddr *) &cli_sin,
                           &addrLen);

       tmpfile = popen("ls *.dat", "r");
       while (fgets(response, sizeof(response), tmpfile) != NULL)
       {

       strcat(buffer,response);
	   }
       
       write(sock,buffer,strlen(buffer)+1);


      bzero(response,128);
      bzero(buffer,sizeof(buffer));
	  
	rc = read(sock, filename, sizeof(filename));
    if (rc == -1) 
	 {
     printf("Failed to receive file");
     exit(1);
     }


  fd=open(filename,O_RDONLY);
  if(fd==-1){
    if(strcmp(filename,"")==0)
    printf("Client quit!\n");
    else
    printf("\"%s\": No such file exists!\n", filename);
    }
   else
   {
   printf("\"%s\" is ready to send to client!\n",filename);
   send_fp=fopen(filename,"r");
   while (fgets(response,sizeof(response),send_fp)!=NULL)
   {
   strcat(sendfile,response);
   }
   write(sock,sendfile,strlen(sendfile)+1);
   printf("\"%s\" has been sent to client!\n",filename);
   }

   bzero(sendfile,sizeof(sendfile));
   bzero(response,128);
   bzero(filename,sizeof(filename));
   close(sock);

}
   close (sock_listen);
   return 0;

}

