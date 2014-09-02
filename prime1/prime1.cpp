#include <stdio.h>
#include <math.h>
#include <set>

#define MAX_TABLE 200000
int nums[MAX_TABLE];

void print_nums()
{
    for (int i=0;i<MAX_TABLE;i++) {
        if (nums[i]==-1) break;
        printf("%d ",nums[i]);
    }
    printf("\n");
}

int main()
{
    unsigned t=0, n1=0, n2=0;

    scanf("%d",&t);
    for (int i=0;i<t;i++) {
        scanf("%d %d",&n1, &n2);
        if (n1 == 1) ++n1;

        // prep up array with numbers
        int j;
        for (j=n1;j<=n2;j++)
            nums[j-n1]=j;
        nums[j-n1]=-1;

        //print_nums();

        for (j=2;j<=sqrt(n2);j++)
            for (int mnoznik=n1/j;mnoznik*j<=n2;mnoznik++) {
                if (mnoznik<2) mnoznik=2;
            //for (int mnoznik=2;mnoznik*j<=n2;mnoznik++) {
                //printf("Working on j=%d mnoznik=%d wynik=%d\n",j,mnoznik,j*mnoznik);
                if (mnoznik*j>=n1)// && nums[mnoznik*j-n1] != -1)

                    nums[mnoznik*j-n1]=0;
            }

        //print_nums();
        for (j=n1;j<=n2;j++)
            if (nums[j-n1]!=0)
                printf("%d\n",j);
        printf("\n");
    }
}

