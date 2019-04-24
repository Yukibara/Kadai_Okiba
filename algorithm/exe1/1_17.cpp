#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void spira(int n) {
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n - 1; j++) {
			putchar(' ');
		}
		for (int j = 0; j < i * 2 + 1; j++) {
			putchar('*');
		}
		puts("");
	}
}

int main() {
	int h;
	printf("‚‚³‚ð“ü—Í‚µ‚Ä‚­‚¾‚³‚¢F"); scanf("%d", &h);

	spira(h);

	return 0;
}
