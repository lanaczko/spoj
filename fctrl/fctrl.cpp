#include <stdio.h>
#include <math.h>

int main()
{
    unsigned t=0;

    scanf("%d",&t);
    for (int i=0;i<t;i++) {
        long n, ret=0;
        scanf("%ld", &n);

        long k=1;
        while (powl(5,k)<=n) {
            ret+=floor((double)n/pow(5,k++));
        }
        printf("%ld\n",ret);
    }

    return 0;
}

