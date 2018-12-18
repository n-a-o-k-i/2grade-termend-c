#include <stdio.h>

int main(void){
  int a = 0;
  int b = 0;

  do {
  	++a;
  	if(1 < a){
  		if (a == 2){
  			b += 2;
  			printf("%d\n", b);
  		}else if(a == 3){
  			b += 1;
  			printf("%d\n", b);
  		}else {
  			b -= 1;
  			printf("%d\n", b);
  		}
   	}else{
   		b = a;
   		printf("%d\n", b);
   	}
  }while(a < 5);
  
  return 0;
}