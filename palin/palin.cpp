#include <stdio.h>
#include <string>
#include <stdlib.h>

#define MAX_EXPR_LEN 1000001

void reverse(std::string &str) {
    str = std::string(str.rbegin(), str.rend());
}

std::string add_one(std::string&a,int _d)
{
	std::string res;
	int rest=0;
	for (int i=a.size()-1;i>=0;--i) {
		int c=a[i]&0xf;
		res+=(((c+_d+rest)%10) + 0x30);
		if (c+_d+rest>9) rest=1;else rest=0;
		_d=0;
	}
	if (rest) res+='1';

	reverse(res);
	return res;
}

bool is_palin(std::string&s)
{
	std::string s2(s);
	reverse(s2);
	return (s==s2);
}

int main()
{
    unsigned t=0;
    char expr[MAX_EXPR_LEN];

    scanf("%d",&t);
    for (int i=0;i<t;i++) {
        scanf("%s", expr);
	std::string str(expr);

	str=add_one(str,'1');
	while (!is_palin(str)) {
	    int str_end=str.size()-1;
	    for (int i=str_end;i>=str_end/2;--i) {
            if (str[i] != str[str_end-i])
                str=add_one(str,abs(str[i]-str[str_end-i]));
        }
        //printf("candidate= %s\n",str.c_str());
	}


	printf("%s\n",str.c_str());
    }

    return 0;
}
