/*
calcule media para 50 alunos, com 4 notas,
 media >= 7 aprovado media < 7 reprovado
*/

#include <stdio.h>

void calculaMedia(int b1){
  int cont;

  printf("\n\nMedia final:\n");
  cont = 1;
  do{
    printf("%i x %i: %i\n", n, cont, (n * cont));
    cont++;
  } while (cont <= 10);
}

void tabuadaFor(int n){
  int cont;
  //Procedimento para calcular a tabuada usando o For
  printf("\n\nTabuada calculada usando o for:\n");
  for (cont=1; cont <=10; cont++){
    printf("%i x %i: %i\n", n, cont, (n * cont));
  }
}

void tabuadaWhile(int n){
  int cont;

  //Procedimento para calcular a tabuada usando o While
  printf("\n\nTabuada calculada usando o while:\n");
  cont = 1;
  while (cont <= 10){
    printf("%i x %i: %i\n", n, cont, (n * cont));
    cont++;
  }
}


int main(void) {
  int n, i;
  
  printf("Informe o numero que se deseja calcular a tabuada: ");
  scanf("%i", &n);

  tabuadaFor(n);



  return 0;
}