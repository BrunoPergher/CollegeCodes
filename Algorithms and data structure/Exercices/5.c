/*Um tipo abstrato de dados (Registro) que represente cada um dos pixels coloridos da imagem, ou seja, que represente o padrão RGB;
Uma matriz rgb(N,M) dinâmica, onde N e M são duas constantes de tamanhos 10 e 15 respectivamente, onde cada elemento da matriz é um pixel da imagem colorida;
Procedimentos para carregar e escrever a imagem (a matriz). Sugestão: considere que em um problema do mundo real a imagem terá muitos pixels para serem carregados, de modo que é praticamente impossível ao usuário digitar cada um dos valores para cada pixel. Neste caso, os valores seriam lidos a partir de um arquivo de imagem. Assim, a sugestão é que os valores iniciais sejam gerados aleatoriamente no intervalo entre [0 .. 255];
Uma segunda matriz dinâmica gray[N,M] de inteiros para armazenar os valores dos pixels da imagem em tons de cinza;
Um procedimento para calcular o valor dos pixel em tons de cinza, onde para tal procedimento deve ser utilizada a seguinte operação: gray = 0.300 * R + 0.590 * G + 0.110 * B;
*/
#include <stdio.h>
#include <stdlib.h>
#define N 10
#define M 15

typedef struct {
    int R;
    int G;
    int B;
} Color;

void liberaMemoriaVetor(Color* colors){
    free(colors);
}

Color* alocaMemoriaVetorColors(int tam){
    return (Color*) malloc(sizeof(Color) * tam);
}

void carregaVetorColors(Color* colors, int tam){
    int i;
    printf("\n");
    for(i=0; i<tam; i++){
        colors[i].R = rand() % 255;
        colors[i].G = rand() % 255;
        colors[i].B = rand() % 255;
    }
}

void escreveVetorColors(Color* colors, int tam){
    int i;
    for(i=0; i<tam; i++){
        printf("\tR: %i\n", colors[i].R);
        printf("\tG: %i\n", colors[i].G);
        printf("\tB: %i\n", colors[i].B);
        printf("\n");
    }
}

//Prototipação dos módulos
int main(){
    Color* colors;
    colors = alocaMemoriaVetorColors(N * M);
    
    carregaVetorColors(colors, (N * M));
    escreveVetorColors(colors, (N * M));
    
    liberaMemoriaVetor(colors);
    return 0;
}

