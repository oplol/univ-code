#include <openssl/rsa.h>
#include <stdlib.h>
int main()
{
   FILE *fp;
   
   RSA *key;
   
   key = RSA_generate_key(2048, 3,  NULL, NULL);
   if (key == NULL)
   {
      printf("\nFailed to generate key\n");
      exit(1);
   }
   
   fp = fopen("key.dat", "w");
   
   RSA_print_fp(fp, key, 0);
   
   fclose(fp);   
   RSA_free(key);
   return 0;
}
