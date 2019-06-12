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

// 中身の改変がsあろうとなかろうと、
// ポインタ渡しにしないとその都度コピーが発生するので非効率的になりダメっぽい
int size(Stack* st) {
	return st->num;
}

int judge(char* str) {
	Stack stk;
	Initlialize(&stk, MAX_STACK_SIZE);
	char c;
	for (int i = 0; str[i] != '\0'; i++) {
		switch (str[i]) {
		case '{':
		case '[':
		case '(':
			stack_push(&stk, str[i]);
			break;

		case '}':
			c = stack_pop(&stk);
			if (c != '{')return 0;
			break;
		case ']':
			c = stack_pop(&stk);
			if (c != '[')return 0;
			break;
		case ')':
			c = stack_pop(&stk);
			if (c != '(')return 0;
			break;
		default:
			break;
		}
	}
	if (isEmpty(&stk))
		return 1;
	else
		return 0;
}

int main(void) {
	char str[256];
	int flag_continue;
	do {
		printf("Please enter string :"); 
		// 空白を含むときの実装を考える必要あり
		scanf("%[^\n]%*c", str);

		if (judge(str)) {
			puts("Correct!");
		}
		else {
			puts("Incorrect.");
		}
		printf("1:Continue   0:Exit ->");
		scanf("%d", &flag_continue);
		while (getchar() != '\n');
	} while (flag_continue);

	return 0;
}