// 最小限の機能のみ(削除機能とかはない)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// 各種構造体の定義(教科書P.356に準拠)
typedef struct {
	int no;
	char name[20];
}Member;

typedef struct nod{
	Member data;
	struct nod *next;
}Node;

typedef struct {
	Node* head;
	Node* crnt;
}List;

// リスト初期化のための関数
void InitList(List* list) {
	list->head = NULL;
	list->crnt = NULL;
}

// 領域確保のための関数
Node* AllocNode(void) {
	Node* res = (Node*)calloc(1, sizeof(Node));
	return res;
}

// 任意の位置に要素を挿入する関数
void InsertAfter(List* list, Node *a, const Member* x) {
	list->crnt = AllocNode();
	list->crnt->data = *x;
	list->crnt->next = a->next;
	a->next = list->crnt;
	list->crnt = NULL;
}

// 先頭に要素を挿入する関数
// InsertAfterに統合しようとしたけどバグったのでやめた
void InsertTop(List* list, const Member* x) {
	list->crnt = AllocNode();

	Node* ptr = list->head;
	list->head = list->crnt;
	list->crnt->data = *x;
	list->crnt->next = ptr;
	list->crnt = NULL;
}

// リストを表示する関数
// 表示だけなので別にポインタ渡さなくても良い気がする
void printList(List list) {
	Node* ptr = list.head;
	if (ptr == NULL) {
		puts("Data Not Found.");
	}
	else {
		puts("No | Data");
		puts("---| -------------------------------");
		while (ptr != NULL) {
			// 参照するメンバーデータ
			Member crtData = ptr->data;
			printf("%3d|%s \n", crtData.no, crtData.name);
			ptr = ptr->next;
		}
		puts("---| -------------------------------");
	}
}

int main() {
	List list;
	InitList(&list);

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
			Node* ptr = list.head;
			printf("No     :"); scanf("%d", &Menber.no);
			printf("Name :"); scanf("%s", &Menber.name);
			if (ptr == NULL) { // リストが空だったら先頭に
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
						if (ptr->next == NULL) {
							puts("Number is So big. This Data will add End of List.");
							break;
						}
						ptr = ptr->next;
					}
					InsertAfter(&list, ptr, &Menber);
				}
			}
			break;
		}

		case 3: {
			puts("Bye.");
			free(list.head);
			return 0;		// 終わらせる
		}

		default: {
			puts("This order Not Found.");
			break;
		}
		}
	}
}