#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int getMedian(int a, int b, int c) {
	if (b <= a) {
		if (c <= b) { // a<b<c, c=b<a, c<b=a, a=b=c 
			return b;
		}
		else if (a <= c) { // b<a=c, b<a<c, b=a<c
			return a;
		}
		else { // b<c<a
			return c;
		}
	}
	else if (c < a) { // c<a<b
		return a;
	}
	else if (c < b) { // a=c<b, a<c<b
		return c;
	}
	else { // a<b<c, a<b=c
		return b;
	}
}

int main() {
	// なんかいい感じの実装できるかもしれないし出来ないかもしれない
	printf("2,1,1の中央値は%d\n", getMedian(2, 1, 1));
	printf("1,0,2の中央値は%d\n", getMedian(1, 0, 2));
	printf("2,2,1の中央値は%d\n", getMedian(2, 2, 1));
	printf("1,1,2の中央値は%d\n", getMedian(1, 1, 2));
	printf("2,0,1の中央値は%d\n", getMedian(2, 0, 1));
	printf("1,2,0の中央値は%d\n", getMedian(1, 2, 0));
	printf("1,2,1の中央値は%d\n", getMedian(1, 2, 1));
	printf("0,2,1の中央値は%d\n", getMedian(0, 2, 1));
	printf("2,2,2の中央値は%d\n", getMedian(2, 2, 2));
	printf("0,1,2の中央値は%d\n", getMedian(0, 1, 2));
	printf("1,2,2の中央値は%d\n", getMedian(1, 2, 2));
	printf("2,1,2の中央値は%d\n", getMedian(2, 1, 2));
	printf("2,1,0の中央値は%d\n", getMedian(2, 1, 0));

	return 0;
}
