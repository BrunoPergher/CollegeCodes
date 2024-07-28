/******************************************************************************
Uma determinada biblioteca possui obras de ciências exatas, ciências humanas e ciências biomédicas, totalizando 1.500 volumes, 500 de cada área.
O proprietário resolveu informatiza-la e, para tal, agrupou as informações sobre cada livro do seguinte modo:

Código de catalogação:__________________________ Doado(Sim/Não):_______________
Nome da obra: _____________________________________________________________
Nome do autor: _____________________________________________________________
Editora: _____________________________ Nº. De Páginas: ________________________

Construa um algoritmo que declare tal estrutura e que reúna todas as informações de todas as obras em três vetores distintos para cada área;
Elabore um trecho de algoritmo que, utilizando como premissa o que foi feito no item a, realize uma consulta às informações. O usuário fornecerá código da obra e sua área; existindo tal livro, informa seus campos; do contrário, envia mensagem de aviso. A consulta repete-se até que o usuário introduza código finalizador com o valor -1; ok
Idem ao item b, porém o usuário simplesmente informa o nome e a área do livro e deseja consultar; ok
Escreva um trecho de algoritmo que liste todas as obras de cada área que representem livros doados; ok
Idem ao item d, porém, obras cujos livros sejam comprados e cujo número de páginas se encontre entre 100 e 300; ok
Elabore um trecho de algoritmo que faça a alteração de um registro; para tal, o usuário fornece o código, a área e as demais informações sobre o livro;
Construa um trecho de algoritmo que efetue a exclusão de algum livro; o usuário fornecerá o código e a área. Lembre-se de que somente pode ser excluído um livro existente

*******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TAM 1

typedef struct sLivros
{
    char autor[50];
    char editora[50];
    char nome[50];
    int pags;
    int cod;
    int ehDoado;
} Livro;

Livro carregaLivro();     
void escreveLivro(Livro); 
//Protótipos do Model
void carregaVetorHumanas(Livro[]);
void carregaVetorBiomedicas(Livro[]);
void carregaVetorExatas(Livro[]);
void escreveVetorExatas(Livro[]);
void escreveVetorHumanas(Livro[]);
void escreveVetorBiomedicas(Livro[]);

void carregaVetorExatas(Livro exatas[])
{
    int i;
    for (i = 0; i < TAM; i++)
    {
        exatas[i] = carregaLivro();
    }
}

void carregaVetorHumanas(Livro humanas[])
{
    int i;
    for (i = 0; i < TAM; i++)
    {
        humanas[i] = carregaLivro();
    }
}

void carregaVetorBiomedicas(Livro biomedicas[])
{
    int i;
    for (i = 0; i < TAM; i++)
    {
        biomedicas[i] = carregaLivro();
    }
}

/*
void carregaVetorLivros(Livro livros[]){
  int i;
  for (i = 0; i < TAM; i++){
    livros[i] = carregaLivro();
  }
}*/

Livro carregaLivro()
{
    Livro l;
    printf("Digite o Nome do livro: ");
    scanf("%s", l.nome);
    printf("Digite o autor do livro: ");
    scanf("%s", l.autor);
    printf("Digite a editora do livro: ");
    scanf("%s", l.editora);
    printf("Digite o codigo do livro(Ordem Crescente começando no 0):");
    scanf("%i", &l.cod);
    printf("O livro é doado?(1 - sim, 2 - não)");
    scanf("%i", &l.ehDoado);
    printf("Digite a quantidade de paginas do livro: ");
    scanf("%i", &l.pags);
    return l;
}

void escreveVetorExatas(Livro exatas[])
{
    int i;
    for (i = 0; i < TAM; i++)
    {
        escreveLivro(exatas[i]);
    }
}

void escreveVetorHumanas(Livro humanas[])
{
    int i;
    for (i = 0; i < TAM; i++)
    {
        escreveLivro(humanas[i]);
    }
}

void escreveVetorBiomedicas(Livro biomedicas[])
{
    int i;
    for (i = 0; i < TAM; i++)
    {
        escreveLivro(biomedicas[i]);
    }
}

/*void escreveVetorLivros(Livro livros[]){
  int i;
  for (i = 0; i < TAM; i++){
    escreveLivro(livros[i]);
  }
}*/

