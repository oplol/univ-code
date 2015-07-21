#include <stdio.h>
#include <openssl/md5.h>

int main()   
{
    FILE *fp;
    int len, i;

    unsigned char buf[5000];
    unsigned char md5sum[16];
                
    if(!( fp = fopen("input.dat", "rb")))
    {
        printf("\nFailed to open file\n"); return (1);
    }
    
    len = fread(buf, 1, sizeof(buf), fp);

    MD5(buf, len, md5sum);
     
    for( i = 0; i < 16; i++ )
    {
       printf("%02x", md5sum[i]);
    }
    printf("\n");
    
    return 0;
}   
