/*
10 - Escreva um algoritmo que lê uma matriz M(5,5) e calcula as somas:
da linha 4 de M.
da coluna 2 de M.
da diagonal principal.
da diagonal secundária.
de todos os elementos da matriz.
Escreva estas somas e a matriz.
*/
#include<stdio.h>
int main(){
	
	int i, x, m[5][5]; 
	for(i = 0; i <= 4; i++){ //linha
		for(x = 0; x <= 4; x++){ //coluna
	  printf("Digite um valor para matriz M: ");
	  scanf("%i", &m[i][x]);	
	    }
    }
    
	int soma;
	for(x = 0; x <= 4; x++){
		soma += m[4][x];	//Soma linha 4
	}
	
	int soma2;	
	for(i = 0; i <= 4; i++){
		soma2 += m[i][2];	//Soma coluna 2
    }
    
	int somad;	
	for(i = 0; i <= 4; i++){	
		for(x = 0; x <= 4; x++){
		    if(i == x){	
		    	somad += m[i][x];    //Diagonal principal
		    }
	    }
    }
    
	int somas = 0;
	for(i = 0; i <= 4; i++){	
		for(x = 0; x <= 4; x++){	
	    	if(i + x == 4){	
			    somas += m[i][x];	//Diagonal secundária
		    }
	    }
    }
    
	int somat;
	for(i = 0; i <= 4; i++){
		  for(x = 0; x <= 4; x++){
	      somat = somat + m[i][x]; //soma todos os valores
	  }
  }
	// a partir de agora vc pede para imprimir o q pede na questão
	printf("Soma linha 4: %i\n", soma);
	printf("Soma coluna 2: %i\n", soma2);
	printf("Soma diagonal principal: %i\n", somad);
	printf("Soma diagonal secundaria: %i\n", somas);
	printf("Soma matriz total: %i\n", somat);
}
