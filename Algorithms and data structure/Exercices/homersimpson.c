/*
. Write a program that prints the numbers from 2 to 200. But for multiples of three print 
“Homer” instead of the number and for the multiples of five print “Simpson”.For numbers 
which are multiples of both three and five print “Homer Simpson”.
*/

#include <stdio.h>

void writeNumbers();
void verification(int);

int main(void) {
  writeNumbers();
  return 0;
}

void writeNumbers(i){
  for(int i = 2; i <= 200; i++){
    verification(i);
  }
}

void verification(i){
  if(i % 5 == 0 && i % 3 == 0 ){
    printf("Homer Simpson \n");
  }
  else if(i % 3 == 0){
      printf("Homer \n");
  }
  else if(i % 5 == 0){
      printf("Simpson \n");
  }
  else{
      printf("%d \n", i);
  };
}

