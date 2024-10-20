#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    int inf;
    struct nodo * next;
}nodo;

typedef struct {
    nodo *inicio;
    nodo *fim;
}descritor;

typedef descritor * fila;

void criar_fila(fila *);
int eh_vazia_fila(fila);
void ins_fila(fila, int);
int cons(fila);
void ret_fila(fila);

void criar_fila(fila *pf){
    *pf = (descritor *)malloc(sizeof(descritor));
    if(!(*pf)) {
        printf("memoria insuficiente\n");
        exit(1);
    }
    (*pf)->inicio = (*pf)->fim = NULL;
}

int eh_vazia_fila(fila f){
    return f->inicio == NULL;
}

void ins_fila(fila f, int v){
    nodo *novo = (nodo *)malloc(sizeof(nodo));
    
    if(!novo){
        printf("memoria insuficiente\n"); //exit(1);
    }

    novo->inf = v;
    novo->next = NULL;
    
    if(eh_vazia(f))
        f->inicio = novo;
    else
        f->fim->next = novo;
    f->fim = novo;
}

int cons_fila(fila f){
    if(eh_vazia(f)){
        printf("fila vazia\n"); //exit(2);
    }
    return f->inicio->inf;
}

void ret_fila(fila f){
    if(eh_vazia(f)){
        printf("fila vazia\n"); //exit(2);
    }

    nodo *aux = f->inicio;
    f->inicio = f->inicio->next;
    if(!f->inicio)
        f->fim = NULL;
    free(aux);
}