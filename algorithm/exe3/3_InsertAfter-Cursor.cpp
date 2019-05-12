// 最小限の機能のみ(削除機能とかはない)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define Null -1
#define LIST_SIZE 1024
typedef int Index;

// 各種構造体の定義(教科書P.356に準拠)
typedef struct {
	int no;
	char name[20];
}Member;

typedef struct {
	Member data;
	Index next;
	Index Dnext;
}Node;

typedef struct {
	Node* n;
	Index head;
	Index max;
	Index deleated;
	Index crnt;
}List;

// Listの初期化関数
void InitList(List* list, int size) {
	list->n = (Node*)calloc(size, sizeof(Node));
	list->head = Null;
	list->max = Null;
	list->deleated = Null;
	list->crnt = Null;
}

// 空いているところを取得する関数
Index getIndex(List* list) {
	if (list->deleated == Null) {	// 無ければ末尾の次
		return ++list->max;
	}
	else {									// あればそこ
		list->deleated = list->n[list->deleated].Dnext;
		// フリーリストの後続ノードを入れておく
		return list->deleated;
	}
}

// 任意の位置に要素を挿入する関数
void InsertAfter(List* list, Index idx, const Member* x) {
	list->crnt = getIndex(list);
	// データを入れる
	list->n[list->crnt].data = *x;
	list->n[list->crnt].next = list->n[idx].next;
	list->n[idx].next = list->crnt;
}

// 先頭に要素を挿入する関数
// InsertAfterに統合しようとしたけどバグったのでやめた
void InsertTop(List* list, const Member* x) {
	Index ptr = list->head;
	list->crnt = getIndex(list);
	list->head = list->crnt;
	list->n[list->head].data = *x;
	list->n[list->head].next = ptr;
}

// リストを表示する関数
// 表示だけなので別にポインタ渡さなくても良い気がする
void printList(List list) {
	Index ptr = list.head;
	if (ptr == Null) {
		puts("Data Not Found.");
	}
	else {
		puts("No | Data");
		puts("---| -------------------------------");
		while (ptr != Null) {
			// 参照するメンバーデータ
			Member crtData = list.n[ptr].data;
			printf("%3d|%s \n", crtData.no, crtData.name);
			ptr = list.n[ptr].next;
		}
		puts("---| -------------------------------");
	}
}

int main() {
	List list;
	InitList(&list, LIST_SIZE);

	int order;
	while (1) {
		printf("\nPlease Input Your Order. 1:PrintData   2:AddData  3:Exit  ->");
		scanf("%d", &order);
		switch (order)
		{
		case 1: {
			printList(list);		//表示する
			break;
		}

		case 2: {
			Member Menber;
			Index ptr = list.head;
			printf("No     :"); scanf("%d", &Menber.no);
			printf("Name :"); scanf("%s", &Menber.name);
			if (ptr == Null) { // リストが空だったら先頭に
				InsertTop(&list, &Menber);
			}
			else {
				int inNo;
				printf("What number AfterInsert? (~Caution~ 0-index.):"); scanf("%d", &inNo);
				// 先頭への挿入
				if (inNo == 0) {
					InsertTop(&list, &Menber);
				}
				else {
					for (int i = 1; i < inNo; i++) {
						if (list.n[ptr].next == Null) {
							puts("Number is So big. This Data will add End of List.");
							break;
						}
						ptr = list.n[ptr].next;
					}
					InsertAfter(&list, ptr, &Menber);
				}
			}
			break;
		}

		case 3: {
			puts("Bye.");
			free(list.n);
			return 0;		// 終わらせる
		}

		default: {
			puts("This order Not Found.");
			break;
		}
		}
	}
}