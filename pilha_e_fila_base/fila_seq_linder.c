#include <stdio.h>
#include <stdlib.h>

#define MAX 50

typedef struct {
    int n;
    int inicio;
    int fim;
    int val[MAX];
} fila;

void criar_fila(fila *);
int eh_vazia(fila *);
int tam(fila *);
void ins(fila *, int);
int cons(fila *);
void ret(fila *);
int cons_ret(fila *);
void gera_fila(fila *, int , int);

void criar_fila(fila *f){
    f->n = f->inicio = 0;
    f->fim = -1;
}

int eh_vazia(fila *f){
    return (!f->n);
}

int tam(fila *f){
    return (!f->n);
}

void ins(fila *f, int v){
    if(f->n == MAX){
        printf("ja ta cheio\n");
        exit(1);
    }

    f->fim = ((f->fim) + 1) % MAX;
    f->val[f->fim] = v;
    f->n++;
}

int cons(fila *f){
    if(eh_vazia(f)){
        printf("fila vazia\n");
        exit(2);
    }

    return f->val[f->inicio];
}

void ret(fila *f){
    if(eh_vazia(f)){
        printf("fila vazia\n");
        exit(3);
    }

    f->inicio = (f->inicio+1) % MAX;
    f->n--;
}

int cons_ret(fila *f){
    if(eh_vazia(f)){
        printf("fila vazia\n");
        exit(4);
    }

    int v = f->val[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->n--;
    
    return v;
}

void gera_fila(fila *f, int m, int n){
    if(m > n){
        printf("intervalo invalido\n");
        exit(5);
    }

    if(m == n){
        criar_fila(f);
        ins(f, m);
    } else {
        gera_fila(f, m, n - 1);
        ins(f, n);
    }
}


// https://judge.beecrowd.com/pt/problems/view/1110 
int main(){
    int n;
    while(scanf("%d", &n), n){
        fila f;
        gera_fila(&f, 1, n);

        printf("Discarded cards:");

        while(f.n > 2){
            int a = cons_ret(&f), b = cons_ret(&f);
            printf(" %d,", a);
            ins(&f, b);
        }

        printf(" %d\n", cons_ret(&f));
        printf("Remaining card: %d\n", cons_ret(&f));
    }
}