#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 53

// # Region Structs #
typedef struct sElemento {
  struct sElemento *next;
  struct sElemento *prev;
  char dado[50];
} Elemento;

typedef struct sLista {
  struct sElemento *head;
  struct sElemento *tail;
  struct sLista *next;
  struct sLista *prev;
  int chave;
  int size;
} Lista;

typedef struct sTabela {
  struct sLista *head;
  struct sLista *tail;
  int chave;
  int size;
} Tabela;

// # End Region Structs #

// # Region Prototipação #
int hash(char *dado);

Elemento *alocaMemoriaElemento(char *dado);
Lista *alocaMemoriaLista(int chave);
Tabela *alocaMemoriaTabela();

Elemento *buscarElemento(Lista *lista, char *dado);
int contaTotalNomesLista(Lista *lista, char *dado);

void insereLista(Lista *lista, Elemento *pivo, char *dado);
Lista *buscaLista(Tabela *tabela, int chave);
void removeElementoDaLista(Tabela *tabela, char *dado);
void imprimeLista(Lista *lista);

void insereTabela(Tabela *tabela, Lista *pivo, char *dado);
void removeListaDaTabela(Tabela *tabela, Lista *lista);
void imprimeTabela(Tabela *tabela);
int contaTotalNomes(Tabela *tabela);
void insereNome(Tabela *tabela, char *dado);
void insereArquivo(Tabela *tabela);
int pesquisaNome(Tabela *tabela, char *dado);

void swap(Elemento *A, Elemento *B);
Elemento *particionarElementos(Lista *lista, Elemento *left, Elemento *pivo);
void quickSort(Lista *lista, Elemento *left, Elemento *right, int i);
// # End Region Prototipação #

// # Region Quick sort #

int main() {
  Tabela *tabela = alocaMemoriaTabela();
  Lista *lista;
  int opcao, chave, flag = 0;
  char nome[50];

  do {
    printf("\n==========  Banco de nomes  ==========\n");
    printf("1 - Inserir nomes do arquivo\n");
    printf("2 - Inserir nome\n");
    printf("3 - Pesquisar nome\n");
    printf("4 - Imprimir nomes por lista\n");
    printf("5 - Imprimir todos os nomes\n");
    printf("6 - Quantidade de nomes em uma lista\n");
    printf("7 - Quantidade de nomes total\n");
    printf("8 - Ordenar uma lista\n");
    printf("9 - Ordenar todas as listas\n");
    printf("10 - Remover nome\n");
    printf("11 - Todas as listas e quantidade de elementos nelas.\n");

    printf("Opcao: ");
    scanf("%d", &opcao);

    system("clear");
    switch (opcao) {
    case 1:
      insereArquivo(tabela);

      break;
    case 2:
      printf("\nQual o nome a ser adicionado ?\n");
      scanf("%s", nome);

      insereNome(tabela, nome);

      break;
    case 3:
      printf("\nColoque o nome a ser buscado: ");
      scanf("%s", nome);

      int busca = pesquisaNome(tabela, nome);

      if (busca > 0) {
        printf("\n O nome %s foi encontrado(s) %d na lista", nome, busca);
      } else {
        printf("\n%s nao encontrado(a)", nome);
      }
      break;
    case 4:
      printf("\nQual a chave ? ");
      scanf("%d", &chave);

      lista = buscaLista(tabela, chave);

      if (lista == NULL) {
        printf("Não existe uma lista criada com essa chave");
      } else {
        imprimeLista(lista);
      }

      break;
    case 5:
      imprimeTabela(tabela);

      break;
    case 6:
      printf("\nColoque a chave da lista: ");
      scanf("%d", &chave);

      lista = buscaLista(tabela, chave);
      if (lista == NULL) {
        printf("Não existe uma lista criada com essa chave");
      } else {
        printf("\nQuantidade de nomes na lista %d: %d\n", chave, lista->size);
      }

      break;
    case 7:
      printf("\nQuantidade de nomes na tabela: %d\n", contaTotalNomes(tabela));

      break;
    case 8:
      printf("\nColoque a chave da lista: ");
      scanf("%d", &chave);

      lista = buscaLista(tabela, chave);
      if (lista == NULL) {
        printf("Não existe uma lista criada com essa chave");
      } else {
        quickSort(lista, lista->head, lista->tail, 0);
      }

      break;
    case 9:
      printf("\nOrdenando...");

      lista = tabela->head;
      for (int i = 0; i < tabela->size; i++) {
        lista = buscaLista(tabela, lista->chave);
        quickSort(lista, lista->head, lista->tail, 0);

        lista = lista->next;
      }

      break;
    case 10:
      printf("\nQual o nome a ser removido ? \n");
      scanf("%s", nome);

      removeElementoDaLista(tabela, nome);

      break;
    case 11:
      lista = tabela->head;
      if (lista == NULL) {
        printf("Não existe listas criadas");
      }

      while (lista != NULL) {
        printf("%d\n", lista->size);
        lista = lista->next;
      }

      break;
    default:
      flag += 1;

      break;
    }
  } while (flag == 0);

  free(lista);
  free(tabela);

  return 0;
}

