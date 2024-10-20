#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int inf;
    struct node * next;
}node;

typedef node * pilha;

void create(pilha *);
int is_empty(pilha);
void push(pilha *, int);
int top(pilha);
void pop(pilha *);
int top_pop(pilha *);
void destroy(pilha);

void create(pilha *pp){
    *pp = NULL;
}

int is_empty(pilha p){
    return !p;
}

void push(pilha *pp, int v){
    node *new = (node *)malloc(sizeof(node));
    if(!new){
        printf("memoria insuficiente");
        exit(1);
    }
    new->inf = v;
    new->next = *pp;
    *pp = new;
}

int top(pilha p){
    if (!p){
        printf("pilha vazia");
        exit(2);
    }

    return p->inf;
}

void pop(pilha *pp){
    if(!(*pp)){
        printf("pilha vazia");
        exit(3);
    } else {
        node *aux = *pp;
        *pp = (*pp)->next;
        free(aux);
    }
}

int top_pop(pilha *pp){
    if(!(*pp)){
        printf("pilha vazia");
        exit(4);
    } else {
        int v = (*pp)->inf;
        node *aux = *pp;
        *pp = (*pp)->next;
        free(aux);
        return v;
    }
}

void destroy(pilha l){
    pilha aux;
    while(l){
        aux = l;
        l = l->next;
        free(aux); 
    }
}

#define BS 'B' + 'S'
#define CF 'C' + 'F'

int main(){
    char s[1001];

    while(~scanf(" %s", s)){
        int i = 0, ans = 0;
        pilha p;
        
        create(&p);
        push(&p, s[i]);

        while(s[++i]){
            if(!is_empty(p) && (top(p) + s[i] == BS || top(p) + s[i] == CF)){
                ans++;
                pop(&p);
            } else {
                push(&p, s[i]);
            }
        }

        printf("%d\n", ans);
    }
}