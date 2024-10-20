#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int num, altd, alte;
    struct node *esq, *dir;
} node;

typedef node * AVL;

// Função que retorna a altura do nó passado como parâmetro
// A altura é definida como o maior valor entre alte (altura da subárvore à esquerda) e altd (altura da subárvore à direita)
// Soma-se 1 ao valor da altura do maior filho, para incluir o próprio nó
int altura(AVL arvore) {
    if (arvore == NULL) return 0; // Se o nó for NULL, a altura é zero
    return (arvore->alte > arvore->altd) ? arvore->alte + 1 : arvore->altd + 1; // Retorna a altura do maior subfilho
}

// Função para atualizar as alturas de alte e altd de um nó
// Esta função deve ser chamada sempre que a estrutura da árvore é modificada, como após inserções ou rotações
void atualizar_altura(AVL arvore) {
    arvore->alte = (arvore->esq == NULL) ? 0 : altura(arvore->esq); // Atualiza a altura da subárvore à esquerda
    arvore->altd = (arvore->dir == NULL) ? 0 : altura(arvore->dir); // Atualiza a altura da subárvore à direita
}

// Função que realiza uma rotação à direita para balancear a árvore AVL
// Usada quando a subárvore esquerda está desbalanceada (mais alta que a direita)
// A rotação à direita move o nó da esquerda para o topo e o nó desbalanceado desce para a direita
void rotacao_direita(AVL *arvore) {
    AVL aux1, aux2;
    aux1 = (*arvore)->esq;  // 'aux1' é o nó que ficará no topo após a rotação
    aux2 = aux1->dir;       // 'aux2' é a subárvore direita de 'aux1', que se tornará a subárvore esquerda do nó original
    (*arvore)->esq = aux2;  // O nó original passa a apontar para 'aux2' como sua subárvore esquerda
    aux1->dir = (*arvore);  // O nó 'aux1' agora tem o nó original como sua subárvore direita
    atualizar_altura(*arvore);  // Atualiza as alturas do nó que desceu
    atualizar_altura(aux1);     // Atualiza as alturas do novo nó superior
    *arvore = aux1;  // A raiz da árvore atual passa a ser 'aux1'
}

// Função que realiza uma rotação à esquerda para balancear a árvore AVL
// Usada quando a subárvore direita está desbalanceada (mais alta que a esquerda)
// A rotação à esquerda move o nó da direita para o topo e o nó desbalanceado desce para a esquerda
void rotacao_esquerda(AVL *arvore) {
    AVL aux1, aux2;
    aux1 = (*arvore)->dir;  // 'aux1' é o nó que ficará no topo após a rotação
    aux2 = aux1->esq;       // 'aux2' é a subárvore esquerda de 'aux1', que se tornará a subárvore direita do nó original
    (*arvore)->dir = aux2;  // O nó original passa a apontar para 'aux2' como sua subárvore direita
    aux1->esq = (*arvore);  // O nó 'aux1' agora tem o nó original como sua subárvore esquerda
    atualizar_altura(*arvore);  // Atualiza as alturas do nó que desceu
    atualizar_altura(aux1);     // Atualiza as alturas do novo nó superior
    *arvore = aux1;  // A raiz da árvore atual passa a ser 'aux1'
}

// Função que realiza o balanceamento da árvore AVL
// Verifica o Fator de Balanceamento (FB) do nó atual
// Se o FB for 2 ou -2, realiza uma rotação para balancear a árvore
void balanceamento(AVL *arvore) {
    int FBpai, FBfilho;
    FBpai = (*arvore)->altd - (*arvore)->alte;  // Fator de Balanceamento do nó atual (FB = altura direita - altura esquerda)
    
    // Caso 1: A subárvore direita está desbalanceada (FB = 2)
    if (FBpai == 2) {
        FBfilho = (*arvore)->dir->altd - (*arvore)->dir->alte;  // Fator de balanceamento do filho direito
        if (FBfilho >= 0) {
            rotacao_esquerda(arvore);  // Rotação simples à esquerda se o filho direito também estiver desbalanceado para a direita
        } else {
            rotacao_direita(&((*arvore)->dir));  // Rotação dupla: primeiro à direita no filho direito
            rotacao_esquerda(arvore);  // Depois à esquerda no nó atual
        }
    // Caso 2: A subárvore esquerda está desbalanceada (FB = -2)
    } else if (FBpai == -2) {
        FBfilho = (*arvore)->esq->altd - (*arvore)->esq->alte;  // Fator de balanceamento do filho esquerdo
        if (FBfilho <= 0) {
            rotacao_direita(arvore);  // Rotação simples à direita se o filho esquerdo também estiver desbalanceado para a esquerda
        } else {
            rotacao_esquerda(&((*arvore)->esq));  // Rotação dupla: primeiro à esquerda no filho esquerdo
            rotacao_direita(arvore);  // Depois à direita no nó atual
        }
    }
}

