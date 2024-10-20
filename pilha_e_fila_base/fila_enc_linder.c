#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    int inf;
    struct nodo * next;
}nodo;

typedef struct {
    // int ne;
    nodo *inicio;
    nodo *fim;
}descritor;

typedef descritor * fila;

void criar_fila(fila *);
int eh_vazia(fila);
int tam(fila);
void ins(fila, int);
int cons(fila);
void ret(fila);
int cons_ret(fila);
void destruir(fila);
//void gera_fila(fila, int , int);

void criar_fila(fila *pf){
    *pf = (descritor *)malloc(sizeof(descritor));
    if(!(*pf)) {
        printf("memoria insuficiente\n");
        //exit(1);
    }
    (*pf)->inicio = (*pf)->fim = NULL;
    // (*pf)->ne = 0;
}

int eh_vazia(fila f){
    return f->inicio == NULL;
}

void ins(fila f, int v){
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
    //f->ne++;
}

int cons(fila f){
    if(eh_vazia(f)){
        printf("fila vazia\n"); //exit(2);
    }
    return f->inicio->inf;
}

void ret(fila f){
    if(eh_vazia(f)){
        printf("fila vazia\n"); //exit(2);
    }

    nodo *aux = f->inicio;
    f->inicio = f->inicio->next;
    if(!f->inicio)
        f->fim = NULL;
    free(aux);
    // f->ne--;
}

int cons_ret(fila f){
    if(eh_vazia(f)){
        printf("fila vazia\n"); //exit(2);
    }

    int v = f->inicio->inf;

    nodo *aux = f->inicio;
    f->inicio = f->inicio->next;
    if(!f->inicio)
        f->fim = NULL;
    free(aux);
    // f->ne--;
    return v;
}

void destruir(fila f){
    nodo *aux;
    while(f->inicio){
        aux = f->inicio;
        f->inicio = f->inicio->next;
        free(aux);
    }
    free(f);
}

// https://judge.beecrowd.com/pt/problems/view/1897

#define offset 100000
#define max offset * 2 + 1

int main(){
    fila f;
    int n, m;
    int distancias[max], visitados[max] = {};

    scanf("%d %d", &n, &m);

    criar_fila(&f);
    ins(f, n);
    visitados[n + offset] = 1;
    distancias[n + offset] = 0;

    while(!visitados[m + offset]){
        int v = cons_ret(f);
        int operacoes[] = {v * 2, v * 3, v/2, v/3, v+7, v-7};

        for(int i = 0; i<6; i++){
            int k = operacoes[i];

            if(k >= -offset && k <= offset){
                int resultado = k + offset;

                if(!visitados[resultado]){
                    ins(f, k);
                    visitados[resultado] = 1;
                    distancias[resultado] = distancias[v + offset] + 1;
                }
            }
        }
    }
    printf("%d\n", distancias[m + offset]);
}