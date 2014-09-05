#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <math.h>

#define MAX_EXPR_LEN 1000001

#define unlikely(x)     __builtin_expect((x),0)

void increment(std::string&str,int d)
{
    //printf("increment %s %d\n",str.c_str(),d);
    ++str[d];
    if (unlikely(str[d]==':')) {
     //   printf("Compilcated increment\n");
        str[d]='0';
        int rest=1;
        for (int j=d-1;j>=0;--j) {
      //      printf("Checking j=%d str[j]=%c\n",j,str[j]);
            if (str[j]=='9')
                str[j]='0';
            else {
                ++str[j]; rest=0;
                break;
            }
        }
        if (rest) str=std::string("1")+str;
    }
//    else
       // printf("Simple increment\n");
//	printf("Result: %s\n",str.c_str());
	return;
}

bool is_palin(std::string&s)
{
    int e=s.size()-1;
    for (int i=0;i<e/2+1;++i)
        if (s[i]!=s[e-i]) return false;
    return true;
}

int main()
{
    unsigned t=0;
    char expr[MAX_EXPR_LEN];

    scanf("%d",&t);
    for (int i=0;i<t;i++) {
        scanf("%s", expr);
	std::string str(expr);

	increment(str,str.size()-1);
	while (!is_palin(str)) {
	    int str_end=str.size()-1;
	    for (int i=str_end;i>str_end/2;--i) {
            if (str[i] != str[str_end-i]) {
                char old=str[i];
                str[i]=str[str_end-i];
                if (old>str[i])
                    increment(str,i-1);
            }
 //           printf("candidate= %s i=%d str[i]=%c str[other]=%c str_end=%d str_end/2=%d\n",str.c_str(),i,str[i],str[str_end-i],str_end,str_end/2);
        }
	}


	printf("%s\n",str.c_str());
    }

    return 0;
}
