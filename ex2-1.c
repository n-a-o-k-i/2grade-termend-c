#include <stdio.h>
#include <unistd.h>

int main(void){
  int i;
  for (i=1; i<=50; i++){
    if (i%15 == 0 || ((i/10)%10 == 3 && i%5 == 0)){ //3と5の公倍数でアホ犬
      printf("%d aho-wan!\n", i);
      sleep(1); //実行結果見やすくするだけ
    } else if (i%5 == 0){ //5の倍数で犬
      printf("%d wan!\n", i);
      sleep(1); //実行結果見やすくするだけ
    } else if (i%3 == 0 || i%10 == 3 || (i/10)%10 == 3){ //3の倍数でアホ
      printf("%d aho!\n", i);
      sleep(1); //実行結果見やすくするだけ
    } else {
      printf("%d\n", i);
    }
  }
  return 0;
}