#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>  
#include <time.h>
#define M 8
#define N 8
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

typedef struct Jogador
{
  int num;
  char nome;
  int m;
  int n;
  char time;
  bool bola;
  bool existe;
} Jogador;

Jogador** alocaMatriz(int, int);
void carregaMatriz(Jogador**, int, int);
Jogador criarJogadorNulo();
Jogador criaJogador(int, char, int, int, char, bool);
void imprimeQuadra(Jogador**, int, int);
char insereJogadores(Jogador**);
void insereJogadorQuadra(Jogador, Jogador**);
Jogador encontraJogador(Jogador**, int, int, int, char);
Jogador selecionarJogador(Jogador**, int, int, char);
bool acoesJogador(Jogador**, int, int, Jogador);
int numeroAleatorio(int);
void game(Jogador**, int, int);
void moverJogador(Jogador**, int, int, Jogador);
Jogador encontrarInimigoProximo(Jogador**, Jogador);
bool passarBola(Jogador**, int, int, Jogador);
bool chutarBola(Jogador**, int, int, Jogador);
Jogador jogadorInimigoMesmaLinha(Jogador**, Jogador);
void transferirBolaOutroTime(Jogador**, Jogador, int, int); 

int main() {
  srand(time(NULL));

  printf("\n \nBem vindos ao " MAG "Futsal por Turnos \n \n" RESET);
  printf(RED "Regras de Funcionamento: \n \n" RESET);
  printf(MAG "1- " RESET "Cada time pode fazer uma ação por turno \n");
  printf(MAG "2- " RESET "Estar mais perto do gol, ou não ter nenhum jogador na \n    frente aumenta as chances de marcar um gol \n");
  printf(MAG "3- " RESET "O jogo acaba quando o time marcar 3 gols! \n \n \n");
  Jogador **quadra = alocaMatriz(M, N);
  carregaMatriz(quadra, M, N);
  game(quadra, M, N);
  return 0;
}

Jogador selecionarJogador(Jogador** quadra, int m, int n, char time) {
  int num;
  bool encontrou = false;
  Jogador j;

  while (encontrou == false) {
    scanf("%d", &num);

    j = encontraJogador(quadra, m, n, num, time);

    if (j.existe == false) {

      printf(RED "Jogador com número informado nao encontrado, insira novamente: \n" RESET);

    } else {

      encontrou = true;

    }
  }
  return j;
}

Jogador encontrarInimigoProximo(Jogador** quadra, Jogador jogador){
  int m = jogador.m;
  int n = jogador.n;
  char time = jogador.time;

  Jogador j1 = quadra[m-1][n-1];
  if(j1.existe == true && j1.time != time){
    return j1;
  }

  Jogador j2 = quadra[m-1][n];
  if(j2.existe == true && j2.time != time){
    return j2;
  }

  Jogador j3 = quadra[m-1][n+1];
  if(j3.existe == true && j3.time != time){
    return j3;
  }

  Jogador j4 = quadra[m][n+1];
  if(j4.existe == true && j4.time != time){
    return j4;
  }

  Jogador j5 = quadra[m+1][n+1];
  if(j5.existe == true && j5.time != time){
    return j5;
  }

  Jogador j6 = quadra[m+1][n];
  if(j6.existe == true && j6.time != time){
    return j6;
  }

  Jogador j7 = quadra[m+1][n-1];
  if(j7.existe == true && j7.time != time){
    return j7;
  }

  Jogador j8 = quadra[m][n-1];
  if(j8.existe == true && j8.time != time){
    return j8;
  }

  return criarJogadorNulo();
}

bool passarBola(Jogador** quadra, int m, int n, Jogador j) {
  printf("Informe o numero do jogador que deseja passar a bola: ");
  Jogador alvo = selecionarJogador(quadra, m, n, j.time);

  Jogador inimigoExiste = encontrarInimigoProximo(quadra, alvo);

  if (inimigoExiste.existe == true) {

    int random = numeroAleatorio(10);

    if(random > 5){
      printf(RED "Você passou a bola, mas o jogador inimigo %d estava perto e a roubou! \n" RESET, j.num);
      quadra[j.m][j.n].bola = false;
      quadra[inimigoExiste.m][inimigoExiste.n].bola = true;
    } else {
      printf(CYN "Você passou a bola para o jogador %d \n" RESET, alvo.num);
      quadra[j.m][j.n].bola = false;
      quadra[alvo.m][alvo.n].bola = true;
    }
  }else{
    printf(CYN "Você passou a bola para o jogador %d \n" RESET, alvo.num);
    quadra[j.m][j.n].bola = false;
    quadra[alvo.m][alvo.n].bola = true;
  }
}

