#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct station{
	char name[256];
	char rapid;
	struct station *next;
};

struct station *read_list(FILE *fp) {
	struct station *new, *prev, *result;
	struct station tmp;
	char tentative;
	new = (struct station *)malloc(sizeof(struct station));
	fscanf (fp, "%[^,],%c%c", new->name, &new->rapid, &tentative); //%[^,]　csvファイルの文字列を読みこむとき必要
	prev = new;
	result = new;

	while ((fscanf (fp, "%[^,],%c%c", tmp.name, &tmp.rapid, &tentative)) != EOF) {
		new = (struct station *)malloc(sizeof(struct station));
		*new = tmp;
		prev->next = new;
		prev = new;
	}

	prev->next = NULL;
	return (result);
}

void show_station(struct station *sp) {
	while(sp != NULL) {
		printf("%s, 快速停車駅かどうか = %c\n", sp->name, sp->rapid);
		sp = sp->next;
	}
}

struct station *delete_station(struct station *sp) {
	char query_name[256];
	struct station *process1, *process2;
	printf("削除する駅の名前を入力してください: ");
	scanf ("%s", query_name);
	process1 = sp;

	while(process1 != NULL) {
		if(strcmp(process1->name, query_name) != 0) {
			process2 = process1;
			process1 = process1->next;
		}
		else
			break;
	}

	printf("%s駅を削除\n", query_name);

	if (process1 == NULL) {
		printf("%s駅が見つかりませんでした\n", query_name);
		return sp;
	} else if (process1 == sp) {
		printf("%s \n", process1->name);
		sp = process1->next;
	} else {
		sp->next = process1->next;
	}

	return sp;
}

struct station *add_station(struct station *sp) {
	char query_name[256];
	struct station *new, *process1;
	printf("どの駅の後ろに追加しますか?\n");
	printf("先頭に駅を追加する場合は first を入力してください\n");
	scanf ("%s", query_name);

	if (strcmp(query_name, "first") == 0) {
		printf("%s駅の前に追加\n", sp->name);
		new = (struct station *)malloc(sizeof(struct station));
		printf("新しい駅の名前を入力してください: ");
		scanf ("%s%*c", new->name);
		printf("快速は停車しますか? = [Y/N] ");
		scanf ("%c", &new->rapid);
		new->next = sp;
		return new;
	} else {
		process1 = sp;
		while (process1 != NULL) {
			if(strcmp(process1->name, query_name) == 0)
				break;
			else
				process1 = process1->next;
		}
		if (process1 == NULL)
			printf("%s駅は見つかりませんでした\n", query_name);
		else {
			printf("%s駅と%s駅の間に追加します\n", process1->name, (process1->next)->name);
			new = (struct station *)malloc(sizeof(struct station));
			printf("新しい駅の名前を入力してください: ");
			scanf ("%s%*c", new->name);
			printf("快速は停車しますか? = [Y/N] ");
			scanf ("%c", &new->rapid);
			new->next = process1->next;
			process1->next = new;
		}
	}
	return sp;
}

int main() {
	FILE *fp;
	struct station *line=NULL;
	int trigger;

	if((fp = fopen("stationlist.csv", "r")) == NULL) {
		printf("stationlist.csvは開けません\n");
		exit(EXIT_FAILURE);
	}

	line = read_list(fp);
	fclose(fp);
	show_station(line);

	for(;;) {
		printf("---------------------\n");
		printf(" 駅を追加するには1を入力してください\n 駅を削除するには2を入力してください\n 駅リストを表示するには3を入力してください\n 終了するには4を入力してください\n");
		scanf("%d", &trigger);
		switch(trigger) {
			case 1:
			printf("駅の追加\n");
			line = add_station(line);
			break;
			case 2:
			printf("駅の削除\n");
			line = delete_station(line);
			break;
			case 3:
			show_station(line);
			break;
			case 4:
			printf("プログラムの終了\n");
			if((fp = fopen("stationlist-result.csv", "w")) == NULL) {
				printf("stationlist-result.csvは開けません\n");
				exit(EXIT_FAILURE);
			}
			while (line != NULL) {
				fprintf(fp, "%s, %c\n", line->name, line->rapid);
				line = line->next;
			}
			fclose(fp);
			return 0;
			default:
			printf("1から4の数字を入力してください\n");
			break;
		}
	}
	return 0;
}