// # Region Methods #

// # Region Hash #

int hash(char *dado) {
  //char *str = dado;
  int i, chave = 0;
  for (i=0; i<strlen(dado); i++){
    chave+=dado[i] * 7;
  }
  return (chave % M);
}
// # End Region Hash #

// # Region Alocação de memória #

Elemento *alocaMemoriaElemento(char *dado) {
  Elemento *elemento = (Elemento *)malloc(sizeof(Elemento));

  strcpy(elemento->dado, dado);
  elemento->next = NULL;
  elemento->prev = NULL;

  return elemento;
}

Lista *alocaMemoriaLista(int chave) {
  Lista *lista = (Lista *)malloc(sizeof(Lista));

  lista->next = NULL;
  lista->prev = NULL;
  lista->chave = chave;
  lista->size = 0;

  return lista;
}

Tabela *alocaMemoriaTabela() {
  Tabela *tabela = (Tabela *)malloc(sizeof(Tabela));

  tabela->head = NULL;
  tabela->tail = NULL;
  tabela->size = 0;

  return tabela;
}

// # End Region Alocação de memória #

// # Region Elemento #

Elemento *buscarElemento(Lista *lista, char *dado) {
  Elemento *elemento = lista->head;

  while (elemento != NULL) {
    if (strcmp(elemento->dado, dado) == 0) {
      return elemento;
    }

    elemento = elemento->next;
  }

  return NULL;
}

int contaTotalNomesLista(Lista *lista, char *dado) {
  Elemento *elemento = lista->head;
  int cont = 0;

  while (elemento != NULL) {
    if (strcmp(elemento->dado, dado) == 0) {
      cont++;
    }

    elemento = elemento->next;
  }

  return cont;
}

// # End Region elemento #

// # Region Listas #
void insereLista(Lista *lista, Elemento *pivo, char *dado) {
  Elemento *elementoParaAdicionar = alocaMemoriaElemento(dado);

  if ((pivo == NULL) && (lista->size != 0)) {
    elementoParaAdicionar->next = lista->head;
    elementoParaAdicionar->next->prev = elementoParaAdicionar;
    lista->head = elementoParaAdicionar;

  } else if (lista->size == 0) {
    lista->head = elementoParaAdicionar;
    lista->tail = elementoParaAdicionar;

  } else {
    elementoParaAdicionar->next = pivo->next;
    elementoParaAdicionar->prev = pivo;

    if (pivo->next == NULL) {
      lista->tail = elementoParaAdicionar;
    } else {
      pivo->next->prev = elementoParaAdicionar;
    }

    pivo->next = elementoParaAdicionar;
  }

  lista->size++;
}

Lista *buscaLista(Tabela *tabela, int chave) {
  Lista *lista = tabela->head;

  while (lista != NULL) {
    if (lista->chave == chave) {
      return lista;
    }

    lista = lista->next;
  }

  return NULL;
}

void removeElementoDaLista(Tabela *tabela, char *dado) {
  int chave = hash(dado);

  Lista *lista = buscaLista(tabela, chave);
  if (lista == NULL) {
    printf("Não foi possivel remover pois esse elemento não existe");

    return;
  }

  Elemento *elemento = buscarElemento(lista, dado);
  if (elemento == NULL) {
    printf("Não foi possivel remover pois esse elemento não existe");

    return;
  }

  if ((lista != NULL) && (elemento != NULL)) {
    if ((elemento != NULL) && (lista->size != 0)) {
      if (elemento == lista->head) {
        lista->head = elemento->next;

        if (lista->head == NULL) {
          lista->tail = NULL;
        } else {
          elemento->next->prev = NULL;
        }
      } else {
        elemento->prev->next = elemento->next;

        if (elemento->next == NULL) {
          lista->tail = elemento->prev;
        } else {
          elemento->next->prev = elemento->prev;
        }
      }

      free(elemento);
      lista->size--;

      if (lista->size == 0) {
        removeListaDaTabela(tabela, lista);
      }
    }
  }
}

void imprimeLista(Lista *lista) {
  if (lista != NULL) {
    Elemento *elemento = lista->head;

    printf("Chave %d \n", lista->chave);
    while (elemento != NULL) {
      printf("%s\n", elemento->dado);
      elemento = elemento->next;
    }

    printf("\n");
  }
}