Jogador jogadorInimigoMesmaLinha(Jogador** quadra, Jogador j) {
  int i;
  char time = j.time;

  if (time == 'a') {
    for (i = j.n; i < 8; i++) {
      if (quadra[j.m][i].existe == true && quadra[j.m][i].time != 'a') {
        return quadra[j.m][i];
        break;
      }
    }
  } else {
    for (i = j.n; i >= 0; i--) {
      if (quadra[j.m][i].existe == true && quadra[j.m][i].time != 'b') {
        return quadra[j.m][i];
        break;
      }
    }
  }
  return criarJogadorNulo();
}

bool chutarBola(Jogador** quadra, int m, int n, Jogador j) {
  char time = j.time;
  int x = j.n, y = j.m;
  int distanciaGolX = 0, distanciaGolY = 0;
  int dificuldade = 0;

  if (time == 'a') {
    distanciaGolX = 7 - x;
    if (y >= 3) {
      distanciaGolY = y - 3;
    } else {
      distanciaGolY = 3 - y;
    }
  } else {
    distanciaGolX = x;
    if (y >= 3) {
      distanciaGolY = y - 3;
    } else {
      distanciaGolY = 3 - y;
    }
  }

  dificuldade = distanciaGolX + distanciaGolY;
  Jogador inimigo = jogadorInimigoMesmaLinha(quadra, j);

  int random = numeroAleatorio(10);

  if (inimigo.existe == true) {
    dificuldade += 2;
    if (random >= dificuldade) {
      if (j.time == 'a') {
        printf(RED "O TIME VERMELHO MARCOU UM GOL! \n" RESET); 
        transferirBolaOutroTime(quadra, j, m, n);
      } else {
        printf(BLU "O TIME AZUL MARCOU UM GOL! \n" RESET); 
        transferirBolaOutroTime(quadra, j, m, n);
      }
      return true;
    } else {
      printf(RED "Você chutou a bola, mas ela foi interceptada pelo outro time! \n" RESET); 
      quadra[j.m][j.n].bola = false;
      quadra[inimigo.m][inimigo.n].bola = true;
      return false;
    }
  } else {
    if (random >= dificuldade) {
      if (j.time == 'a') {
        printf(RED "O TIME VERMELHO MARCOU UM GOL! \n" RESET); 
        transferirBolaOutroTime(quadra, j, m, n);
      } else {
        printf(BLU "O TIME AZUL MARCOU UM GOL! \n" RESET); 
        transferirBolaOutroTime(quadra, j, m, n);
      }
      return true;
    } else {
      printf(RED "Você chutou a bola mas errou o gol! \n" RESET);
      transferirBolaOutroTime(quadra, j, m, n);
      return false;
    }
  } 
}

void transferirBolaOutroTime(Jogador** quadra, Jogador origem, int m, int n) {
  char time;
  if (origem.time == 'a') {
    printf("Time " BLU "azul" RESET " seleciona qual jogador vai sair com a bola! \n");
    time = 'b';
  } else {
    printf("Time " RED "vermelho" RESET " seleciona qual jogador vai sair com a bola! \n");
    time = 'a';
  }
  printf("Por favor insira o número do jogador a receber a bola:  ");
  Jogador j = selecionarJogador(quadra, m, n, time);
  quadra[j.m][j.n].bola = true;
  quadra[origem.m][origem.n].bola = false;
}

void moverJogador(Jogador** quadra, int m, int n, Jogador j) {
  int mOriginal = j.m;
  int nOriginal = j.n;
  int novoM, novoN;
  bool posicaoValida = false;

  while (posicaoValida == false) {

    bool mValido = false, nValido = false;

    while(mValido == false) {

      printf("Informe o número da" MAG " linha " RESET "que deseja posicionar o jogador:  ");
      scanf("%d", &novoM);

      if (novoM >= 0 || novoM < 8){
        mValido = true;
        break;
      } else {
        printf(RED "Numero de linha não existe!" RESET);
      }
    }
    while (nValido == false) {
      printf("Informe o número da" MAG " coluna " RESET "que deseja posicionar o jogador:  ");
      scanf("%d", &novoN);

      if (novoN >= 0 || novoN < 8){
        nValido = true;
        break;
      } else {
        printf(RED "Número de coluna não existe!" RESET);
      }
    }
    if ((novoM == 3 || novoM == 4) && (novoN == 0 || novoN == 7)){
      printf(RED "Você não pode colocar um jogador na posição do gol! \n" RESET);
    } else {
      if(quadra[novoM][novoN].existe == false) {
      posicaoValida = true;
      }else{
        printf(RED "Já existe um jogador nesta casa! \n" RESET);
      }
    }
  }
  Jogador nulo = criarJogadorNulo();
  quadra[novoM][novoN] = j;
  quadra[novoM][novoN].m = novoM;
  quadra[novoM][novoN].n = novoN;
  quadra[mOriginal][nOriginal] = nulo;
}

