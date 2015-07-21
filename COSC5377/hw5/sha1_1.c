#include <stdio.h>
#include <openssl/sha.h>

int main()   
{
    FILE *fp;
    int len, i;

    SHA_CTX ctx;
    unsigned char buf[1000];
    unsigned char sha1sum[20];
                
    
    SHA1_Init(&ctx);
    if(!( fp = fopen("input.dat", "rb")))
    {
        printf("\nFailed to open file\n"); return (1);
    }
    
    while((len = fread( buf, 1, sizeof(buf), fp ) ) > 0 )
    {
        SHA1_Update(&ctx, buf, len);
    }
         
    SHA1_Final(sha1sum, &ctx);
            
    for( i = 0; i < 20; i++ )
    {
       printf("%02x", sha1sum[i]);
    }
    printf("\n");
    
    return 0;
}   
