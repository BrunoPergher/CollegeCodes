/*Um tipo abstrato de dados (Registro) que represente cada um dos pixels coloridos da imagem, ou seja, que represente o padrão RGB;
Uma matriz rgb(N,M) dinâmica, onde N e M são duas constantes de tamanhos 10 e 15 respectivamente, onde cada elemento da matriz é um pixel da imagem colorida;
Procedimentos para carregar e escrever a imagem (a matriz). Sugestão: considere que em um problema do mundo real a imagem terá muitos pixels para serem carregados, de modo que é praticamente impossível ao usuário digitar cada um dos valores para cada pixel. Neste caso, os valores seriam lidos a partir de um arquivo de imagem. Assim, a sugestão é que os valores iniciais sejam gerados aleatoriamente no intervalo entre [0 .. 255];
Uma segunda matriz dinâmica gray[N,M] de inteiros para armazenar os valores dos pixels da imagem em tons de cinza;
Um procedimento para calcular o valor dos pixel em tons de cinza, onde para tal procedimento deve ser utilizada a seguinte operação: gray = 0.300 * R + 0.590 * G + 0.110 * B;
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 1
#define M 5

typedef struct {
  int R;
  int G;
  int B;
} Color;

// Protótipos dos módulos
Color **alocaMemoriaMatrizDinamica(int, int);
int **alocaMemoriaMatrizDinamicaGray(int, int);
void carregaMatrizDinamica(Color**, int, int);
void escreveMatrizDinamica(Color**, int, int);
void carregaMatrizDinamicaGray(Color**, int**, int, int);
void escreveMatrizDinamicaGray(int**, int, int);
void liberaMemoriaMatrizDinamica(Color**, int);
int calculateGrayscale(Color);

int main() {
  srand(time(NULL));
  Color **colors;
  int** colorsGrayscale;
  
  colors = alocaMemoriaMatrizDinamica(N, M);
  colorsGrayscale = alocaMemoriaMatrizDinamicaGray(N, M);
  
  carregaMatrizDinamica(colors, N, M);
  escreveMatrizDinamica(colors, N, M);

  carregaMatrizDinamicaGray(colors, colorsGrayscale, N, M);
  escreveMatrizDinamicaGray(colorsGrayscale, N, M);
  
  liberaMemoriaMatrizDinamica(colors, N);

  return 0;
}

Color **alocaMemoriaMatrizDinamica(int n, int m) {
  Color **mat;
  int i, j;
  
  mat = (Color **)malloc(sizeof(Color *) * n);
  
  for (i = 0; i < n; i++)
    mat[i] = malloc(m * sizeof(Color));
  
  return mat;
}

int** alocaMemoriaMatrizDinamicaGray(int lin, int col) {
  int **mat ;
  int i, j ;
  
  mat = (int **)malloc(sizeof(int *) * lin);
  
  for (i=0; i < lin; i++)
   mat[i] = malloc (col * sizeof (int));
  
  return mat;
}

void carregaMatrizDinamica(Color** ma, int n, int m) {
  // Procedimento para carregar a matriz
  int l, c;

  for (l = 0; l < n; l++) {
    for (c = 0; c < m; c++) {
      ma[l][c].R = rand() % 255;
      ma[l][c].G = rand() % 255;
      ma[l][c].B = rand() % 255;
    }
  }
}

void carregaMatrizDinamicaGray(Color** ma, int** maGrayscale, int n, int m) {
  // Procedimento para carregar a matriz
  int l, c;

  for (l = 0; l < n; l++) {
    for (c = 0; c < m; c++) {
      maGrayscale[l][c] = calculateGrayscale(ma[l][c]);
    }
  }
}

void escreveMatrizDinamica(Color** ma, int n, int m) {
  // Procedimento para escrever a matriz
  int l, c;
  for (l = 0; l < n; l++) {
    for (c = 0; c < m; c++) {
      printf("Pixel Linha: %i, coluna: %i \n", l+1, c+1);
      printf("R:\t%i \n", ma[l][c].R);
      printf("G:\t%i \n", ma[l][c].G);
      printf("B:\t%i \n", ma[l][c].B);
      printf("\n");
    }
    printf("\n");
  }
}

void escreveMatrizDinamicaGray(int** ma, int n, int m) {
  // Procedimento para escrever a matriz
  int l, c;
  for (l = 0; l < n; l++) {
    for (c = 0; c < m; c++) {
      printf("Pixel GrayScale \n");
      printf("Pixel Linha: %i, coluna: %i \n", l+1, c+1);
      printf("%d ", ma[l][c]);
      printf("\n");
    }
    printf("\n");
  }
}

void liberaMemoriaMatrizDinamica(Color** ma, int n) {
  // Procedimento para desalocar memoria da matriz
  int i;
  for (i = 0; i < n; i++) {
    free(ma[i]);
  }
  free(ma);
}

int calculateGrayscale(Color color) {
  return (0.300 * color.R + 0.590 * color.G + 0.110 * color.B);
}