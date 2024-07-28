#include <stdio.h>
#include <stdlib.h>

typedef struct sElement {
  int chave;
  int placa;
  struct sElement *prox;
} element;

typedef struct sFila {
  element *front;
  element *rear;
  int tamanho;
  int maxSize;
} fila;

fila *criaFila(int maxFila);
fila *destroiFila(fila *f);
element *pesquisaFila(fila *f, int elemento);
int empty(fila *f);
int tamanhoFila(fila *f);
int pqinsert(fila *f, int elemento);
int pqmindelete(fila *f, int *elemento);
void imprimeFila(fila *f);
void validaInsert(fila *f, int elemento, fila *fSec);
void validaRemove(fila *f, int elemento, fila *fSec);
int removeElementoFila(fila *f, element *elemento, fila *fSec);
void rotacionarFila(fila *f, element *elemento, fila *fSec);

int main() {
  fila *f;
  fila *fSecundaria;
  int op;
  int n;
  int retirar = 0;

  if (!(f = criaFila(10))) {
    printf("Erro na alocação de memória!");
    return 1;
    free(f);
    f = NULL;
  }

  if (!(fSecundaria = criaFila(100))) {
    printf("Erro na alocação de memória!");
    return 1;
    free(f);
    f = NULL;
  }

  validaInsert(f, 1, fSecundaria);
  validaInsert(f, 2, fSecundaria);
  validaInsert(f, 3, fSecundaria);
  validaInsert(f, 4, fSecundaria);
  validaInsert(f, 5, fSecundaria);
  validaInsert(f, 6, fSecundaria);
  validaInsert(f, 7, fSecundaria);
  validaInsert(f, 8, fSecundaria);
  validaInsert(f, 9, fSecundaria);
  validaInsert(f, 10, fSecundaria);
  validaInsert(f, 11, fSecundaria);
  validaInsert(f, 12, fSecundaria);
  
  
  imprimeFila(f);

  validaRemove(f, f->front->chave, fSecundaria);
  validaRemove(f, f->front->chave, fSecundaria);
  validaRemove(f, f->front->chave, fSecundaria);
  validaRemove(f, f->front->chave, fSecundaria);
  
  element *ele1 = pesquisaFila(f, 7);
  
  removeElementoFila(f, ele1, fSecundaria);
  imprimeFila(f);
  
  destroiFila(fSecundaria);
  destroiFila(f);

  return 0;
}

fila *criaFila(int maxFila) {
  fila *f;

  if ((f = malloc(sizeof(fila))) == NULL) {
    return NULL;
  }

  f->front = NULL;
  f->rear = NULL;
  f->tamanho = 0;
  f->maxSize = maxFila;
  return f;
}

fila *destroiFila(fila *f) {
  while (f->front != NULL) {
    validaRemove(f, f->front->chave, f);
  }

  free(f);
  return f;
}

int empty(fila *f) {
  if ((f->front != NULL) && (f->rear != NULL)) {
    return 0;
  }

  return 1;
}

int tamanhoFila(fila *f) { return f->tamanho; }

void validaInsert(fila *f, int elemento, fila *fSec) {
  if (!(pqinsert(f, elemento))) {
    if (f->tamanho == f->maxSize) {
      printf("Estacionamento cheio, vc sera movido para a lista de espera\n");

      validaInsert(fSec, elemento, f);
      printf("fila SECUNDARIA:\n");
      imprimeFila(fSec);

    } else {
      printf("Inserção falha!");
    }
  }
}

void rotacionarFila(fila *f, element *elemento, fila *fSec) {
  validaInsert(f, elemento->chave, fSec);
  validaRemove(f, elemento->chave, fSec);
}

int removeElementoFila(fila *f, element *elemento, fila *fSec) {
  element *aux = f->front;
  element *first = f->front;

    printf("dfsdf");
  
  while (elemento->chave != aux->chave) {
    rotacionarFila(f, aux, fSec);
    if (aux == NULL) {
      printf("aux null");
    }
    aux = aux->prox;
    if (aux == NULL) {
      printf("aux null");
    }
    if (aux->prox == NULL) {
      break;
    }
  }

  if (elemento->chave == aux->chave) {
    aux = aux->prox;
    validaRemove(f, elemento->chave, f);
  }

  while (first->chave != aux->chave) {
    rotacionarFila(f, aux, fSec);
    aux = aux->prox;
    if (aux->prox == NULL) {
      break;
    }
  }

  return 1;
}

element *pesquisaFila(fila *f, int elemento) {
  element *aux;
  aux = f->front;

  while (elemento != aux->chave) {
    aux = aux->prox;

    if (aux->prox == NULL) {
      break;
    }
  }

  if (elemento != aux->chave) {
    printf("O elemento %d não existe \n", elemento);
    return NULL;
  }

  return aux;
}

void validaRemove(fila *f, int elemento, fila *fSec) {
  if (!(pqmindelete(f, &elemento))) {
    if (f->tamanho == 0) {
      printf("Fila vazia.\n");
      return;
      
    } else {
      if (f->tamanho > 0 && f->tamanho < f->maxSize && fSec->front != NULL) {
        validaInsert(f, fSec->front->chave, fSec);
        printf(
            "adicionando elemento da fila secundaria para a fila principal\n");
        validaRemove(fSec, fSec->front->chave, fSec);

        if (fSec->tamanho > 0) {
          printf("fila SECUNDARIA: \n");
          imprimeFila(fSec);
        }
      }
    }
  }
}

int pqinsert(fila *f, int elemento) {
  element *tmp;

  if (f->tamanho == f->maxSize) {
    return 0;
  }

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
  if (empty(f)) {
    return 0;
  }

  element *tmp;
  tmp = f->front;

  *elemento = f->front->chave;
  f->front = f->front->prox;

  free(tmp);

  if (f->tamanho == f->maxSize) {
    f->tamanho--;
    return 0;
  }

  f->tamanho--;

  return 1;
}

void imprimeFila(fila *f) {
  element *elemento = f->front;

  while (elemento != NULL) {
    printf("%.d\t", elemento->chave);
    elemento = elemento->prox;
  }

  printf("\n\n");
}