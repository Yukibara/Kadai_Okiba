#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 2048

typedef struct node {
	char data;
	struct node* next;
}Node;

typedef struct {
	Node* head;
	Node* crnt;
}List;

typedef struct {
	int max;
	int num;
	List stk;
}Stack;

void Initlialize(Stack* st, int maxsize) {
	st->max = maxsize; // 使ってない
	st->num = 0;
	st->stk.head = NULL;
	st->stk.crnt = NULL;
}

// 空だったら1、そうでなければ0
int isEmpty(Stack* st) {
	if (st->num <= 0) {
		return 1;
	}
	else return 0;
}

// stackに積む
int stack_push(Stack* st, char c) {
	st->stk.crnt = st->stk.head;
	// メモリ確保に失敗
	if ((st->stk.head = calloc(1, sizeof(Node))) == NULL) {
		puts("push faild");
		return -1;
	}
	// メモリ確保に成功
	st->stk.head->data = c;
	st->stk.head->next = st->stk.crnt;
	(st->num)++;
	return 0;
}

// stackからpopする
char stack_pop(Stack* st) {
	if (isEmpty(st)) {
		puts("Stack is Empty. Pop failed.");
		return NULL;
	}
	else {
		char res;
		st->stk.crnt = st->stk.head->next;
		res = st->stk.head->data;
		free(st->stk.head);
		st->stk.head = st->stk.crnt;
		(st->num)--;
		return res;
	}
}

// Stackを
// FRONT
// [中身]
// BACK
// の形式で表示する
void printStack(Stack* st) {
	if (isEmpty(st)) {
		puts("Stack is Empty.");
		return;
	}
	st->stk.crnt = st->stk.head;
	puts("FRONT");
	while (st->stk.crnt != NULL) {
		printf("%c\n", st->stk.crnt->data);
		st->stk.crnt = st->stk.crnt->next;
	}
	puts("BACK");
}

// 中身の改変があろうとなかろうと、
// ポインタ渡しにしないとその都度コピーが発生するので非効率的になりダメっぽい
int size(Stack* st) {
	return st->num;
}

int main(void) {
	Stack st;
	Initlialize(&st, MAX_STACK_SIZE);

	int menu;
	char c;
	while (1) {
		printf("1:PUSH 2:POP 3:PRINT 0:EXIT ->");
		scanf("%d", &menu);
		while (getchar() != '\n'); // バッファをクリアする
		switch (menu) {
		case 1:
			printf("Please enter you want to push char. -> ");
			scanf("%c", &c);
			stack_push(&st, c);
			printf("%c pushed! \n", c);
			break;
		case 2:
			c = stack_pop(&st);
			printf("%c popped! \n", c);
			break;
		case 3:
			printStack(&st);
			break;
		case 0:
			puts("Bye.");
			return 0;
		default:
			break;
		}
	}

	return 0;
}