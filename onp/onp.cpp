#include <stdio.h>
#include <string.h>
#include <stack>
#include <string>

#define MAX_EXPR_LEN 401

int prio[128];

int onp(char* expr, std::string & output)
{
    std::stack<char> s;

    for (int i=0; i<strlen(expr); ++i) {
        char token = expr[i];

        if (token >= 'a' && token <='z') {
            output += token;
        }
        if (token == '+' || token == '-' || token == '*' || token == '/' || token == '^') {
            while (prio[s.top()] > prio[token]) {
                output += s.top();
                s.pop();
            }
            s.push(token);
        }
        if (token == '(')
            s.push(token);
        if (token == ')') {
            while (s.top() != '(') {
                output += s.top();
                s.pop();
            }
            s.pop(); //remove (
        }
        //printf("output = %s token=%c\n", output.c_str(),token);
    }
    if (!s.empty()) {
        output += s.top();
        s.pop();
    }

    return 0;
}

int main()
{
    prio['+'] = 0;
    prio['-'] = 1;
    prio['*'] = 2;
    prio['-'] = 3;
    prio['^'] = 4;

    unsigned t=0;
    char expr[MAX_EXPR_LEN];
    std::string output;

    scanf("%d",&t);
    for (int i=0;i<t;i++) {
        scanf("%s", expr);

        onp(expr, output);
        printf("%s\n", output.c_str());
        output = "";
    }

    return 0;
}
