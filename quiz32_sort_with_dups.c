

#include <stdio.h>
#include <stddef.h>

void Sort0and1Arr(int *arr, size_t len);
void Swap(int *a, int *b);
void PrintArr(int *arr, size_t len);

int main(void)
{
	int arr[] = {1,0,0,1,0,1,1,1,1,0,1,0};
	size_t len = sizeof(arr) / sizeof(*arr);
	
	printf("before sort: ");
	PrintArr(arr, len);
	printf("\n");
	
	Sort0and1Arr(arr, len);
	printf("after sort: ");
	PrintArr(arr, len);

	return 0;
}

void Sort0and1Arr(int *arr, size_t len)
{
	size_t i = 0;
	size_t j = 0;
	
	for(; i < len; ++i)
	{
		for (j = 0; j < (len - i - 1); ++j)
		{
			if (arr[j] > arr[j + 1])
			{
				Swap((arr + j), (arr + j + 1));
			}
		}
	}
}

void Swap(int *a, int *b)
{
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}

void PrintArr(int *arr, size_t len)
{
	size_t i = 0;
	
	for(; i < len; ++i)
	{
		printf("%d, ", arr[i]);
	}
	printf("\n");
}

