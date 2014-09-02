#include <stdio.h>

int main()
{
    int d=0;
    while (true) {
        scanf("%d", &d);
        if (d!=42)
            printf("%d\n",d);
        else
            return 0;
    }

    return 0;
}
