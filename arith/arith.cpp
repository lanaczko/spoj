#define LOGIT 0

#include <stdio.h>
#include <string.h>
#include <string>
#include <list>
#include <stdlib.h>

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

void print_result(std::string a,std::string b, std::string res, std::list<std::string>& ii, char op)
{
    int max_length=0;
    if (!ii.empty()){
        max_length=ii.back().size()+ii.size()-1;
    }
    else
        max_length=0;

    b=std::string(1,op)+b;
    std::string*shorter,*longer;
    if(a.size()<b.size()) {shorter=&a;longer=&b; }else {shorter=&b;longer=&a;}
    if (max_length<longer->size())
        max_length=longer->size();
    if (max_length<res.size())
        max_length=res.size();



    printf("%s%s\n%s%s\n",std::string(max_length-a.size(),' ').c_str(),a.c_str(),std::string(max_length-b.size(),' ').c_str(),b.c_str());

    std::string * second;
    if (!ii.empty()) {
        remove_prep_zeros(ii.front());
        second=&ii.front();
    }
    else
        second=&res;

    std::string dashes;
    if (b.size()>second->size()) {
        dashes = std::string(b.size(),'-');
    }
    else {
        dashes = std::string(second->size(),'-');
    }
    dashes=std::string(max_length-dashes.size(),' ')+dashes;
    printf("%s\n",dashes.c_str());

    if (!ii.empty()) {
        int ident=max_length;
        for (std::list<std::string>::iterator it=ii.begin(); it!=ii.end();++it) {
            remove_prep_zeros(*it);
            printf("%s%s\n",std::string(ident-it->size(),' ').c_str(),it->c_str());
            ident--;
        }
        /* ----- */
#if 0
        if (res.size()>ii.back().size()) {
            dashes = std::string(res.size(),'-');
        }
        else {
            dashes = std::string(ii.back().size(),'-');
        }
#endif
        int dash_size = max_length-ii.back().size();
        if (res.size()==max_length)
            dash_size=max_length;

        DLOGF("max_length=%d dash_size=%d\n",max_length,dash_size);

        dashes=std::string(dash_size,'-');
        dashes=std::string(max_length-dashes.size(),' ')+dashes;
        printf("%s\n",dashes.c_str());
    }

    printf("%s%s\n", std::string(max_length-res.size(),' ').c_str(),res.c_str());
    printf("\n");
}

int main()
{
    unsigned t=0;
    char expr[MAX_EXPR_LEN];

    scanf("%d",&t);
    for (int i=0;i<t;i++) {
        print_intermid.clear();
        std::string a,b; a.reserve(1024); b.reserve(1024);
        char op;

        scanf("%s", expr);
        split(expr, a, b, op);

        switch (op) {
            case '+': {
                std::string res = count_it(a,b,add);
                print_result(a,b,res,print_intermid,'+');
                break;
                      }
            case '-': {
                std::string res = count_it(a,b,sub);
                print_result(a,b,res,print_intermid,'-');
                break;
                      }
            case '*': {
                std::string res=count_it(a,b,mul);
                if (print_intermid.size()<=1)
                    print_intermid.clear();
                print_result(a,b,res,print_intermid,'*');
                break;
                      }
            default:
                DLOGF("Unknown op = %c\n",op);
        }
    }
    
    return 0;
}
