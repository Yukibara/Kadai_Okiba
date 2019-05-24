#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define ALLEY_SIZE 1024

// 等しければ0を、a>bであれば正の値を、a<bであれば負の値を返す
// 比較用関数
int minComp(const void* a, const void* b) {
	int res = 0;
	if (*(int*)a > *(int*)b)res = 1;
	else if (*(int*)a <*(int*) b)res = -1;

	return res;
}

// 二分探索用関数
// size_tはVS2019環境だとunsigned intとして定義されている
void* binserch(const void* key, const void* base,
	size_t nmemb, size_t size,
	int (*compar)(const void*, const void*)) {

	// absを使いたいので、long long にしておく(unsigned int だとそのままではabs使えない)
	// (intだとあふれるかも)
	long long no = -1;
	long long yes = nmemb;

	// めぐる式二分探索
	// 探索範囲を左から右から、どんどん狭めていく感じ
	while (abs(yes - no)>1) {
		long long mid = (yes + no) / 2;
		int de = *((int*)base + mid);
		// 汎用ポインタは加算・減算ができないので1byteのcharにキャストして操作する
		if(compar((char*)base+size*mid,key)>=0){
			yes = mid;
		}
		else {
			no = mid;
		}
	}
	// 一致していたらそれを返して、違ったらNULL
	if (compar((char*)base+size*yes,key)==0)return &yes;
	else return NULL;
}

int main(void) {
	int number_list[ALLEY_SIZE] = {0};
	for (int i = 0; i < ALLEY_SIZE; i++) {
		// 0,3,6,9,........
		number_list[i] = i * 3;
	}

	while (1) {
		int order;
		printf("Please input your Order. 1:Search 2:Exit   ->"); scanf("%d",&order);

		// switch文が面倒になったのでif文で書いた,2以外だったら全部Search
		if (order == 2) { puts("Bye."); return 0; }

		int search;
		printf("Please input number that you want to search：");
		scanf("%d", &search);

		// 二分探索関数の呼び出し
		int *res_serch = (int *)binserch(&search, number_list, 1024, sizeof(int), (int(*)(const void*,const void*))minComp);
		// 見つからなかった(関数からNULLが返ってきた)
		if (res_serch == NULL) {
			printf("Not Found.\n");
		}
		// 見つかった
		else {
			// 1-indexにして表示する
			printf("Found ! It is  %dth in index \n", (*res_serch)+1);
		}
	}

	return 0;
}