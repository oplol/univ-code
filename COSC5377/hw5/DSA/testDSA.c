#include <stdlib.h>
#include <openssl/dsa.h>
#include <openssl/md5.h>

int main()
{
	FILE *fp;
    int len, i;

    MD5_CTX ctx;
    unsigned char buf[1000];
    unsigned char md5sum[16];
                
    
    MD5_Init(&ctx);
    if(!( fp = fopen("input.dat", "rb")))
    {
        printf("\nFailed to open file\n"); return (1);
    }
    
    while((len = fread( buf, 1, sizeof(buf), fp ) ) > 0 )
    {
        MD5_Update(&ctx, buf, len);
    }
         
    MD5_Final(md5sum, &ctx);
    
	printf("MD5(input.dat) = ");
    for( i = 0; i < 16; i++ )
    {
       printf("%02x", md5sum[i]);
    }
    printf("\n");


   DSA *key;
   FILE *fp1, *fp2;
   /*unsigned char digest[8] = "1234567";*/
   int siglen;
   unsigned char signature[1000];
   int retcode;

   key = DSA_generate_parameters(1024, NULL, 0, NULL, NULL, NULL, NULL);

   if (key == NULL)
   {
      printf("\nFailed to generate parameters\n");
      exit(1);
   }
   fp1 = fopen("params.dat", "w");
   DSAparams_print_fp(fp1, key);
   fclose(fp1);

   DSA_generate_key(key);
   if (key == NULL)
   {
      printf("\nFailed to generate key\n");
      exit(1);
   }

   fp2 = fopen("key.dat", "w");

   DSA_print_fp(fp2, key, 0);
   fclose(fp2);

   retcode = DSA_sign(0, md5sum, 8, signature, &siglen, key);
   if (retcode == 0)
   {
      printf("\n *** Error in signing ***\n\n");
      exit(1);
   }

   FILE *fp3;
   fp3 = fopen("signature.dat", "w");
   fputs(signature, fp3);
   fclose(fp3);

   printf("\nSignature of the hash = ");
   printf("%s\n",signature);

   retcode = DSA_verify(0, md5sum, 8, signature, siglen, key);
   if (retcode == 1)
      printf("\n *** Valid signature ***\n\n");
   if (retcode == 0)
      printf("\n *** Incorrect signature ***\n\n");
   if (retcode == -1)
      printf("\n *** Error in verifying ***\n\n");

   DSA_free(key);
   return 0;
}

