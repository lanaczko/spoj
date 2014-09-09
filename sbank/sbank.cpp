#include <stdio.h>
#include <stdlib.h>
#include <tr1/unordered_map>
#include <string>
#include <list>
#include <string.h>

typedef std::tr1::unordered_map<std::string, int> un_map;
std::list<std::string> l;
un_map m;

#define LOG 0

int main()
{
    unsigned t=0;

    scanf("%d",&t);
    for (int i=0;i<t;i++) {
        int n;
        scanf("%d", &n);
#if LOG
        printf("t=%d n=%d\n",t,n);
#endif
        for (int j=0;j<=n;++j) {
            char *acc=0; size_t s=0;
            getline(&acc,&s,stdin);
            if (strlen(acc)>1) {
                acc[strlen(acc)-1]=0;
#if LOG
                printf("Read=%s s=%d\n",acc,s);
#endif
                if ((++m[acc]) == 1)
                    l.push_back(std::string(acc));
            }
            free(acc);
        }
        for (std::list<std::string>::iterator it=l.begin();it!=l.end();++it) {
            printf("%s %d\n",it->c_str(), m[*it]);
        }
        printf("\n");
        m.clear(); l.clear();
    }

    return 0;
}

