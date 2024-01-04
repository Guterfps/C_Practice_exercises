
#include <stdio.h>
#include <stdlib.h>

int FindKthSmallestElem(int *arr, size_t len, size_t k);
int CmpFunc(const void *data1, const void *data2);

int main(void)
{
	int arr[] = {0,-1,1, 2, 3,10 ,25, -69 ,420, 3};
	size_t len = sizeof(arr) / sizeof(*arr);
	
	printf("3rd smallest element: %d\n", FindKthSmallestElem(arr, len, 3));
	printf("last smallest element: %d\n", FindKthSmallestElem(arr, len, len - 1));
	printf("first smallest element: %d\n", FindKthSmallestElem(arr, len, 1));
	printf("5th smallest element: %d\n", FindKthSmallestElem(arr, len, 5));
	
	return 0;
}

int FindKthSmallestElem(int *arr, size_t len, size_t k)
{
	qsort(arr, len, sizeof(int), &CmpFunc);
	
	return (arr[k - 1]);
}

int CmpFunc(const void *data1, const void *data2)
{
	return (*(int *)data1 - *(int *)data2);
}