bool acoesJogador(Jogador** quadra, int m, int n, Jogador j){
  bool opcaoValida = false;
  int op;
  while(opcaoValida == false) {
    op = 0;

    printf("Seleciona a ação que deseja realizar: \n");
    printf(MAG "1- " RESET "Mover Jogador \n");
    printf(MAG "2- " RESET "Passar Bola \n");
    printf(MAG "3- " RESET "Chutar ao gol \n");

    scanf("%d", &op);

    if ((op == 2 || op == 3) && j.bola == false) {
      printf(RED "O jogador selecionado não está com a bola \n" RESET);
    } else {
      if (op > 0 && op < 4) {
        opcaoValida = true;
      } else {
        printf(RED "Opção Inválida \n" RESET);
      }
    }
  }
  bool gol = false;
  switch(op){
    case 1:
      moverJogador(quadra, m, n, j);
      gol = false;
      break;
    case 2:
      passarBola(quadra, m, n, j);
      break;
    case 3:
      gol = chutarBola(quadra, m, n, j);
      break;
    default:
      printf(RED "Opção Inválida! \n" RESET);
  }
  return gol;
}
void game(Jogador** quadra, int m, int n) {
  bool match = false;
  char timeInicial = insereJogadores(quadra);
  int a = 0, b = 0, rodadas = 0;

  if (timeInicial == 'a') {
    while(match == false) {
      printf("\n \nPLACAR:" RED " %d " RESET "X" BLU " %d \n \n" RESET, a, b);
      imprimeQuadra(quadra, m, n);
      printf("Vez do time" RED " vermelho" RESET " jogar! \n");
      printf("Informe o numero do jogador que deseja selecionar: ");
      Jogador j = selecionarJogador(quadra, m, n, 'a');
      bool fezGol = acoesJogador(quadra, m, n, j);

      if (fezGol == true) {
        a++;
        if (a > 2) {
          printf(RED "\n \nO time vermelho ganhou o jogo! \n" RESET);
          match = false;
          break;
        }
      }
      printf("\n \nPLACAR:" RED " %d " RESET "X" BLU " %d \n \n" RESET, a, b);
      imprimeQuadra(quadra, m, n);
      printf("Vez do time" BLU " azul" RESET " jogar! \n");
      printf("Informe o numero do jogador que deseja selecionar: ");

      j = selecionarJogador(quadra, m, n, 'b');
      fezGol = acoesJogador(quadra, m, n, j);

      if (fezGol == true) {
        b++;
        if (b > 2) {
          printf(BLU "\n \nO time azul ganhou o jogo! \n" RESET);
          match = false;
          break;
        }
      }

      rodadas++;
    } 
  }else{
    while (match == false) {
      printf("PLACAR:" RED " %d " RESET "X" BLU " %d \n \n" RESET, a, b);
      imprimeQuadra(quadra, m, n);
      printf("Vez do time" BLU " azul" RESET " jogar! \n");
      printf("Informe o numero do jogador que deseja selecionar: ");
      Jogador j = selecionarJogador(quadra, m, n, 'b');
      bool fezGol = acoesJogador(quadra, m, n, j);

      if (fezGol == true) {
        b++;
        if (b > 2) {
          printf(BLU "\n \nO time azul ganhou o jogo! \n" RESET);
          match = false;
          break;
        }
      }
      printf("\n \nPLACAR:" RED " %d " RESET "X" BLU " %d \n \n" RESET, a, b);
      imprimeQuadra(quadra, m, n);
      printf("Vez do time" RED " vermelho" RESET " jogar! \n");
      printf("Informe o numero do jogador que deseja selecionar: ");

      j = selecionarJogador(quadra, m, n, 'a');
      fezGol = acoesJogador(quadra, m, n, j);

      if (fezGol == true) {
        a++;
        if (a > 2) {
          printf(RED "\n \nO time vermelho ganhou o jogo! \n" RESET);
          match = false;
          break;
        }
      }
      rodadas++;
    } 
  }
  printf("O jogo acabou em "MAG"%d rodadas! \n \n " RESET, rodadas);
}
Jogador** alocaMatriz(int m, int n) {
  Jogador **mat;
  int i;
  mat = (Jogador **)malloc(sizeof(Jogador*) * m);

  if(mat == NULL){
    printf("Memoria insuficiente.\n");
    exit(1);
  }

  for(i=0; i< n; i++) {
    mat[i] = (Jogador*)malloc(sizeof(Jogador) * n);
    if(mat[i] == NULL){
      printf("Memoria insuficiente.\n");
      exit(1);
    }
  }
  return mat;
}