// # End Region Listas #

// # Region Tabela #

void imprimeTabela(Tabela *tabela) {
  int myNumbers[] = {39, 7,  40, 8,  41, 9,  42, 10, 43, 11, 44, 12, 45,
                     13, 46, 14, 47, 15, 48, 16, 49, 17, 50, 18, 51, 19,
                     52, 20, 53, 21, 54, 22, 55, 23, 56, 24, 57, 25, 0,
                     26, 1,  57, 2,  28, 3,  29, 5,  31, 6,  32};

  for (int i = 0; i < 52; i++) {
    Lista *lista = buscaLista(tabela, myNumbers[i]);

    if (lista != NULL) {
      imprimeLista(lista);
    }
  }
}

int contaTotalNomes(Tabela *tabela) {
  Lista *lista = tabela->head;
  int qtdNomes = 0;

  while (lista != NULL) {
    qtdNomes += lista->size;
    lista = lista->next;
  }

  return qtdNomes;
}

void insereNome(Tabela *tabela, char *dado) {
  int chave = hash(dado);
  Lista *lista = buscaLista(tabela, chave);
  insereTabela(tabela, lista, dado);
}

void insereArquivo(Tabela *tabela) {
  FILE *file;
  char nome[50];

  file = fopen("nomes.txt", "r");

  while (fgets(nome, 50, file) != NULL) {
    strcpy(nome, strtok(nome, "\n"));
    insereNome(tabela, nome);
  }
}

int pesquisaNome(Tabela *tabela, char *dado) {
  int chave = hash(dado);
  Lista *lista = buscaLista(tabela, chave);
  int cont = 0;

  if (lista != NULL) {
    cont = contaTotalNomesLista(lista, dado);
  }

  if (cont > 0) {
    return cont;
  }

  return -1;
}

void insereTabela(Tabela *tabela, Lista *pivo, char *dado) {
  int chave = hash(dado);

  Lista *lista = buscaLista(tabela, chave);

  if (lista == NULL) {
    lista = alocaMemoriaLista(chave);

    if ((pivo == NULL) && (tabela->size != 0)) {
      lista->next = tabela->head;
      lista->next->prev = lista;
      tabela->head = lista;

    } else if (tabela->size == 0) {
      tabela->head = lista;
      tabela->tail = lista;

    } else {
      lista->next = pivo->next;
      lista->prev = pivo;

      if (pivo->next == NULL) {
        tabela->tail = lista;
      } else {
        pivo->next->prev = lista;
      }

      pivo->next = lista;
    }

    tabela->size++;
  }

  insereLista(lista, lista->tail, dado);
}

void removeListaDaTabela(Tabela *tabela, Lista *lista) {
  if ((lista != NULL) && (tabela->size != 0)) {
    if (lista == tabela->head) {
      tabela->head = lista->next;

      if (tabela->head == NULL) {
        tabela->tail = NULL;
      } else {
        lista->next->prev = NULL;
      }
    } else {
      lista->prev->next = lista->next;

      if (lista->next == NULL) {
        tabela->tail = lista->prev;
      } else {
        lista->next->prev = lista->prev;
      }
    }

    free(lista);
    tabela->size--;
  }
}
// # End Region Tabela #

// # Region Quick sort #
void swap(Elemento *A, Elemento *B) {
  char temp[30];
  strcpy(temp, A->dado);
  strcpy(A->dado, B->dado);
  strcpy(B->dado, temp);
}

Elemento *particionarElementos(Lista *lista, Elemento *left, Elemento *pivo) {
  ///* Considers last element as pivot, places the
  // pivot element at its correct position in sorted array,
  // and places all smaller (smaller than pivot) to left
  // of pivot and all greater elements to right of pivot */
  Elemento *aux = left->prev;

  for (Elemento *i = left; i != pivo; i = i->next) {
    if (strcmp(i->dado, pivo->dado) < 0) {
      if (aux) {
        aux = aux->next;
      } else {
        aux = left;
      }

      swap(aux, i);
    }
  }

  if (aux) {
    aux = aux->next;
  } else {
    aux = left;
  }

  swap(aux, pivo);

  return aux;
}

void quickSort(Lista *lista, Elemento *left, Elemento *right, int i) {
  if (right != NULL && left != NULL && left != right && left != right->next) {
    Elemento *pivo = particionarElementos(lista, left, right);

    quickSort(lista, left, pivo->prev, i + 1);
    quickSort(lista, pivo->next, right, i + 1);
  }
}
// # End Region Quick sort #

// # End Region Methods #
