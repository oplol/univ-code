/* cli.cpp  -  Minimal ssleay client for Unix
   30.9.1996, Sampo Kellomaki <sampo@iki.fi> */

/* mangled to work with SSLeay-0.9.0b and OpenSSL 0.9.2b
   Simplified to be even more minimal
   12/98 - 4/99 Wade Scholine <wades@mail.cybg.com> */

/* modified by Ivo Jirasek Aug. 2001 */
#include <stdio.h>
#include <memory.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <strings.h>

#include <openssl/crypto.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/ssl.h> 
#include <openssl/err.h>
#include <openssl/rand.h>


#define CHK_NULL(x) if ((x)==NULL) exit (1)
#define CHK_ERR(err,s) if ((err)==-1) { perror(s); exit(1); }
#define CHK_SSL(err) if ((err)==-1) { ERR_print_errors_fp(stderr); exit(2); }

int main (int argc, char *argv[])
{
  int err;
  int sd;
  struct sockaddr_in sa;
  SSL_CTX* ctx;
  SSL*     ssl;
  X509*    server_cert;
  char*    str;
  char     buf [20000];
  SSL_METHOD *meth;

  FILE *recv_fp, *fp1;
  char filename[100] = "cli.dat";   /* filename to send */
  char filename1[100] = "serv_copy.dat";   /* filename to receive */

  char f_name_buf[80];    /* buffer for the name of the file of random numbers */
  const char  *p_to_buf;
  int  load_status;

  SSLeay_add_ssl_algorithms();
  meth = SSLv2_client_method();
  SSL_load_error_strings();
  ctx = SSL_CTX_new (meth);                        CHK_NULL(ctx);

  CHK_SSL(err);
  
  /* ----------------------------------------------- */
  /* Create a socket and connect to server using normal socket calls. */
  
  sd = socket (AF_INET, SOCK_STREAM, 0);       CHK_ERR(sd, "socket");
 
  memset (&sa, '\0', sizeof(sa));
  sa.sin_family      = AF_INET;
  sa.sin_addr.s_addr = inet_addr ("127.0.0.1");   /* Server IP */
  sa.sin_port        = htons     (7778);          /* Server Port number */
  
  err = connect(sd, (struct sockaddr*) &sa,
		sizeof(sa));                   
  CHK_ERR(err, "connect");

  /* ---------------------------------------------- */

  printf("In client. Now we have TCP conncetion. Start SSL negotiation\n");
  
  /* Specify where the file of random numbers is */

  p_to_buf = RAND_file_name(f_name_buf, 80);
  if(p_to_buf == NULL)
    printf("In client. Problem with the file name\n");

  load_status = RAND_load_file(p_to_buf, -1);
  if(load_status <=0)
    printf("In client. Problem with reading the file\n");


  ssl = SSL_new (ctx);                         CHK_NULL(ssl);    
  SSL_set_fd (ssl, sd);
  err = SSL_connect (ssl);

  printf("In client. Just after SSL_connect\n");
  CHK_SSL(err);
    
  /* Following two steps are optional and not required for
     data exchange to be successful. */
  
  /* Get the cipher - opt */

  printf ("In client. SSL connection using %s\n", SSL_get_cipher (ssl));
  
  /* Get server's certificate (note: beware of dynamic allocation) - opt */ 

  server_cert = SSL_get_peer_certificate (ssl);       CHK_NULL(server_cert);
  printf ("Server certificate:\n");
  
  str = X509_NAME_oneline (X509_get_subject_name (server_cert),0,0);
  CHK_NULL(str);
  printf ("\t subject: %s\n", str);
  /* Free (str); */

  str = X509_NAME_oneline (X509_get_issuer_name  (server_cert),0,0);
  CHK_NULL(str);
  printf ("\t issuer: %s\n", str);
  /* Free (str); */

  /* We could do all sorts of certificate verification stuff here before
     deallocating the certificate. */ 

  X509_free (server_cert); 
  
  /* --------------------------------------------------- */
  /* DATA EXCHANGE - Send a message and receive a reply. */
  int nbytes;
  recv_fp=fopen(filename,"rb");
  nbytes = fread(buf, 1, sizeof(buf), recv_fp);
  while (nbytes)
  {
  err= SSL_write(ssl, buf, nbytes);
  printf("\nSent %d bytes", err);
  CHK_SSL(err);
  nbytes = fread(buf, 1 ,sizeof(buf), recv_fp);
  }
  fclose(recv_fp);
  printf("\nIn client. Just after the first write\n"); /* */


  fp1=fopen(filename1,"wb");
  err = SSL_read (ssl, buf, sizeof(buf));
  CHK_SSL(err);

  while(err > 0)
  {
  //printf("\n %d", err);
  fwrite(buf,1,err,fp1);
  err = SSL_read (ssl, buf, sizeof(buf));
  CHK_SSL(err);
  }
  fclose(fp1);
  printf ("\nFile \"%s\" has been successfully copied from the server!\n", filename1);

  SSL_shutdown (ssl);  /* send SSL/TLS close_notify */

  /* Clean up. */

  close (sd);
  SSL_free (ssl);
  SSL_CTX_free (ctx);

  return 0;
}
/* EOF - cli.cpp */



