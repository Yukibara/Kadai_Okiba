#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int mdays[2][12] = {
	{31,28,31,30,31,30,31,31,30,31,30,31},
	{31,29,31,30,31,30,31,31,30,31,30,31}
};

int isleap(int year) {
	return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
}

typedef struct {
	int y;
	int m;
	int d;
} YMD;

YMD after(YMD x, int n) {
	x.d += n;
	while (x.d > mdays[isleap(x.y)][x.m-1]) {
		x.d -= mdays[isleap(x.y)][x.m-1];
		if (x.m >= 12) {		// 12月になったら1年増やして1月に戻る
			x.y++;
			x.m = 1;
		}else {
			x.m++;				// 12月じゃなかったら月を増やす
		}
	}
	return x;
}

int main(void) {
	YMD date;
	int day,retry;

	do {
		printf("年		：");		scanf("%d", &date.y);
		printf("月		：");		scanf("%d", &date.m);
		printf("日		：");		scanf("%d", &date.d);
		printf("何日後	：");		scanf("%d", &day);
		
		printf("%5d年%2d月%2d日の%d日後は、\n", date.y, date.m, date.d, day);

		date = after(date, day);

		printf("%5d年%2d月%2d日です。\n", date.y, date.m, date.d);
		printf("もう一度しますか (1...はい/0...いいえ):");
		scanf("%d", &retry);
	} while (retry == 1);

	return 0;
}