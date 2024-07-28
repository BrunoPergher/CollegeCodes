#include <stdio.h>
#include <stdlib.h>
#define True 1
#define False 0

typedef struct TNo {
  int indice;
  struct TNo *dir, *esq;
} TNo;

typedef struct TArvore {
  struct TNo *ini;
  int tam;
  int altura;
} TArvore;

/* Inicializa a arvore */
void _init_Arvore(TArvore *A) {
  A->ini = NULL;
  A->tam = 0;
  A->altura = 0;
}

/* Cria novo no */
TNo *novoNO(int chave) {
  TNo *novo;
  novo = malloc(sizeof(TNo));
  novo->dir = NULL;
  novo->esq = NULL;
  novo->indice = chave;
  return novo;
}

/* Insere novo no na arvore */
int insereNO(TArvore *A, int chave) {
  int h = 1;
  TNo *pont;
  pont = A->ini;
  if (A->tam == 0) {
    A->ini = novoNO(chave);
    A->tam++;
    A->altura++;
    return 0;
  }

  while (pont != NULL) {
    h++;
    if (chave < pont->indice) { // verifica se a chave vai ser inserida a
                                // esquerda ou a direita
      if (pont->esq != NULL) {  // verifica se existe filho a esquerda
        pont = pont->esq;
      } else {
        pont->esq = novoNO(chave);
        A->tam++;
        if (h > A->altura)
          A->altura = h; // atualiza altura
        return 0;
      }
    } else {
      if (pont->dir != NULL) { // verifica se existe filho a direita
        pont = pont->dir;
      } else {
        pont->dir = novoNO(chave);
        A->tam++;
        if (h > A->altura)
          A->altura = h; // atualiza altura
        return 0;
      }
    }
  }
  return -1;
}

/* Remove um no da arvore */
TNo *removeNO(TArvore *A, TNo *no) {
  TNo *aux;
  A->tam--;
  // caso no removido seja folha
  if (no->dir == NULL && no->esq == NULL)
    return NULL;
  // caso o no removido tenha os dois filhos
  if (no->esq != NULL && no->dir != NULL) {
    aux = no->dir;
    while (aux->esq->esq != NULL)
      aux = aux->esq;
    no->indice = aux->esq->indice; // copia o menor filho
    aux->esq = aux->esq->dir;      // sobe o filho da direita do menor filho
    return no;
  }
  // caso no tenha apenas o filho direito
  if (no->dir != NULL)
    return no->dir;
  // caso no tenha apenas o filho esquerdo
  if (no->esq != NULL)
    return no->esq;
  exit - 1;
}

/* Mede a altura da arvore */
void medeAltura(TArvore *A, TNo *no, int h) {
  if (A == NULL)
    return;
  if (h > A->altura)
    A->altura = h;
  h++;
  if (no->dir != NULL)
    medeAltura(A, no->dir, h);
  if (no->esq != NULL)
    medeAltura(A, no->esq, h);
}

/* Busca um no pelo valor de seu indice */
int buscaNO(TArvore *A, int chave) {
  A->altura = 0;
  TNo *pont = A->ini;
  while (pont != NULL) {
    if (pont->indice == chave) { // verifica se encontrou o valor buscado
      pont = removeNO(A, pont);
      return True;
    }
    if (chave < pont->indice)
      pont = pont->esq; // verifica se o valor buscado é < ou > que o indice
    else
      pont = pont->dir;
  }
  insereNO(A, chave);
  medeAltura(A, A->ini, 0);
  return False;
}

/* Funcao principal */
int main() {
  int chave, i;
  TArvore A;
  _init_Arvore(&A);
  printf("Insira as chaves a serem inseridas na árvore. Insira -1 "
                     "para parar.\n");
  while (True) {
    scanf("%d", &chave);
    if (chave < 0)
      break;
    insereNO(&A, chave);
  }
  printf("Número de elementos inseridos:"" %d\n",
         A.tam);
  printf("Altura da árvore:"  " %d\n", A.altura);
  printf("Insira o valor a ser buscado.\n");
  scanf("%d", &chave);
  buscaNO(&A, chave);
  printf("Novo número de elementos:"  " %d\n" , A.tam);
  printf("Nova altura da árvore:"  " %d\n" , A.altura);
  return 0;
}