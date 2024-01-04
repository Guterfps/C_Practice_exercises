
#include <stdio.h>
#include <stddef.h>
#include <assert.h>

int RotatedArrBinarySearch(int *arr, size_t len, int target);

int main(void)
{
	int arr[] = {4,5,10,-2,3};
	size_t len = sizeof(arr) / sizeof(*arr);
	int arr2[] = {7,8,11,1,4,5};
	size_t len2 = sizeof(arr2) / sizeof(*arr2);
	
	printf("target at index: %d	", RotatedArrBinarySearch(arr, len, -2));
	(-2 == arr[RotatedArrBinarySearch(arr, len, -2)]) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("target at index: %d	", RotatedArrBinarySearch(arr, len, 5));
	(5 == arr[RotatedArrBinarySearch(arr, len, 5)]) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("target at index: %d	", RotatedArrBinarySearch(arr, len, 3));
	(3 == arr[RotatedArrBinarySearch(arr, len, 3)]) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("target at index: %d	", RotatedArrBinarySearch(arr2, len2, 11));
	(11 == arr2[RotatedArrBinarySearch(arr2, len2, 11)]) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("target at index: %d	", RotatedArrBinarySearch(arr2, len2, 7));
	(7 == arr2[RotatedArrBinarySearch(arr2, len2, 7)]) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("target at index: %d	", RotatedArrBinarySearch(arr2, len2, 10));
	(-1 == RotatedArrBinarySearch(arr2, len2, 10)) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("target at index: %d	", RotatedArrBinarySearch(arr, len, 10));
	(10 == arr[RotatedArrBinarySearch(arr, len, 10)]) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	return 0;
}

int RotatedArrBinarySearch(int *arr, size_t len, int target)
{
	int start = 0;
	int end = len - 1;
	int mid = 0;
	
	assert(NULL != arr);
	
	if (0 == len) {return -1;}
	
	do
	{
		mid = (start + end) / 2;
		
		if (arr[start] < arr[mid])
		{
			if ((target >= arr[start]) && (target <= arr[mid]))
			{
				end = mid - 1;
			}
			else
			{
				start = mid + 1;
			}		
		}
		else
		{
			if ((target >= arr[mid]) && (target <= arr[end]))
			{
				start = mid + 1;
			}
			else
			{	
				end = mid - 1;
			}
		}
	}
	while ((start <= end) && (arr[mid] != target));
	
	return ((arr[mid] == target) ? mid : -1);
}


