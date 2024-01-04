
#include <stdio.h>
#include <stddef.h>

int FindNumInConstIfs(int *arr, size_t len, int num);


int main(void)
{
	int arr1[] = {1,20,-3,0,25,123};
	int arr2[] = {1,20,-3,0,5,123};
	size_t len1 = sizeof(arr1) / sizeof(*arr1);
	size_t len2 = sizeof(arr2) / sizeof(*arr2);
	
	printf("in arr: %d\n", FindNumInConstIfs(arr1, len1, 25));
	printf("in arr: %d\n", FindNumInConstIfs(arr1, len1, 3));
	printf("in arr: %d\n", FindNumInConstIfs(arr2, len2, 25));
	printf("in arr: %d\n", FindNumInConstIfs(arr2, len2, -3));

	return 0;
}

int FindNumInConstIfs(int *arr, size_t len, int num)
{
	int status = 1;
	size_t i = 0;
	
	for (; i < len; ++i)
	{
		status *= arr[i] ^ num;
	}
	
	return (!status);
}