void escreveLivro(Livro l)
{
    printf("\tNome do livro: %s\n", l.nome);
    printf("\tCodigo: %i\n", l.cod);
    printf("\tEditora: %s\n", l.editora);
    printf("\tAutor: %s\n", l.autor);
    printf("\tQuantidade de paginas: %i\n", l.pags);
    if (l.ehDoado == 1)
    {
        printf("\tDoado: sim\n");
    }
    else if (l.ehDoado == 2)
    {
        printf("\tNão é doado\n");
    }
    else
    {
        printf("\tsem informações\n");
    }
}

void listarDoadosExatas(Livro exatas[]){
  int i;
  printf("Livros da Categoria que foram doados:\n");
  for(i = 0;i < TAM; i++){
    if(exatas[i].ehDoado==1){
      escreveLivro(exatas[i]);
    } 
  }
  printf("\n");
}

void listarDoadosHumanas(Livro humanas[]){
  int i;
  printf("Livros da Categoria que foram doados:\n");
  for(i = 0;i < TAM; i++){
    if(humanas[i].ehDoado==1){
      escreveLivro(humanas[i]);
    } 
  }
  printf("\n");
}

void listarDoadosBiomedicas(Livro biomedicas[]){
  int i;
  printf("Livros da Categoria que foram doados:\n");
  for(i = 0;i < TAM; i++){
    if(biomedicas[i].ehDoado==1){
      escreveLivro(biomedicas[i]);
    } 
  }
  printf("\n");
}

void exatasComprados100a300(Livro exatas[]){
  int i;
  printf("Livros da Categoria que foram comprados e possuiem de 100 a 300 paginas:\n");
  for(i = 0;i < TAM; i++){
    if(exatas[i].ehDoado==2){
      if(exatas[i].pags > 99 && exatas[i].pags < 301 ){
      escreveLivro(exatas[i]);
      }
    } 
  }
  printf("\n");
}

void humanasComprados100a300(Livro humanas[]){
  int i;
  printf("Livros da Categoria que foram comprados e possuiem de 100 a 300 paginas:\n");
  for(i = 0;i < TAM; i++){
    if(humanas[i].ehDoado==2){
      if(humanas[i].pags > 99 && humanas[i].pags < 301 ){
      escreveLivro(humanas[i]);
      }
    } 
  }
  printf("\n");
}

void biomedicasComprados100a300(Livro biomedicas[]){
  int i;
  printf("Livros da Categoria que foram comprados e possuiem de 100 a 300 paginas:\n");
  for(i = 0;i < TAM; i++){
    if(biomedicas[i].ehDoado==2){
      if(biomedicas[i].pags > 99 && biomedicas[i].pags < 301 ){
      escreveLivro(biomedicas[i]);
      }
    } 
  }
  printf("\n");
}


