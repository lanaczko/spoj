#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>


#include <strings.h>

/*
 * Complete the function below.
 *
 * Assumptions: 
 *      () single letter friends naming
 *      () Caller frees return value!
 *      () We can handle as much as 255 friends (non-printable chars included ;) )
 */
char** graph(int input_size, char** input, int* result_size) {
    static const int max_friends = 255; // how much can we handle?
    
    char **res;
    int res_size = 0; // How much do we return?
    int lvl_no=1;
    char friends[max_friends][max_friends];
    char seen[max_friends]; // Friends we've already processed
    int fr_no=0;
    char q[max_friends];
    int q_c=0;
    
    if (!input_size)
        goto output; // I work in kernel :)
    
    bzero(seen, max_friends);
    bzero(q, max_friends);

    seen[input[0][0]]=1;
    q[q_c++]=input[0][0];
    // Build the graph
    for (int i=0; i<input_size; ++i) {
        printf("in%d=%s\n", i, input[i]);

        char root=input[i][0];
        fr_no++;
        int fr_c=0; // friend counter
        for (int ii=1;ii<strlen(input[i]); ++ii){
            char c = input[i][ii];
            printf("ch %c\n",c);
            if (c==':' || c==',' || c==0) continue;
            friends[root][fr_c++]=c;
        }
        friends[root][fr_c]=0;
        printf("my %c=%s\n",root,friends[root]);
    }
    res=malloc(max_friends*sizeof(char*)); 
    
    while (q_c) {
        char *lvl=malloc(max_friends*sizeof(char));
        char s=q[q_c-1]; // get the last one
        
    }
    
 output:
    *result_size = res_size;
    return res; // can please somebody free this?
}








int main() {
    //FILE *f = fopen(getenv("OUTPUT_PATH"), "w");
    FILE *f = fopen("output.txt", "w");
    int res_size;
    char** res;
    
    int _input_size, _input_i;
    scanf("%d\n", &_input_size);
    char* _input[_input_size];
    for(_input_i = 0; _input_i < _input_size; _input_i++) {
        char* _input_item;
        _input_item = (char *)malloc(10240 * sizeof(char));
        scanf("\n%[^\n]",_input_item);


        _input[_input_i] = _input_item;
    }
    
    res = graph(_input_size, _input, &res_size);
    int res_i;
    for(res_i=0; res_i < res_size; res_i++) {
    
        fprintf(f, "%s\n", res[res_i]);
        
    }
    
    
    fclose(f);
    return 0;
}

