#include <stdio.h>
#include <string.h>
#include <string>
#include <list>
#include <stdlib.h>

#define LOGIT 0

#define DLOG(str) if (LOGIT) printf("%s: %s\n", __FUNCTION__, str);
#define DLOGF(fmt, ...) if (LOGIT) printf("%s: " fmt "\n", __FUNCTION__, __VA_ARGS__);

typedef std::string (*count_fn)(std::string,std::string);
std::list<std::string> print_intermid;

void split(char *str, std::string & a, std::string & b, char& op) {
    char* _op = index(str, '*');
    if (_op == 0) {
        _op = index(str,'+');
        if (_op == 0)
            _op = index(str, '-');
    }

    while (str != _op)
        a+=(char)(*str++);
    op = *str++;
    while (*str != 0)
        b+=*str++;

    DLOGF("a=%s b=%s op=%c\n",a.c_str(),b.c_str(),op);
}

void reverse(std::string&str) {
    str = std::string(str.rbegin(), str.rend());
}

void prepend_zeros(std::string&a,std::string&b)
{
    if (a.size()!=b.size()) {
        int diff = abs(a.size()-b.size());
        std::string * shorter;
        if (a.size()<b.size())
            shorter = &a;
        else
            shorter = &b;
        shorter->insert(0,std::string(diff,'0'));
    }
}

std::string add(std::string a,std::string b)
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

std::string sub(std::string a,std::string b)
{
    std::string res;// res.reserve(1024);
    prepend_zeros(a,b);
    DLOGF("ENTER: a=%s b=%s\n",a.c_str(),b.c_str());

    int borrowed=0;
    for (int i=a.size()-1;i>=0;--i) {
        int c=a[i]&0xf;
        int d=b[i]&0xf;
        int e=c-d-borrowed;
        if (e<0) {
            borrowed=1;
            e+=10;
        } else 
            borrowed=0;
        res+=e+0x30;
    }
    reverse(res);
    return res;
}

std::string mul(std::string a,std::string b)
{
    std::string res;// res.reserve(1024);
    DLOGF("ENTER: a=%s b=%s\n",a.c_str(),b.c_str());

    int zeros_to_append=0;
    print_intermid.clear();
    std::list<std::string> intermid;
    for (int j=b.size()-1;j>=0;--j) {
        int overload=0;
        for (int i=a.size()-1;i>=0;--i) {
            int c=a[i]&0xf;
            int d=b[j]&0xf;
            int e=c*d+overload;
            DLOGF("j=%d i=%d c=%d d=%d e=%d overload=%d res=%d",j,i,c,d,e,overload,(e%10));
            res+=(e%10)+0x30;
            overload=e/10;
        }
        if (overload) res+=overload+0x30;
        reverse(res);
        print_intermid.push_back(res);
        res+=std::string(zeros_to_append,'0');
        ++zeros_to_append;

        intermid.push_back(res);
        res.clear();
    }
    std::string sum=intermid.front();
    for (std::list<std::string>::iterator it=++intermid.begin();it!=intermid.end();++it) {
        sum = add(sum,*it);
    }
    return sum;
}

#define MAX_EXPR_LEN 2048

void remove_prep_zeros(std::string & str)
{
    if (!str.empty()){
        DLOGF("Found first not zero at %d",(int)str.find_first_not_of('0'));
        if (str.find_first_not_of('0')!=-1)
            str=str.substr(str.find_first_not_of('0'));
        else
            str="0";
    }
}

std::string count_it(std::string a, std::string b, count_fn f)
{
    std::string res;// res.reserve(1024);
    if (f!=mul)
        prepend_zeros(a,b);
    DLOGF("ENTER: a=%s b=%s\n",a.c_str(),b.c_str());

    res = f(a,b);

    remove_prep_zeros(res);

    return res;
}

void print_operands(std::string a, std::string b, char op, int offset=0)
{
    b=std::string(1,op)+b;
    std::string*shorter,*longer;
    if(a.size()<b.size()) {shorter=&a;longer=&b; }else {shorter=&b;longer=&a;}

    if (offset)
        offset=offset-longer->size();
    if (offset<0) offset=0;

    std::string spaces(offset,' ');

    int diff=abs(a.size()-b.size());
    std::string spaces_diff(offset+diff,' ');


    *longer=spaces+ *longer;
    *shorter=spaces_diff+ *shorter;
    printf("%s\n%s\n",a.c_str(),b.c_str());
}

int main()
{
    unsigned t=0;
    char expr[MAX_EXPR_LEN];

    scanf("%d",&t);
    for (int i=0;i<t;i++) {
        std::string a,b; a.reserve(1024); b.reserve(1024);
        char op;

        scanf("%s", expr);
        split(expr, a, b, op);

        switch (op) {
            case '+': {
                std::string res = count_it(a,b,add);
                print_result(a,b,'+',res.size());
                break;
                      }
            case '-': {
                std::string res = count_it(a,b,sub);
                print_operands(a,b,'-');
                print_dashes_res(b,res);
                break;
                      }
            case '*': {
                std::string res=count_it(a,b,mul);
                int longest;
                if (print_intermid.size()>1) {
                    longest=print_operands(a,b,'*',res.size());
                    int ident=longest;

                    for (std::list<std::string>::iterator it=print_intermid.begin();it!=print_intermid.end();++it) {
                        remove_prep_zeros(*it);
                        std::string spaces(ident-it->size(),' ');
                        printf("%s%s\n",spaces.c_str(),it->c_str());
                        ident--;
                    }
                    std::string dashes(longest,'-');
                    printf("%s\n",dashes.c_str());
                } else {
                    longest=print_operands(a,b,'*');
                }
                if (longest>res.size()) {
                    std::string spaces(longest-res.size(),' ');
                    res=spaces+res;
                }
                printf("%s\n",res.c_str());
                printf("\n");
                break;
                      }
            default:
                DLOGF("Unknown op = %c\n",op);
        }
    }
    
    return 0;
}
