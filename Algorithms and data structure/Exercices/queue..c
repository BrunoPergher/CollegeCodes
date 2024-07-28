#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sElement {
  int chave;
  struct sElement *prox;
} element;

typedef struct sFila {
  element *front;
  element *rear;
  int tamanho;
} fila;

fila *criaFila();
fila *destroiFila(fila *f);
int empty(fila *f);
int tamanhoFila(fila *f);
int pqinsert(fila *f, int elemento);
int pqmindelete(fila *f, int *elemento);
void imprimeFila(fila *f);

int main() {
  fila *f;
  int op;
  int n;
  int retirar = 0;

  if (!(f = criaFila())) {
    printf("Erro na alocação de memória!");

    return 1;

    free(f);
    f = NULL;
  }

  do {
    printf("\n======================== Fila ========================");
    printf("\n0 - Sair \n1 - Inserir \n2 - Remover \n3 - Quantidade de "
           "elementos na fila \n4 - Imprime a fila\n");
    printf("\nEscolha uma opção de ação: ");
    scanf("%d", &op);

    switch (op) {
    case 1:
      printf("Inserir elemento: ");
      scanf("%d", &n);

      if (!(pqinsert(f, n))) {
        printf("Inserção falha!");
      }
      break;

    case 2:
      if (!(pqmindelete(f, &retirar))) {
        printf("Fila vazia.\n");
      } else {
        printf("\nElemento retirado: %d\n", retirar);
      }
      break;

    case 3:
      printf("Quantidade de elementos na fila: %d\n", tamanhoFila(f));
      break;

    case 4:
      imprimeFila(f);
      break;

    default:
      if (op != 0 || op != 1 || op != 2 || op != 3 || op != 4) {
        if (op == 0) {
          printf("saindo....");
        } else {
          printf("\nNúmero fora do menu!\n");
        }
      }
    }
  } while (op != 0);

  destroiFila(f);

  return 0;
}

fila *criaFila() {
  fila *f;

  if ((f = malloc(sizeof(fila))) == NULL) {
    return NULL;
  }

  f->front = NULL;
  f->rear = NULL;
  f->tamanho = 0;
  return f;
}

fila *destroiFila(fila *f) {
  element *tmp1 = f->front;
  element *tmp2 = f->front->prox;

  while ((tmp1 != NULL) && (tmp2 != NULL)) {
    free(tmp1);
  }

  free(f);
  f = NULL;

  return NULL;
}

int empty(fila *f) {
  if ((f->front != NULL) && (f->rear != NULL)) {
    return 0;
  }

  return 1;
}

int tamanhoFila(fila *f) { return f->tamanho; }

int pqinsert(fila *f, int elemento) {
  element *tmp;

  if ((tmp = malloc(sizeof(element))) == NULL) {
    return 0;
  }

  tmp->chave = elemento;
  tmp->prox = NULL;

  if (empty(f)) {
    f->front = tmp;
  } else {
    f->rear->prox = tmp;
  }

  f->rear = tmp;
  f->tamanho++;

  return 1;
}

int pqmindelete(fila *f, int *elemento) {
  element *tmp;
  tmp = f->front;

  if (empty(f)) {
    return 0;
  }

  *elemento = f->front->chave;
  f->front = f->front->prox;

  free(tmp);
  f->tamanho--;
  return 1;
}

void imprimeFila(fila *f) {
  element *tmp = f->front;

  while (tmp != NULL) {
    printf("%.d\t", tmp->chave);
    tmp = tmp->prox;
  }

  printf("\n\n");
}