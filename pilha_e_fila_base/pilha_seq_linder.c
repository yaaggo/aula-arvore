#include <stdio.h>
#include <stdlib.h>

#define MAX 10000

typedef struct {
    int topo;
    int val[MAX];
}pilha;

void criar_pilha(pilha *);
int eh_vazia(pilha *);
void push(pilha *, int);
int top(pilha *);
void pop(pilha *);
int top_pop(pilha *);

void criar_pilha(pilha *p){
    p->topo = -1;
}

int eh_vazia(pilha *p){
    return p->topo == -1;
}

void push(pilha *p, int v){
    if(p->topo == MAX - 1){
        printf("estouro de pilha\n");
        exit(1);
    }
    p->val[++(p->topo)] = v;
}

int top(pilha *p){
    if (eh_vazia(p)){
        printf("erro consulta em pilha vazia");
        exit(2);
    }

    return p->val[p->topo];
}

void pop(pilha *p){
    if (eh_vazia(p)){
        printf("pilha vazia\n");
        exit(3);
    }
    p->topo--;
}

int top_pop(pilha *p){
    if(eh_vazia(p)){
        printf("pilha vazia\n");
        exit(4);
    }
    return p->val[p->topo--];
}

// https://judge.beecrowd.com/pt/problems/view/1068

int main(){
    char s[1001];

    while(scanf(" %s", s) != EOF){
        pilha p;
        int i = -1;

        criar_pilha(&p);

        while(s[++i]){
            if(s[i] == '('){
                push(&p, (int)s[i]);
            } else if(s[i] == ')'){
                if(eh_vazia(&p)){
                    break;
                } else {
                    pop(&p);
                }
            }
        }
        if(!s[i] && eh_vazia(&p)){
            puts("correct");
        } else {
            puts("incorrect");
        }

    }
}