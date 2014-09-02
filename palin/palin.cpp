#include <stdio.h>
#include <string.h>

#define MAX_EXPR_LEN 1000001

void reverse(char *str) {
    for (int i=0;i<strlen(str);++i) {
        char t=str[i];
        str[i]= str[strlen(str)-1];
        str[strlen(str)-1] = t;
    }
}

int main()
{
    unsigned t=0;
    char expr[MAX_EXPR_LEN];

    scanf("%d",&t);
    for (int i=0;i<t;i++) {
        scanf("%s", expr);

        int e_len = strlen(expr)-1;

        reverse(expr);
        printf("%s\n", expr);

        for (int j=0;j<e_len/2+1;j++) {
            printf("%s j=%d e_len=%d e_len-j=%d\n", expr,j,e_len,e_len-j);
            while (expr[j] != expr[e_len-j]) {
                printf("%c == %c\n",expr[j] , expr[e_len-j]);
                // increase expr[j] until it matches expr[e_len-j]
                if (expr[e_len-j] != '9') {
                    expr[e_len-j]++;
                } else {
                    //while (expr[e_len
                    expr[e_len-j-1]++;
                    expr[e_len-j] = '0';
                }
            }
        }

        printf("%s\n", expr);
    }

    return 0;
}
