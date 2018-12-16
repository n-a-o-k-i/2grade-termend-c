#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct station{
  char name[100];
  char rapid;
  struct station *next; //nextっつーポインタ変数宣言
};

void showlist(struct station *sp){ //spは先頭番地
  while(sp != NULL){ //spがNULL（終点）になるまで繰り返す
    printf("station: %s,\trapid: %c\n", sp->name, sp->rapid);
    sp = sp->next; //次の駅へ
  }
}

void addstation(struct station *sp){
  struct station *new; //newっつーポインタ変数宣言
  char query_name[100]; //下で使う駅名を入れるやつ
  new = (struct station *)malloc(sizeof(struct station)); //動的メモリ確保
  printf("Insert after?: ");
  scanf ("%s", query_name);
  printf("Input name of new station: ");
  scanf ("%s", new->name);
  printf("rapid (y/n): ");
  scanf ("%*c%c", &new->rapid);
  
  //追加の作業
  while(sp != NULL){//駅名の探索
    if(strcmp(sp->name, query_name) == 0){
      new->next = sp->next; //新しい駅の次に今の駅の次の駅を代入
      sp->next = new; //今の駅を新しい駅に書き換え
      break;
    }else{
      sp = sp->next; //駅名が違ったら探索継続
    }
  }

  if(sp == NULL){//どの駅にも合致しなかったら(breakを踏まずにきたら，stop = NULL)
    printf("The station %s does not exist.\n", query_name); //入力された駅ねえよって言う
    exit(1); //異常終了
  }
}

void deletestation(struct station *sp){
  char query_name[100];
  struct station *tmp;
  tmp = sp;
  printf("Name of delete station: ");
  scanf ("%s", query_name);
  while(sp != NULL){
    if(strcmp(sp->name, query_name) != 0){//一致しなければ続ける
      tmp = sp;//今停車している駅の情報をtmpに一時保管
      sp = sp->next;
    }else{//名前が一致した場合
      break;//ループを抜ける--> tmpの中には，1つ前の駅の情報が入っている
    }
  }
  tmp->next = sp->next;//繋ぎかえ
}

int main(void){
  struct station st0, st1, st2, st3, st4, *stop;
  int flag;

  st0 = (struct station){"hachioji", 'y', &st1};
  st1 = (struct station){"katakura", 'y', &st2};
  st2 = (struct station){"aihara", 'y', &st3};
  st3 = (struct station){"hashimoto", 'y', &st4};
  st4 = (struct station){"sagamihara", 'y', NULL};
  stop = &st0;//始発の駅のポインタ（先頭番地）をstopに代入

  for(;;){//無限ループ
    printf("1: add station\n 2: delete station\n 3: list\n 4: quit\n");
    scanf ("%d", &flag);
    switch(flag){
    case 1:
      printf("=== add station ===\n");
      addstation(&st0);
      break;
    case 2:
      printf("=== delete station ===\n");
      deletestation(&st0);
      break;
    case 3:
      printf("=== show list ===\n");
      showlist(&st0);
      break;
    case 4:
      printf("=== quit ===");
      printf("save to file hogehoge\n");
      return 0;
    default:
      printf("select number 1 to 4\n");
      break;
    }
  }
/*   printf("=== before ===\n"); */
/*   showlist(stop); */

/*   //  stop = &st0; */
/*   addstation(&st0); */

/*   stop = &st0;//始発駅にstopを移動 */
/*   printf("=== after ===\n"); */
/*   showlist(stop); */

  return 0;
}