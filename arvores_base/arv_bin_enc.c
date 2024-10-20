#include <stdio.h>
#include <stdlib.h>


// ARVORE BINARIA DE BUSCA

typedef struct node {
    int info;
    struct node *left;
    struct node *right;
    struct node *father;
}node;

typedef node * arv;

void maketree(arv *, int);
void setleft(arv, int);
void setright(arv, int);
int info(arv);

arv left(arv);
arv right(arv);
arv father(arv);
arv brother(arv);

int isleft(arv);
int isright(arv);

void ins(arv *, int);
void percursoPreOrdem(arv);
void percursoInOrdem(arv);
void percursoPosOrdem(arv);
void percursoEmLargura(arv);

void remocaoPorFusao(arv *);
void remocaoPorCopia(arv *);


// ########################################################
// FILA PARA O PERCURSO EM LARGURA

typedef struct nodo {
    arv inf;
    struct nodo * next;
}nodo;

typedef struct {
    nodo *inicio;
    nodo *fim;
}descritor;

typedef descritor * fila;

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

void ins_fila(fila f, arv v){
    nodo *novo = (nodo *)malloc(sizeof(nodo));
    
    if(!novo){
        printf("memoria insuficiente\n"); //exit(1);
    }

    novo->inf = v;
    novo->next = NULL;
    
    if(eh_vazia_fila(f))
        f->inicio = novo;
    else
        f->fim->next = novo;
    f->fim = novo;
}

arv cons_fila(fila f){
    if(eh_vazia_fila(f)){
        printf("fila vazia\n"); //exit(2);
    }
    return f->inicio->inf;
}

void ret_fila(fila f){
    if(eh_vazia_fila(f)){
        printf("fila vazia\n"); //exit(2);
    }

    nodo *aux = f->inicio;
    f->inicio = f->inicio->next;
    if(!f->inicio)
        f->fim = NULL;
    free(aux);
}
//##########################################################
//##################FUNÇÕES ARVORE##########################
//##########################################################

void maketree(arv *t, int x){
    *t = (arv)malloc(sizeof(node));
    if(!(*t)){
        printf("memoria insuficiente");
        exit(1);
    }

    (*t)->info = x;
    (*t)->left = NULL;
    (*t)->right = NULL;
    (*t)->father = NULL;
}

void setleft(arv t, int x){
    t->left = (arv)malloc(sizeof(node));
    if(!(t->left)){
        printf("memoria insuficiente");
        exit(1);
    }
    t->left->info = x;
    t->left->left = NULL;
    t->left->right = NULL;
    t->left->father = t;
}

void setright(arv t, int x){

    t->right = (arv)malloc(sizeof(node));
    if(!(t->right)){
        printf("memoria insuficiente");
        exit(1);
    }
    t->right->info = x;
    t->right->left = NULL;
    t->right->right = NULL;
    t->right->father = t;
}

int info(arv t){
    return t->info;
}

arv left(arv t){
    return t->left;
}

arv right(arv t){
    return t->right;
}

arv father(arv t){
    return t->father;
}

arv brother(arv t){
    if(t->father)
        if(isleft(t))
            return t->father->right;
        else
            return t->father->left;
    return NULL;
}

int isleft(arv t){
    node *q = t->father;
    if(!q)
        return 0;
    if(q->left == t)
        return 1;
    return 0;
}

int isright(arv t){
    if(t->father)
        return(!isleft(t));
    return(0);
}

void ins(arv *t, int v){
    if(!(*t))
        maketree(t, v);
    else {
        arv father = *t;
        do {
            if(v < father->info){
                if(father->left)
                    father = father->left;
                else {
                    setleft(father, v);
                    break;
                }
            } else {
                if(father->right)
                    father = father->right;
                else {
                    setright(father, v);
                    break;
                }
            }
        }while(1);
    }
}

void percursoEmLargura(arv arvore){
    fila f;
    criar_fila(&f);

    if(arvore)
        ins_fila(f, arvore);
    while(!eh_vazia_fila(f)){
        printf("%3d", info(cons_fila(f)));

        if(left(cons_fila(f)))
            ins_fila(f, left(cons_fila(f)));
        if(right(cons_fila(f)))
            ins_fila(f, right(cons_fila(f)));
        ret_fila(f);
    }
}

void percursoPreOrdem(arv arvore){
    if(arvore){
        printf("%3d", info(arvore));
        percursoPreOrdem(left(arvore));
        percursoPreOrdem(right(arvore));
    }
}

void percursoInOrdem(arv arvore){
    if(arvore){
        percursoInOrdem(left(arvore));
        printf("%3d", info(arvore));
        percursoInOrdem(right(arvore));
    }
}

void percursoPosOrdem(arv arvore){
    if(arvore){
        percursoPosOrdem(left(arvore));
        percursoPosOrdem(right(arvore));
        printf("%3d", info(arvore));
    }
}

