#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct sElemento {
  struct sElemento *next;
  struct sElemento *prev;
  int dado;
} Elemento;

typedef struct sFila {
  struct sElemento *front;
  struct sElemento *rear;
  int size;
} Fila;

Elemento *criaElemento(int);
Fila *criaFila();
Elemento *procuraElementoMenor(Fila *);
int pqInsert(Fila *, int);
int pqMinRemove(Fila *);
void empty(Fila *);
int removeElemento(Fila *);
void imprimeFila(Fila *);

int main() {
  Fila *fila = criaFila();

  pqInsert(fila, 10);
  pqInsert(fila, 11);
  pqInsert(fila, 12);
  pqInsert(fila, 1);
  pqInsert(fila, 2);
  pqInsert(fila, 3);
  pqInsert(fila, 13);
  pqInsert(fila, 14);
  pqInsert(fila, 15);

  imprimeFila(fila);

  pqMinRemove(fila);
  pqMinRemove(fila);
  pqMinRemove(fila);
  imprimeFila(fila);

  return 0;
}

int pqInsert(Fila *fila, int chave) {
  Elemento *dado = criaElemento(chave);
  Elemento *pivo = fila->rear;

  if ((pivo == NULL) && (fila->size > 0)) {
    return -1;
  }

  if (fila->size == 0) {
    fila->front = dado;
    fila->rear = dado;
  } else {
    dado->next = pivo->next;
    dado->prev = pivo;

    if (pivo->next == NULL) {
      fila->rear = dado;
    } else {
      pivo->next->prev = dado;
    }

    pivo->next = dado;
  }

  fila->size++;

  return 0;
}

int pqMinRemove(Fila *fila) {
  if (fila->size == 0) {
    return -1;
  }

  Elemento *menorElemento = procuraElementoMenor(fila);
  if (menorElemento == NULL) {
    return -1;
  }

  if (menorElemento != NULL) {
    if (menorElemento == fila->front) {
      fila->front = menorElemento->next;

      if (fila->front == NULL) {
        fila->rear = NULL;
      } else

        menorElemento->next->prev = NULL;
    } else {
      menorElemento->prev->next = menorElemento->next;

      if (menorElemento->next == NULL) {
        fila->rear = menorElemento->prev;
      } else
        menorElemento->next->prev = menorElemento->prev;
    }
  }

  int dado = menorElemento->dado;
  free(menorElemento);
  fila->size--;

  return dado;
}

Elemento *procuraElementoMenor(Fila *fila) {
  int menor = INT_MAX;
  int i;
  Elemento *aux;

  menor = fila->front->dado;
  aux = fila->front;

  for (i = 0; i < fila->size; i++) {
    if (aux->dado < menor) {
      menor = aux->dado;
    }

    aux = aux->next;
  }

  aux = fila->front;
  while (aux != NULL) {
    if (aux->dado == menor) {
      return aux;
    }

    aux = aux->next;
  }

  return NULL;
}

int removeElemento(Fila *fila) {
  Elemento *elemento = fila->front;

  if (fila->size == 0) {
    return -1;
  }

  if (elemento == NULL) {
    return -1;
  }

  if ((elemento != NULL) && (fila->size > 0)) {
    if (elemento == fila->front) {
      fila->front = elemento->next;

      if (fila->front == NULL) {
        fila->rear = NULL;
      } else {
        elemento->next->prev = NULL;
      }
    } else {
      elemento->prev->next = elemento->next;

      if (elemento->next == NULL) {
        fila->rear = elemento->prev;
      } else {
        elemento->next->prev = elemento->prev;
      }
    }
  }

  int dado = elemento->dado;
  free(elemento);
  fila->size--;

  return dado;
}

void imprimeFila(Fila *fila) {
  Elemento *aux;
  aux = fila->front;

  while (aux != NULL) {
    printf("%i | ", aux->dado);
    aux = aux->next;
  }

  printf("\n");
}

Fila *criaFila() {
  Fila *fila;

  fila = (Fila *)malloc(sizeof(Fila));

  if (fila == NULL) {
    return NULL;
  }

  fila->size = 0;
  fila->front = NULL;
  fila->rear = NULL;

  return fila;
}

Elemento *criaElemento(int dado) {
  Elemento *elemento;

  elemento = (Elemento *)malloc(sizeof(Elemento));

  if (elemento == NULL) {
    return NULL;
  }

  elemento->next = NULL;
  elemento->prev = NULL;
  elemento->dado = dado;

  return elemento;
}

void empty(Fila *fila) {
  while (fila->front != NULL) {
    removeElemento(fila);
  }

  free(fila);
}