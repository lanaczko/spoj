#include <stdio.h>
#include <string.h>
#include <string>

#define MAX_EXPR_LEN 1000001

void reverse(std::string &str) {
    str = std::string(str.rbegin(), str.rend());
}

std::string add_one(std::string&a)
{
	std::string res;
	int rest=0;
	int d=1;
	for (int i=a.size()-1;i>=0;--i) {
		int c=a[i]&0xf;
		res+=(((c+d+rest)%10) + 0x30);
		if (c+d+rest>9) rest=1;else rest=0;
		d=0;
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
	std::string str(expr);

	str=add_one(str);
	while (!is_palin(str)) {
		str=add_one(str);
		//printf("%s\n",str.c_str());
	}


	printf("%s\n",str.c_str());
    }

    return 0;
}
