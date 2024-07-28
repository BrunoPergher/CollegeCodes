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

  for(;;) {
    printf("\n=======================================\n");
    printf("Menu Lista\n");
    printf("=======================================\n \n");

    printf("1 - Inserir elemento na lista\n");
    printf("2 - Remover elemento na lista\n");
    printf("3 - Pesquisar elemento na lista\n");
    printf("4 - Visualizar Lista\n");
    printf("5 - Visualizar Lista Inversa\n");
    printf("0 - Finalizar Programa\n");
    scanf("%i", &indice);

    switch (indice) {
    case 1:
      printf("Qual elemento pivo deve ser usado ?\n 1-tail \n 2- head \n 3-Manual \n  4-Null \n");
      scanf("%i", &menuAdd);
      
      switch (menuAdd){
        case 1:
          printf("Qual elemento deve ser adicionado ?\n");
          scanf("%i", &valorElemento);
          addElementoLista(lista, lista->tail, valorElemento);
        break;

        case 2:  
          printf("Qual elemento deve ser adicionado ?\n");
          scanf("%i", &valorElemento);
          addElementoLista(lista, lista->head, valorElemento);
        break;

        case 3: 
          printf("Qual elemento é o pivo ?\n");
          scanf("%i", &valorElementoPivo);
          
          printf("Qual elemento deve ser adicionado ?\n");
          scanf("%i", &valorElemento);

          // TODO Use the manual VALUE
          // Elemento *ele1 = pesquisaListaInverso(lista, valorElemento);
          addElementoLista(lista, lista->head, valorElemento);
        break;

        case 4:  
          printf("Qual elemento deve ser adicionado ?\n");
          scanf("%i", &valorElemento);
          addElementoLista(lista, NULL, valorElemento);
        break;
      }

    case 2:
      printf("Qual elemento deve ser removido ?\n");
      scanf("%i", &valorElemento);
      
      Elemento *ele1 = pesquisaListaInverso(lista, valorElemento);
      printf("%i \n", ele1->dado);

      int removido = removeElementoLista(lista, ele1);
      printf("Removido o valor %i da lista \n", removido);
      percorreLista(lista);
      break;

    case 3:
      printf("Qual elemento deve ser pesquisado ?\n");
      scanf("%i", &valorElemento);
      
      Elemento *ele = pesquisaLista(lista, valorElemento);
      if(ele != NULL){
        printf("Existe\n");
      }
      else{
        printf("Não Existe\n");
      }
      break;

    case 4:
      percorreLista(lista);
      break;

    case 5:
      percorreListaInverso(lista);
      break;

    case 0:
      printf("Finalizando program bye bye...");
      indice = 0;
      break;

    default:
      printf("Numero invalido\n");
    }

    indice = 0;
  }

  limpaLista(lista);

  return 0;
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
  }
  
  if (elemento != aux->dado){
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