#define _CRT_SECURE_NO_WARNINGS
#define ARRAY_SIZE 5
#include <stdio.h>

double aveof(const int a[], int n) {
	double sum = 0;
	for (int i = 0; i < n; i++) {
		sum += a[i];
	}
	return sum / n;
}

int main() {
	int data[ARRAY_SIZE] = { 5,2,3,4,6 };
	int size = ARRAY_SIZE;

	for (int i = 0; i < size; i++) {
		printf("%d ", data[i]);
	}
	printf(". average is %f.\n", aveof(data, size));

	return 0;
}