void remocaoPorFusao(arv *arvore) {
    // Verifica se a árvore (subárvore) não está vazia
    if (*arvore) {
        // Guarda o ponteiro para o nó que será removido
        arv tmp = *arvore;

        // Caso o nó não tenha filho à direita
        if (!((*arvore)->right)) {
            // Se existir um filho à esquerda, atualiza o ponteiro do pai
            if ((*arvore)->left)
                (*arvore)->left->father = (*arvore)->father;

            // O nó da árvore se torna o filho à esquerda (ou NULL se não houver)
            *arvore = (*arvore)->left;
        } else {
            // Caso o nó não tenha filho à esquerda
            if ((*arvore)->left == NULL) {
                // Atualiza o pai do filho à direita para o pai do nó que será removido
                (*arvore)->right->father = (*arvore)->father;

                // O nó da árvore se torna o filho à direita
                *arvore = (*arvore)->right;
            } else {
                // Caso o nó tenha tanto filho à esquerda quanto à direita
                // Percorre o maior valor da subárvore esquerda (extremo direito)
                tmp = (*arvore)->left;
                while (tmp->right)
                    tmp = tmp->right;

                // Faz o maior nó da subárvore esquerda apontar para o filho à direita do nó removido
                tmp->right = (*arvore)->right;

                // Atualiza o pai do filho à direita para o novo pai (nó encontrado)
                tmp->right->father = tmp;

                // Guarda o nó que será removido em 'tmp'
                tmp = *arvore;

                // O nó da árvore se torna o filho à esquerda
                *arvore = (*arvore)->left;
            }
        }
        // Libera a memória do nó removido
        free(tmp);
    }
}

void remocaoPorCopia(arv *arvore) {
    // Verifica se a árvore (subárvore) não está vazia
    if (*arvore) {
        // Guarda o ponteiro para o nó que será removido
        arv tmp = *arvore;

        // Caso o nó não tenha filho à direita
        if (!((*arvore)->right)) {
            // Se existir um filho à esquerda, atualiza o ponteiro do pai
            if ((*arvore)->left)
                (*arvore)->left->father = (*arvore)->father;

            // O nó da árvore se tcd orna o filho à esquerda (ou NULL se não houver)
            *arvore = (*arvore)->left;
        } else {
            // Caso o nó não tenha filho à esquerda
            if ((*arvore)->left == NULL) {
                // Atualiza o pai do filho à direita para o pai do nó que será removido
                (*arvore)->right->father = (*arvore)->father;

                // O nó da árvore se torna o filho à direita
                *arvore = (*arvore)->right;
            } else {
                // Caso o nó tenha ambos os filhos (à esquerda e à direita)
                // Buscamos o menor nó da subárvore à direita
                tmp = (*arvore)->right;

                // O menor valor da subárvore à direita será o nó mais à esquerda da mesma
                while(tmp->left)
                    tmp = tmp->left;

                // Copia o valor do nó encontrado (menor valor da subárvore à direita)
                // para o nó que será removido. Esta é a "remoção por cópia".
                (*arvore)->info = tmp->info;

                // Agora precisamos remover o nó que foi copiado, ou seja, 'tmp'.
                // Verifica se o nó copiado era o filho direto do nó a ser removido
                if (tmp->father == *arvore) {
                    // Atualiza o filho à direita do nó pai (nó original) para o filho à direita do nó removido
                    tmp->father->right = tmp->right;

                    // Se o nó removido tinha um filho à direita, atualiza o ponteiro 'father' do filho
                    if (tmp->father->right)
                        tmp->father->right->father = tmp->father;
                } else {
                    // Caso o nó copiado (tmp) não seja o filho direto, ele estava mais abaixo
                    // na subárvore à direita. Portanto, atualizamos o ponteiro do pai do nó removido
                    // para apontar para o filho à direita do nó removido (se existir).
                    tmp->father->left = tmp->right;

                    // Se o nó removido (copiado) tinha um filho à direita, atualizamos o ponteiro 'father'
                    if (tmp->father->left)
                        tmp->father->left->father = tmp->father;
                }
            }
        }
        // Libera a memória do nó removido
        free(tmp);
    }
}

int main() {
    arv arvore = NULL;

    // Inserir alguns valores na árvore binária de busca
    ins(&arvore, 50);
    ins(&arvore, 30);
    ins(&arvore, 70);
    ins(&arvore, 20);
    ins(&arvore, 40);
    ins(&arvore, 60);
    ins(&arvore, 80);

    // Mostrar a árvore antes da remoção
    printf("Árvore In-Ordem antes da remoção:\n");
    percursoEmLargura(arvore);
    printf("\n");

    // Remover o nó com valor 70 (que possui dois filhos)
    printf("Removendo o nó com valor 70 usando remoção por fusão...\n");
    remocaoPorCopia(&arvore->right);  // Remover o nó 70

    // Mostrar a árvore após a remoção
    printf("Árvore In-Ordem após a remoção:\n");
    percursoEmLargura(arvore);
    printf("\n");

    return 0;
}