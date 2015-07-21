#include <stdio.h>
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
            
    for( i = 0; i < 16; i++ )
    {
       printf("%02x", md5sum[i]);
    }
    printf("\n");
    
    return 0;
}   
