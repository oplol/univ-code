#include <openssl/rsa.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
   
   unsigned char msg[128];
   unsigned char ciphertext[128];
   unsigned char plaintext[128];

   FILE  *fpk, *fp1, *fp2, *fp3;

   /*** File encryption/decryption testing  ***/
    fp1 = fopen("input.dat", "rb");
    if (fp1 == NULL)
    {
       printf("Failed to open input file\n");
       return 0;
    }

    fp2 = fopen("ciphertext.dat", "wb");
    if (fp2 == NULL)
    {
       printf("Failed to open output file: cryphertext.dat\n");
       return 0;
    }  
    
    fp3 = fopen("plaintext.dat", "wb");
    if (fp3 == NULL)
    {
       printf("Failed to open output file: plaintext.dat\n");
       return 0;
    }
   
   /*** RSA key ***/
   RSA *key;
   int size;
   
   key = RSA_generate_key(2048, 3,  NULL, NULL);
   if (key == NULL)
   {
      printf("\nFailed to generate key\n");
      exit(1);
   }
   RSA *key_copy;

   key_copy = RSA_generate_key(2048, 3,  NULL, NULL);
   if (key_copy == NULL)
   {
      printf("\nFailed to generate key\n");
      exit(1);
   } 

  /*key_copy = (RSA*) malloc(sizeof(RSA));
  key_copy -> e = BN_new();
  key_copy -> n = BN_new();
  key_copy -> d = BN_new();
  key_copy -> p = BN_new();
  key_copy -> q = BN_new();*/
  /*key_copy -> dmpl = BN_new();*/
  /*key_copy -> dmql = BN_new();*/
  /*key_copy -> iqmp = BN_new();*/

   BN_copy(key_copy -> n, key -> n);
   BN_copy(key_copy -> e, key -> e);
   key_copy -> p = NULL;
   key_copy -> q = NULL;
   key_copy -> d = NULL;
   
   fpk = fopen("public_key.dat", "w");
   
   RSA_print_fp(fpk, key, 0);
   
   fclose(fpk);   

   /*** Get the input file ***/
   int nbytes,  count = 0;
   while(!feof(fp1))
   { 
     nbytes = fread(msg, 1, 128, fp1);
     count++;
     /*** RSA encrypt and decrypt ***/
     size = RSA_public_encrypt(nbytes, msg, ciphertext, key_copy, RSA_PKCS1_PADDING);
        fwrite(ciphertext, 1, size, fp2);
    printf("\n%d\n",size);
     int size1;
     size1 = RSA_private_decrypt(size, ciphertext, plaintext, key, RSA_PKCS1_PADDING);
        fwrite(plaintext, 1, size1, fp3);
    printf("\n%d\n",size1);
    printf("\n----------------------------\n");
   }
  
   /* length of the file */
   /*struct stat file_status;
   if(stat("input.dat", &file_status) != 0)
   {
        perror("Rename the input file as input.dat!");
   }
   printf("%d\n", file_status.st_size);*/


   fclose(fp1);
   fclose(fp2);
   fclose(fp3);

   RSA_free(key);
   return 0;
}
