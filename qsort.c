#include <stdio.h>
#include <stdlib.h> // rand() 함수 포함 라이브러리

void swap(int* pnum1, int* pnum2) 
{
	int tmp = *pnum1;
	*pnum1 = *pnum2;
	*pnum2 = tmp;
}
void print_arr(int* arr, int len) 
{
	
	for (int i = 0; i < len; ++i) 
	{
		printf("%d ", arr[i]);
	}
	printf("\n");

}
void test1() 
{
	int arr[] = {3,2,6,4,5,8,7,1};
	int length = sizeof(arr) / sizeof(int);

	int pivot = length-1;
	int target = 0;
	
	//1회전
	for (int i = target; i < length; ++i) 
	{
		if (arr[i] < arr[pivot]) 
		{
			swap(&arr[i], &arr[i + 1]);
			target = i + 1;
		}
	}

	swap(&arr[target], &arr[pivot]);
	print_arr(arr, length);

	// 예상 결과
	// 1,2,6,4,5,8,7,3
}
int cnt = 0;
int cnt2 = 0;
int cnt3 = 0;

void test2(int* arr, int start, int end) 
{
	cnt3++;
	if (start > end) {
		return;
	}
	int pivot = end;
	int target = start;
	int len = end - start + 1;

	for (int i = target; i < end; ++i) 
	{
		cnt++;
		if (arr[i] < arr[pivot]) 
		{
			swap(&arr[i], &arr[target]);
			++target;
		}
	}

	swap(&arr[target], &arr[pivot]);
	// 픽스된 원소를 기준으로 좌우 갈라쇼
	//printf("start : %d\n", start);
	//printf("end : %d\n", end);
	//print_arr(arr, len);
	test2(arr, start, target - 1);
	test2(arr, target + 1, end);
}
void bubble_sort(int* arr, int len)
{
	for (int i = 0; i < len - 1; i++) 
	{
		for (int j = 0; j < len - i - 1; j++)
		{
			cnt2++;
			if (arr[j] > arr[j + 1]) {
				swap(&arr[j], &arr[j + 1]);
			}
		}
	}
}
int main()
{
	int len2 = 100000;
	int* arr2 = (int*)malloc(sizeof(int) * len2);
	for (int i = 0; i < len2; i++)
	{
		int ran = rand() % len2;
		*(arr2 + i) = ran;
	}
	int arr[] = {4,1,2,8,7,3,6,5};
	int arr1[] = {1,2,1,7,45,51,21,11,248,78,7,33,16,15,5,1,2,4,1,33,182};

	int len = sizeof(arr1) / sizeof(int);
	printf("%d, %d\n", arr2[999], len2);
	test2(arr2, 0, len2 - 1);
	bubble_sort(arr2, len2);
	printf("%d\n", cnt);
	printf("%d\n", cnt2);
	//print_arr(arr2, len2);
	return 0;
}