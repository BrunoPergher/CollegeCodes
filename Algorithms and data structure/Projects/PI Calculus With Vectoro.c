#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct{
    double x;
    double y;
}ponto;

//Prototipação
double calculaPi(int);
int selecionaQuantidade();
void imprimePi(int);
void apresentaInterface();
double replicaCalculo(int);
ponto* gerarPonto(double, double);

int main(void)
{
    apresentaInterface();
    int n = selecionaQuantidade();
    imprimePi(n);
    return 0;
}

double replicaCalculo(int n){
    double replica[10];
    double totalPi;
    int i;

    for( i = 0; i < 10; i++)
    {
        replica[i] = calculaPi(n);
        totalPi += replica[i];
    }

    return totalPi / 10;
}

void apresentaInterface(){
    printf("=============================================================\n");
    printf(" Descubra o valor de PI segundo o método de Monte Carlo\n");
    printf("=============================================================\n");
}

//valida pontos dentro do circuo e calcula o valor aproximado de PI
double calculaPi(int n)
{
    int i, insideCircle = 0;
    ponto *pp;
    //double x, y;
    double n1;
    double n2;

    srand(time(NULL));
   
    for (i = 0; i < n; i++)
    {
        n1 = (double)rand() / RAND_MAX * 2.0 - 1.0;
        n2 = (double)rand() / RAND_MAX * 2.0 - 1.0;
        pp = gerarPonto(n1, n2);

        if (pp -> x * pp -> x + pp -> y * pp -> y <= 1)
        {
            insideCircle++;
        }
        free(pp);
    }
    return (double)4 * insideCircle / n;
}

//Quantos pontos serão criados para fazer a validação e calculo
int selecionaQuantidade()
{
    int n;
    printf("\nEscolha a quantidade de pontos aleatorios a serem gerados(Quanto mais, mais aproximado vai ser o resultado)\n");
    scanf("%d", &n);

    return n;
}

//Imprime PI
void imprimePi(int n)
{
    double pi = replicaCalculo(n);
    printf("\n%lf", pi);
}

//aloca a memoria e define os valores de x e y utilizando ponteiros
ponto* gerarPonto(double n1, double n2){
    ponto *pp;
    pp = malloc(sizeof(ponto));
    pp -> x = n1; //se criar o numero aleatório nesse método, o programa não funciona como deveria.
    pp -> y = n2;

    return pp;
}