#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
	int a,b;

	printf("aの値："); scanf("%d", &a); //aの入力

	while (1) { //bの入力
		printf("bの値："); scanf("%d", &b);
		if (a >= b) {
			puts("aより大きな値を入れてください");
		}
		else break;
	}
	printf("b-aは%dです\n", b - a);
	return 0;
}
