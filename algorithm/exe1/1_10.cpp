#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
	int a,b;

	printf("a�̒l�F"); scanf("%d", &a); //a�̓���

	while (1) { //b�̓���
		printf("b�̒l�F"); scanf("%d", &b);
		if (a >= b) {
			puts("a���傫�Ȓl�����Ă�������");
		}
		else break;
	}
	printf("b-a��%d�ł�\n", b - a);
	return 0;
}
