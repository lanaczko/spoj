#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
using namespace std;
int bigger(int a,int b,int c)
{
    if(a>b)
    {
        if(c>a)
            return c;
        else
            return a;
    }
    else
    {
        int c1=0,c2=0,c0,b0;
        b0=b; 
        c0=c;
        while(c0!=0)
        {
            c0/=10; 
            c1++;
        }
        while(b0!=0)
        {
            b0/=10; 
            c2++;
        }
        if(c1>c2)
            return c;
        else    
            return b;
    }
}
int main()
{
    int i,n;
    cin>>n;
    for(i=0;i<n;i++)
    {
        int j,a,b,big,ans,dig,d,mult,dgit,m=0,ass;
        char ch;
        string res,str="";
        cin>>a>>ch>>b;
        if(ch=='+'||ch=='-')
        {
            if(ch=='+')
                ans=a+b;
            else if(ch=='-')
                ans=a-b;

            big=bigger(a,b,ans);
            d=big;
            dig=0;
            while(d!=0)
            {
                d/=10;
                dig++;
            }
            string abc="";
            if(ch=='+')
                abc.append("+");
            else
                abc.append("-");
            string qrt;
            ostringstream oss;
            oss<<b;
            qrt=oss.str();
            abc.append(qrt);
            cout<<setw(dig);
            cout<<a<<"\n";
            if(b==big)
                cout<<setw(dig+1);
            else
                cout<<setw(dig);
            cout<<abc;
            cout<<"\n";
            int k=0;
            if(b==big)
                k--;
            for(;k<dig;k++)
                cout<<'-';
            cout<<'\n';
            if(b==big)
                cout<<setw(dig+1);
            else
                cout<<setw(dig);
           cout<<ans;
        }

        else if(ch=='*')
        {
            ans=a*b;
            mult=b;
            big=bigger(a,b,ans);
            d=big;
            dig=0;
            while(d!=0)
            {
                d/=10;
                dig++;
            }
            if(b==big)dig++;
            cout<<setw(dig);
            cout<<a<<'\n';
            cout<<setw(0);
            string abc="";
            cout<<setw(dig);
            abc.append("*");
            string qrt;
            ostringstream oss;
            oss<<b;
            qrt=oss.str();
            abc.append(qrt);
            cout<<abc;
            cout<<'\n';
            d=bigger(a,b,a*(b%10));
            ass=0;
            while(d!=0)
            {
                d/=10;
                ass++;
            }
            if(a>b)
                for(int k=0;k<ass;k++)
                    str.append("-");
            else
                for(int k=0;k<=ass;k++)
                    str.append("-");
            cout<<setw(dig)<<str;
            cout<<'\n';
            while(mult!=0)
            {
                dgit=mult%10;
                mult/=10;
                ostringstream os;
                os<< dgit*a;
                res= os.str();
                for(int q=0;q<m;q++)
                {
                   res.append(" ");
                }
                cout<<setw(dig);
                cout<<res<<'\n';
                m++;
            }
            if(ans!=dgit*a)
            {
                for(int k=0;k<dig;k++)
                    cout<<'-';
                cout<<'\n'<<setw(dig)<<ans<<'\n';
            }

        }

    }
}
