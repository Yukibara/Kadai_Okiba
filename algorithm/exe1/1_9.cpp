#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

int sumof(int a, int b) {
	int c = abs(a-b)+1;
	return c * (a+b)/2;
}

int main() {
	printf("%d", sumof(1, 10));
	return 0;
}