Jogador encontraJogador(Jogador** mat, int m, int n, int num, char time) {
  int i, j;
  Jogador jogador;
  jogador.existe = false;

  for (i=0; i<m; i++) {
    for (j=0; j<n; j++) {
      if (mat[i][j].num == num && mat[i][j].time == time) {
        jogador = mat[i][j];
        break;
      }
    }
  }
  return jogador;
}

void imprimeQuadra(Jogador** mat, int m, int n) {
  int i, j;
  printf("       ");
  for(i=0; i<m; i++){
    printf("%d      ", i);
  }
  printf("\n");
  for(i=0; i<m; i++){
    for(j=0; j<n; j++){
      if(j == 0) {
        printf("%d   ", i);
      }
      if(((i==4 || i==3) && (j==0 || j==7))) {
        printf("[ 🥅  ]");
      }
      else {
        if(mat[i][j].existe) {
          if(mat[i][j].time == 'a'){
            if(mat[i][j].bola){
              printf(RED "[ %d⚽ ]" RESET, mat[i][j].num);
            }else{
              printf(RED "[  %d  ]" RESET, mat[i][j].num);
            }
          }else{
            if(mat[i][j].bola){
              printf(BLU "[ %d⚽ ]" RESET, mat[i][j].num);
            }else{
              printf(BLU "[  %d  ]" RESET, mat[i][j].num);
            }
          }
        }
        else{
          printf("[     ]");
        }
      }
    }
    printf("\n");
  }
}

int numeroAleatorio(int max) {
  return rand() % max;
}

Jogador criaJogador(int num, char nome, int m, int n, char time, bool bola){
  Jogador j;
  j.bola = bola;
  j.existe = true;
  j.m = m;
  j.n = n;
  j.nome = nome;
  j.num = num;
  j.time = time;
  return j;
}

Jogador criarJogadorNulo() {
  Jogador jogador;
  jogador.existe = false;
  return jogador;
}

void carregaMatriz(Jogador** mat, int m, int n) {
  int i, j;
  Jogador jogador = criarJogadorNulo();
  for(i=0; i<m; i++){
    for(j=0; j<n; j++){
      mat[i][j] = jogador;
    }
  }
}

void insereJogadorQuadra(Jogador j, Jogador** quadra) {
  quadra[j.m][j.n] = j;
}

char insereJogadores(Jogador** quadra) {
  Jogador j2;
  Jogador j6;
  int random = numeroAleatorio(10);
  printf("Sorteando quem irá começar com a bola..... \n");
  printf("A bola irá começar com o time ");
  char time;
  if (random > 4) {
    printf(RED "vermelho" RESET "\n");
    j2 = criaJogador(2, '2', 2, 2, 'a', true);
    j6 = criaJogador(2, '2', 2, 5, 'b', false);
    time = 'a';
  }else {
    printf(BLU "azul" RESET "\n");
    j2 = criaJogador(2, '2', 2, 2, 'a', false);
    j6 = criaJogador(2, '2', 2, 5, 'b', true);
    time = 'b';
  }
  Jogador j1 = criaJogador(1, '1', 1, 1, 'a', false);
  
  Jogador j3 = criaJogador(3, '3', 6, 1, 'a', false);
  Jogador j4 = criaJogador(4, '4', 5, 2, 'a', false);
  

  Jogador j5 = criaJogador(1, '1', 1, 6, 'b', false);
  
  Jogador j7 = criaJogador(3, '3', 6, 6, 'b', false);
  Jogador j8 = criaJogador(4, '4', 5, 5, 'b', false);
  insereJogadorQuadra(j8, quadra);
  insereJogadorQuadra(j7, quadra);
  insereJogadorQuadra(j6, quadra);
  insereJogadorQuadra(j5, quadra);
  insereJogadorQuadra(j4, quadra);
  insereJogadorQuadra(j3, quadra);
  insereJogadorQuadra(j2, quadra);
  insereJogadorQuadra(j1, quadra);
  return time;
}