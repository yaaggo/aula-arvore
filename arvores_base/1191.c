#include <stdio.h>
#include <string.h>

int x;
char pr[26], in[26];

void pos(int i, int f){
    if(i<=f){
        int t = i;
        char c = pr[x++];

        while(in[t] != c)t++;

        pos(i, t-1);
        pos(t+1, f);
        printf("%c", c);
    }
}

int main(){
    while(~scanf(" %s %s", pr, in)){
        x = 0;
        pos(0, strlen(in)-1);
        printf("\n");
    }
}