int main(void)
{
    Livro exatas[TAM], biomedicas[TAM], humanas[TAM];

    int menu, subMenu, i, op;

    do
    {

        printf("O que vc deseja fazer? \n");
        printf("1 - Adicionar livro. \n");
        printf("2 - Ver Livros. \n");
        printf("3 - Alterar Livros. \n");
        printf("4 - Excluir livro. \n");
        printf("-1 - Sair. \n");
        scanf("%d", &menu);

        switch (menu)
        {
        case 1:
            printf("Você quer adicionar um livro de:\n");
            printf("1 - Exatas. \n");
            printf("2 - Humanas. \n");
            printf("3 - Biomedicas. \n");
            scanf("%d", &subMenu);

            switch (subMenu)
            {
            case 1:
                carregaVetorExatas(exatas);
                break;

            case 2:
                carregaVetorHumanas(humanas);
                break;

            case 3:
                carregaVetorBiomedicas(biomedicas);
                break;
            }
            break;

        case 2:
            printf("Você quer Ver um livro de:\n");
            printf("1 - Exatas. \n");
            printf("2 - Humanas. \n");
            printf("3 - Biomedicas. \n");
            scanf("%d", &subMenu);
            switch (subMenu)
            {
            case 1:
                printf("1 - Todos os livros \n");
                printf("2 - Pesquisar por codigo \n");
                printf("3- Todos os Livros Doados \n");
                printf("4- Todos os Livros Comprados de 100 a 300 paginas ");
                scanf("%d", &menu);
                if (menu == 1)
                {
                    escreveVetorExatas(exatas);
                }
                else if (menu == 2)
                {
                    int i;
                    printf("Qual o Codigo:\n");
                    scanf("%d", &i);
                    escreveLivro(exatas[i]);
                }
                else if(menu == 3){
                  listarDoadosExatas(exatas);
                }
                else if(menu == 4){
                  exatasComprados100a300(exatas);
                }
                else
                {
                    printf("opção invalida");
                }
                break;

            case 2:
                printf("1 - Todos os livros \n");
                printf("2 - Pesquisar por codigo \n");
                printf("3- Todos os Livros Doados \n");
                printf("4- Todos os Livros Comprados de 100 a 300 paginas ");
                scanf("%d", &menu);
                if (menu == 1)
                {
                    escreveVetorHumanas(humanas);
                }
                else if (menu == 2)
                {
                    int i;
                    printf("Qual o Codigo:\n");
                    scanf("%d", &i);
                    escreveLivro(humanas[i]);
                }
                else if(menu == 3){
                  listarDoadosHumanas(humanas);
                }
                else if(menu == 4){
                  humanasComprados100a300(humanas);
                }
                else
                {
                    printf("opção invalida");
                }

                break;

            case 3:
                printf("1 - Todos os livros \n");
                printf("2 - Pesquisar por codigo \n");
                printf("3- Todos os Livros Doados \n");
                printf("4- Todos os Livros Comprados de 100 a 300 paginas ");
                scanf("%d", &menu);
                if (menu == 1)
                {
                    escreveVetorBiomedicas(biomedicas);
                }
                else if (menu == 2)
                {
                    int i;
                    printf("Qual o Codigo:\n");
                    scanf("%d", &i);
                    escreveLivro(biomedicas[i]);
                }
                else if(menu == 3){
                  listarDoadosBiomedicas(biomedicas);
                }
                else if(menu == 4){
                  biomedicasComprados100a300(biomedicas);
                }
                else
                {
                    printf("opção invalida");
                }
                break;
            }  
        case 3:
            printf("De que categoria você deseja alterar?\n");
            printf("1 - Exatas. \n");
            printf("2 - Humanas. \n");
            printf("3 - Biomedicas. \n");
            scanf("%d", &subMenu);
            switch(subMenu){
              case 1:
              printf("Qual o Codigo do livro a ser Alterado?");
              scanf("%d", &i);

              printf("Livro a ser mudado \n \n");
              escreveLivro(exatas[i]);

              printf("\n \n Novas Informações \n \n");
              exatas[i] = carregaLivro();

              break;

              case 2:
              printf("Qual o Codigo do livro a ser Alterado?");
              scanf("%d", &i);

              printf("Livro a ser mudado \n \n");
              escreveLivro(humanas[i]);

              printf("\n \n Novas Informações \n \n");
              humanas[i] = carregaLivro();

              break;

              case 3:
              printf("Qual o Codigo do livro a ser Alterado?");
              scanf("%d", &i);

              printf("Livro a ser mudado \n \n");
              escreveLivro(biomedicas[i]);

              printf("\n \n Novas Informações \n \n");
              biomedicas[i] = carregaLivro();

              break;
            }
          break;
      
        case 4:
          printf("de que categoria você deseja excluir?\n");
            printf("1 - Exatas. \n");
            printf("2 - Humanas. \n");
            printf("3 - Biomedicas. \n");
            scanf("%d", &subMenu);

            switch(subMenu){
              case 1: 
                printf("Qual o Codigo do livro a ser Excluido?");
                scanf("%d", &i);
              
                printf("Livro a ser excluido \n \n");
                escreveLivro(exatas[i]);

                printf("Deseja realmente exlui-lo? \n");
                printf("1 - sim\n");
                printf("2 - não\n");
                scanf("%d", &op);

                if(op == 1){
                  exatas[i] = exatas[i-501];
                }
                break;
                
                case 2: 
                printf("Qual o Codigo do livro a ser Excluido?");
                scanf("%d", &i);
              
                printf("Livro a ser excluido \n \n");
                escreveLivro(humanas[i]);

                printf("Deseja realmente exlui-lo? \n");
                printf("1 - sim\n");
                printf("2 - não\n");
                scanf("%d", &op);

                if(op == 1){
                  humanas[i] = humanas[i-501];
                }
                break;
                
                case 3: 
                printf("Qual o Codigo do livro a ser Excluido?");
                scanf("%d", &i);
              
                printf("Livro a ser excluido \n \n");
                escreveLivro(biomedicas[i]);

                printf("Deseja realmente exlui-lo? \n");
                printf("1 - sim\n");
                printf("2 - não\n");
                scanf("%d", &op);

                if(op == 1){
                  biomedicas[i] = biomedicas[i-501];     
                }
                break;
            }
        }
    } while (menu != -1);
}
