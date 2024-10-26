#include <stdio.h>
#include <stdlib.h>

typedef struct sLista {
  struct sElemento *head;
  struct sElemento *tail;
  int size;
} Lista;

typedef struct sElemento {
  struct sElemento *next;
  struct sElemento *prev;
  int dado;
} Elemento;

Lista *criaLista();
Elemento *criaElemento(int);
int addElementoLista(Lista *, Elemento *, int);
int removeElementoLista(Lista *, Elemento *);
void percorreLista(Lista *);
void percorreListaInverso(Lista *);
Elemento *pesquisaLista(Lista *, int);
Elemento *pesquisaListaInverso(Lista *, int);
void limpaLista(Lista *);

int main() {
  Lista *lista = criaLista();
  int indice = 50;
  int valorElemento, menuAdd;
  int valorElementoPivo;
  
  if (lista == NULL) {
    printf("Nao foi possivel alocar memoria para a lista!");
    return -1;
  }
  
  addElementoLista(lista, lista->tail, 15);
  addElementoLista(lista, lista->tail, 25);
  addElementoLista(lista, lista->head, 10);
  addElementoLista(lista, lista->tail, 27);
  addElementoLista(lista, NULL, 35);
  addElementoLista(lista, lista->head, 35);
  addElementoLista(lista, lista->tail, 29);
  addElementoLista(lista, NULL, 45);
  
  percorreLista(lista);
  percorreListaInverso(lista);

  removeElementoLista(lista, lista->tail);
  removeElementoLista(lista, lista->head);
  removeElementoLista(lista, NULL);
  Elemento *ele1 = pesquisaListaInverso(lista, 27);
  removeElementoLista(lista, ele1);
  ele1 = pesquisaListaInverso(lista, 55);
  removeElementoLista(lista, ele1);
  removeElementoLista(lista, lista->head);
  ele1 = pesquisaListaInverso(lista, 10);
  removeElementoLista(lista, ele1);

  percorreLista(lista);
  percorreListaInverso(lista);
}

Lista *criaLista() {
  Lista *lista;
  lista = (Lista *)malloc(sizeof(Lista));
  
  if (lista == NULL){
    return NULL;
  }

  lista->size = 0;
  lista->head = NULL;
  lista->tail = NULL;
  return lista;
}

Elemento *criaElemento(int dado) {
  Elemento *elemento;
  elemento = (Elemento *)malloc(sizeof(Elemento));
  
  if (elemento == NULL){
    return NULL;
  }
  
  elemento->next = NULL;
  elemento->prev = NULL;
  elemento->dado = dado;
  
  return elemento;
}

int addElementoLista(Lista *lista, Elemento *pivo, int dado) {
  Elemento *novo = criaElemento(dado);
  
  if ((pivo == NULL) && (lista->size > 0)){
    printf("Pivo é nulo, não foi possivel adicionar o %d \n", dado);
    return 1;
  }

  if (lista->size == 0) {
    lista->head = novo;
    lista->tail = novo;
  } else {
    novo->next = pivo->next;
    novo->prev = pivo;
    
  if (pivo->next == NULL){
    lista->tail = novo;
  } else {
    pivo->next->prev = novo;
  }
    
    pivo->next = novo;
  }
  
  lista->size++;
  return 0;
}

int removeElementoLista(Lista *lista, Elemento *elemento) {
  if(elemento == NULL){
    return -1;
  }
  
  if (lista->size == 0){
    return -1;
  }
  
  if ((elemento != NULL) && (lista->size > 0)) {
    if (elemento == lista->head) {
      lista->head = elemento->next;
      
      if (lista->head == NULL){
        lista->tail = NULL;
      } else{
        elemento->next->prev = NULL;
      }
    } else {
      elemento->prev->next = elemento->next;
      
      if (elemento->next == NULL){
        lista->tail = elemento->prev;
      } else {
        elemento->next->prev = elemento->prev;
      }
    }
  }
  
  int dado = elemento->dado;
  free(elemento);
  lista->size--;
  
  return dado;
}

void percorreLista(Lista *lista) {
  Elemento *aux;
  aux = lista->head;
  
  while (aux != NULL) {
    printf("%i ", aux->dado);
    aux = aux->next;
  }
  
  printf("\n");
}

void percorreListaInverso(Lista *lista) {
  Elemento *aux;
  aux = lista->tail;
  
  while (aux != NULL) {
    printf("%i ", aux->dado);
    aux = aux->prev;
  }
  
  printf("\n");
}

Elemento *pesquisaLista(Lista *lista, int dado) {
  Elemento *aux;
  aux = lista->head;
  
  while (aux != NULL) {
    if(aux->dado == dado){
      return aux;
    }
    
    aux = aux->next;
  }

  return NULL;
}

Elemento *pesquisaListaInverso(Lista *lista, int elemento) {
  Elemento *aux;
  aux = lista->tail;
  
  while (elemento != aux->dado) {
    aux = aux->prev;

    if(aux->prev == NULL){
      break;
    }
  }
  
  if (elemento != aux->dado){
    printf("O elemento %d não existe \n", elemento);
    return NULL;
  }
  
  return aux;
}

void limpaLista(Lista *lista) {
  while (lista->head != NULL) {
    removeElementoLista(lista, NULL);
  }
  
  free(lista);
}