#include <stdio.h>

int main(int argc, char**argv)
{
    printf("1\n");
    for (int i=0;i<500;++i)
        printf("2");
    printf("%s",argv[0]);
    for (int i=0;i<500;++i)
        printf("1");
    printf("\n");

    return 0;
}

