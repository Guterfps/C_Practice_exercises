

#include <stdio.h>
#include <stddef.h>
#include <limits.h>

int EqualSubArrySeparator(int *arr, size_t len);

int main(void)
{
	int arr1[] = {1,4,2,5};
	int arr2[] = {2,3,4,1,4,5};
	size_t len1 = sizeof(arr1) / sizeof(*arr1);
	size_t len2 = sizeof(arr2) / sizeof(*arr2);
	
	printf("seperator: %d, ", EqualSubArrySeparator(arr1, len1));
	(arr1[2] == EqualSubArrySeparator(arr1, len1)) ?
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("seperator: %d, ", EqualSubArrySeparator(arr2, len2));
	(arr2[3] == EqualSubArrySeparator(arr2, len2)) ?
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	return 0;
}

int EqualSubArrySeparator(int *arr, size_t len)
{
	int sum1 = 0;
	int sum2 = 0;
	size_t i = 0, j = 0;
	
	if (3 > len)
	{
		return INT_MIN;
	}
	
	for (i = 0; i < len; ++i)
	{
		sum1 += arr[i];
		for (j = i + 2; j < len; ++j)
		{
			sum2 += arr[j];
		}
		
		if (sum1 == sum2)
		{
			return arr[i + 1];
		}
		sum2 = 0;
	}
	
	return INT_MIN;
}

