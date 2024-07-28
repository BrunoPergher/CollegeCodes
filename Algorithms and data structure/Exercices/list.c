#include <stdio.h>
#include <stdlib.h>

typedef struct sElemento
{
  struct sElemento *next;
  int dado;
} Elemento;

typedef struct sLista
{
  struct sElemento *head;
  struct sElemento *tail;
  int size;
} Lista;

Lista* criaLista();
Elemento* criaElemento(int);
int insereElementoLista(Lista*, Elemento*, int);
void percorreLista(Lista *);

int main() {
  Lista* lista = criaLista();
  
  if (lista == NULL) {
    printf("Nao foi possivel alocar memoria para a lista!");
    return -1;
  }
  
  insereElementoLista(lista, lista->tail, 1);
  percorreLista(lista);
  insereElementoLista(lista, lista->tail, 100);
  percorreLista(lista);
  insereElementoLista(lista, lista->tail, 50);
  percorreLista(lista);
  insereElementoLista(lista, lista->tail, 10);
  percorreLista(lista);
  insereElementoLista(lista, lista->tail, 37);
  percorreLista(lista);

  return 0;
}

Lista* criaLista() {
  Lista* lista;
  lista = (Lista*) malloc(sizeof(Lista));
  if (lista == NULL)
    return NULL;

  lista->size = 0;
  lista->head = NULL;
  lista->tail = NULL;
  return lista;
}

Elemento* criaElemento(int dado) {
  Elemento* elemento;
  elemento = (Elemento*) malloc(sizeof(Elemento));
  if (elemento == NULL)
    return NULL;

  elemento->next = NULL;
  elemento->dado = dado;
  return elemento;
}

int insereElementoLista(Lista* lista, Elemento* pivo, int dado) {
  Elemento* novo = criaElemento(dado);
  if (novo == NULL)
    return -1;

  if (pivo == NULL){
    if(lista->size == 0){
      lista->tail = novo;
    }
    novo->next = lista->head;
    lista->head = novo;
  } else {
    if (pivo->next == NULL){
      lista->tail = novo;
    }
    novo->next = pivo->next;
    pivo->next = novo;
  }
  lista->size++;
  return 0;
}

void percorreLista(Lista* lista) {
  Elemento* aux;
  aux = lista->head;
  while(aux != NULL) {
    printf("%i ", aux->dado);
    aux = aux->next;
  }
  printf("\n");
}