// Função que insere um valor na árvore AVL
// Após inserir, atualiza a altura e realiza o balanceamento da árvore
void inserir(AVL *arvore, int valor) {
    // Caso base: se a árvore (subárvore) for NULL, cria um novo nó com o valor fornecido
    if (*arvore == NULL) {
        *arvore = (node*)malloc(sizeof(node));  // Aloca memória para um novo nó
        (*arvore)->num = valor;  // Atribui o valor ao nó
        (*arvore)->esq = (*arvore)->dir = NULL;  // O novo nó não tem filhos (subárvores)
        (*arvore)->altd = (*arvore)->alte = 0;  // Inicializa as alturas dos filhos como 0
    } else {
        // Caso recursivo: insere o valor na subárvore esquerda se o valor for menor que o nó atual
        if (valor < (*arvore)->num) {
            inserir(&((*arvore)->esq), valor);  // Insere à esquerda
        // Caso recursivo: insere o valor na subárvore direita se o valor for maior que o nó atual
        } else if (valor > (*arvore)->num) {
            inserir(&((*arvore)->dir), valor);  // Insere à direita
        } else {
            return;  // Se o valor já existir, não faz nada
        }

        // Após a inserção, atualiza as alturas do nó
        atualizar_altura(*arvore);

        // Realiza o balanceamento da árvore
        balanceamento(arvore);
    }
}

void remover(AVL* arvore, int valor) {
    // Caso base: Se a árvore estiver vazia, apenas retorna
    if (*arvore == NULL) {
        return; // Valor não encontrado, nada a fazer
    }

    // Passo 1: Encontrar o nó a ser removido
    if (valor < (*arvore)->num) {
        // Se o valor a ser removido for menor que o valor do nó atual,
        // busca recursivamente na subárvore esquerda
        remover(&((*arvore)->esq), valor); // Buscar à esquerda
    } else if (valor > (*arvore)->num) {
        // Se o valor a ser removido for maior que o valor do nó atual,
        // busca recursivamente na subárvore direita
        remover(&((*arvore)->dir), valor); // Buscar à direita
    } else {
        // O nó com o valor a ser removido foi encontrado

        // Caso 1: O nó tem no máximo um filho (nó folha ou com um único filho)
        if ((*arvore)->esq == NULL || (*arvore)->dir == NULL) {
            // 'temp' recebe o único filho (ou NULL se não houver filhos)
            AVL temp = ((*arvore)->esq) ? (*arvore)->esq : (*arvore)->dir;
            
            // Se o nó não tiver nenhum filho (nó folha)
            if (temp == NULL) {
                // Armazena temporariamente o nó a ser removido
                temp = *arvore;
                *arvore = NULL; // Define o ponteiro da árvore como NULL, removendo o nó
            } else {
                // Se o nó tem um único filho, copia o conteúdo do filho para o nó atual
                **arvore = *temp; // Copia o conteúdo do nó apontado por temp para o nó apontado por *arvore (modifica os dados do nó, mas não altera o ponteiro).
            }
            // Libera a memória do nó removido
            free(temp);

        } else {
            // Caso 3: O nó tem dois filhos
            // Encontra o sucessor in-order (menor valor da subárvore direita)
            AVL temp = (*arvore)->dir;// Isso daqui é preferencia ou convenção
            while(temp->esq) 
                temp = temp->esq; // Percorre até o nó mais à esquerda da subárvore direita

            // Substitui o valor do nó a ser removido pelo valor do sucessor
            (*arvore)->num = temp->num;

            // Remove o sucessor recursivamente (ele será um nó folha ou com um único filho)
            remover(&((*arvore)->dir), temp->num); // Remove o sucessor
        }
    }

    // Se a árvore ficou vazia após a remoção (somente no caso de remoção de nó folha)
    if (*arvore == NULL) return;

    // Passo 2: Atualizar a altura do nó atual
    atualizar_altura(*arvore);

    // Passo 3: Balancear a árvore
    // A função balanceamento ajusta o ponteiro 'arvore' conforme necessário
    // para garantir que as propriedades de balanceamento da árvore AVL sejam mantidas
    balanceamento(arvore);
}

void imprimirEmLargura(AVL arvore) {
    if (arvore == NULL) return;

    // Usar um vetor para armazenar nós
    AVL queue[100]; // Capacidade do vetor (ajuste conforme necessário)
    int front = 0, rear = 0;

    // Enqueue o nó raiz
    queue[rear++] = arvore;

    while (front < rear) {
        AVL node = queue[front++]; // Dequeue o primeiro nó
        printf("%d ", node->num); // Imprime o valor do nó

        // Enqueue os filhos esquerdo e direito
        if (node->esq != NULL) {
            queue[rear++] = node->esq;
        }
        if (node->dir != NULL) {
            queue[rear++] = node->dir;
        }
    }
}

int main() {
    AVL arvore = NULL;

    // Insere alguns valores na árvore
    inserir(&arvore, 10);
    inserir(&arvore, 20);
    inserir(&arvore, 30);
    inserir(&arvore, 40);
    inserir(&arvore, 50);
    inserir(&arvore, 25);
    //inserir(&arvore, 35);

    remover(&arvore, 30);

    // Exibe a árvore em ordem
    printf("Árvore em largura: ");
    imprimirEmLargura(arvore);
    
    printf("\n");

    return 0;
}