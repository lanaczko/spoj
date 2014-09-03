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

inline std::string add_one(std::string& a)
{
    std::string res;// res.reserve(1024);
    prepend_zeros(a,b);
    DLOGF("ENTER: a=%s b=%s\n",a.c_str(),b.c_str());

    int rest=0;
    int i=0;
    DLOG("Counting sum \n");
    for (i=a.size()-1;i>=0;--i) {
        int c=a[i]&0xf;
        int d=b[i]&0xf;
        res+=(((c+d+rest)%10) + 0x30);
        DLOGF("i=%d c=%d d=%d rest=%d sum=%d res=%s\n",i,c,d,rest,c+d+rest,res.c_str());
        if (c+d+rest>9) rest=1;else rest=0;
    }
    if (rest)
        res+='1';

    reverse(res);
    return res;
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
