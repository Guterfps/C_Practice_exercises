
#include <stdio.h>
#include <stddef.h>
#include <limits.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int FindKthSmallestElem(int *arr, size_t len, size_t k);
size_t Count(int *arr, size_t len, size_t mid);

int main(void)
{
	int arr[] = {1,0,5,25,-1,9,42,7};
	size_t len = sizeof(arr) / sizeof(*arr);
	size_t i = 0;
	
	for (i = 1; i < len; ++i)
	{
		printf("%ldth smallest element is: %d\n", i, 
				FindKthSmallestElem(arr, len, i));
	}

	return 0;
}

int FindKthSmallestElem(int *arr, size_t len, size_t k)
{
	int low = INT_MAX;
	int high = INT_MIN;
	size_t i = 0;
	
	for (; i < len; ++i)
	{
		low = MIN(low, arr[i]);
		high = MAX(high , arr[i]);
	}
	
	while (low < high)
	{
		size_t mid = low + (high - low) / 2;
		
		if (Count(arr, len, mid) < k)
		{
			low = mid + 1;
		}
		else
		{
			high = mid;
		}
	}
	
	return low;
}

size_t Count(int *arr, size_t len, size_t mid)
{
	size_t counter = 0;
	size_t i = 0;
	
	for (; i < len; ++i)
	{
		if (arr[i] <= (int)mid)
		{
			++counter;
		}
	}
	
	return counter;
}

