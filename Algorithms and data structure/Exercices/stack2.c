#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sElemento {
  struct sElemento *next;
  struct sElemento *prev;
  int dado;
} Elemento;

typedef struct sPilha {
  struct sElemento *head;
  struct sElemento *tail;
  int size;
} Pilha;

Pilha *criaPilha();
Elemento *criaElemento(char);
int push(Pilha *, char);
char pop(Pilha *);
void percorrePilha(Pilha *);
void limpaPilha(Pilha *);
void examinaExpressao(Pilha *, Pilha *);
void errorMessage();
bool open(char);
bool end(char);
bool compare(char, char);

int main() {
  Pilha *pilhaEnd = criaPilha();
  Pilha *pilhaStart = criaPilha();
  
  examinaExpressao(pilhaStart, pilhaEnd);
  return 0;
}

void examinaExpressao(Pilha *pilhaStart, Pilha *pilhaEnd) {
  printf("Digite a letra que vc deseja usar para finalizar a operação "
         "\n======================================================= \n");
  bool on = true;
  int correString = 0;
  char finish = getchar();
  char string[50] = "";
  int iniciador = 0;
  int finalizador = 0;
    
  printf("\nDigite a formula\n");
  while (on) {
    char ch = getchar();
    
    if(ch == finish){
      on = false;
      break;
    }
    
    string[correString] = ch;
    correString++;
    
    bool iniciando = open(ch);
    if(iniciando){
      push(pilhaStart, ch);
      iniciador++;
    }
    
    bool fechando = end(ch);
    if(fechando){
      if(pilhaStart->size == 0){
        errorMessage();
        finalizador++;
        break;
      }
      
      finalizador++;
      push(pilhaEnd, ch);
      bool comparadoCerto = compare(pilhaStart->head->dado, pilhaEnd->head->dado);
      if(comparadoCerto){
        pop(pilhaStart);
        pop(pilhaEnd);
        finalizador--;
        iniciador--;
      }else if (!comparadoCerto){
        printf("Expressão: %s \n", string);
        errorMessage();
        break;
      }
    }
  }

  if(iniciador != finalizador){
    printf("espressão: %s", string);
    errorMessage();
  }else if(pilhaStart->size == 0 && pilhaEnd->size == 0){
    printf("Expressão: %s", string);
    printf("Expressão valida");
  }else{
    printf("espressão: %s", string);
    errorMessage();
  }
}

bool compare(char iniciador, char finalizador) {
  if (iniciador == '{' && finalizador == '}')
    return true;
  else if (iniciador == '[' && finalizador == ']')
    return true;
  else if (iniciador == '(' && finalizador == ')')
    return true;
  else
    return false;
}

bool open(char c) {
  if ((c == '{') || (c == '[') || (c == '(')) {
    return true;
  } else {
    return false;
  }
}

bool end(char c) {
  if ((c == '}') || (c == ']') || (c == ')')) {
    return true;
  } else {
    return false;
  }
}

Pilha *criaPilha() {
  Pilha *pilha;
  pilha = (Pilha *)malloc(sizeof(Pilha));

  if (pilha == NULL) {
    return NULL;
  }

  pilha->size = 0;
  pilha->head = NULL;
  pilha->tail = NULL;

  return pilha;
}

Elemento *criaElemento(char dado) {
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

int push(Pilha *pilha, char dado) {
  Elemento *novo = criaElemento(dado);

  if (pilha->size == 0) {
    pilha->head = novo;
    pilha->tail = novo;
  } else {
    novo->next = pilha->head;
    pilha->head->prev = novo;
    pilha->head = novo;
  }

  pilha->size++;

  return 0;
}

char pop(Pilha *pilha) {
  Elemento *elemento = pilha->head;

  if (pilha->size == 0) {
    return -1;
  }

  if (elemento == NULL) {
    return -1;
  }

  if (elemento == pilha->head) {
    pilha->head = elemento->next;
    if (pilha->head == NULL)
      pilha->tail = NULL;
    else
      elemento->next->prev = NULL;
  } else {
    elemento->prev->next = elemento->next;
    if (elemento->next == NULL)
      pilha->tail = elemento->prev;
    else
      elemento->next->prev = elemento->prev;
  }

  char dado = elemento->dado;
  free(elemento);
  pilha->size--;

  return dado;
}

void percorrePilha(Pilha *pilha) {
  Elemento *aux;

  aux = pilha->head;
  int cont = 1;

  while (aux != NULL) {
    printf("%d- %c \n", cont, aux->dado);
    aux = aux->next;
    cont++;
  }
  printf("\n");
}

void errorMessage() { printf("\n Operação invalida! \n"); }
