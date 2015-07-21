#include <stdio.h>
#include <openssl/sha.h>

int main()   
{
    FILE *fp;
    int len, i;

    unsigned char buf[5000];
    unsigned char sha1sum[20];
                
    if(!( fp = fopen("input.dat", "rb")))
    {
        printf("\nFailed to open file\n");  return (1);
    }
    
    len = fread(buf, 1, sizeof(buf), fp);

    SHA1(buf, len, sha1sum);
     
    for( i = 0; i < 20; i++ )
    {
       printf("%02x", sha1sum[i]);
    }
    printf("\n");
    
    return 0;
}   
