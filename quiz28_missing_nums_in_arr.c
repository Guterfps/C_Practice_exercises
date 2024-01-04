
#include <stdio.h>
#include <stddef.h>

void MathPrintMissingNums(int *arr, size_t len);
void XORPrintMissingNums(int *arr, size_t len);

int main(void)
{
	int arr1[] = {5, 3, 6, 1};
	size_t len1 = sizeof(arr1) / sizeof(*arr1);
	int arr2[] = {4, 2, 1};
	size_t len2 = sizeof(arr2) / sizeof(*arr2);
	int arr3[] = {2, 1};
	size_t len3 = sizeof(arr3) / sizeof(*arr3);
	
	printf("test1:\n");
	MathPrintMissingNums(arr1, len1);
	XORPrintMissingNums(arr1, len1);
	printf("test2:\n");
	MathPrintMissingNums(arr2, len2);
	XORPrintMissingNums(arr2, len2);
	printf("test3:\n");
	MathPrintMissingNums(arr3, len3);
	XORPrintMissingNums(arr3, len3);
	
	return 0;
}

void MathPrintMissingNums(int *arr, size_t len)
{
	int arr_sum = 0;
	int mis_nums_sum = 0;
	int avg = 0;
	int up_to_avg_sum = 0;
	int first_num = 0;
	int second_num = 0;
	size_t i = 0;
	
	for (; i < len; ++i)
	{
		arr_sum += arr[i];
	}
	
	mis_nums_sum = ((len + 2) * (len + 3)) / 2 - arr_sum;
	avg = mis_nums_sum / 2;
	
	for (i = 0; i < len; ++i)
	{
		up_to_avg_sum += (arr[i] <= avg) ? arr[i] : 0;
	}
	
	first_num = (avg * (avg + 1)) / 2 - up_to_avg_sum;
	printf("first missing number: %d \n", first_num);
	second_num = mis_nums_sum - first_num;
	printf("second missing number: %d \n", second_num);
}

void XORPrintMissingNums(int *arr, size_t len)
{
	int arr_xor = 0;
	int set_on_bit = 0;
	int first_num = 0;
	int second_num = 0;
	size_t i = 0;
	
	for (; i < len; ++i)
	{
		arr_xor ^= arr[i];
	}
	for (i = 1; i <= (len + 2); ++i)
	{
		arr_xor ^= i;
	}
	
	set_on_bit = arr_xor & ~(arr_xor - 1);
	
	for (i = 0; i < len; ++i)
	{
		(arr[i] & set_on_bit) ? (first_num ^= arr[i]) : (second_num ^= arr[i]);
	}
	
	for (i = 1; i <= (len + 2); ++i)
	{
		(i & set_on_bit) ? (first_num ^= i) : (second_num ^= i);
	}
	
	printf("XOR missing nums: %d, %d \n", first_num, second_num);
}

