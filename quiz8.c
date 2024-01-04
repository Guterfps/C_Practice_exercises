#include <stdio.h>
#include <limits.h>

int MaxSubArry(int *arr, int len, int *start, int *end);

int main()
{
	int arr[] = {-2, 1, -3, 4, -1, 2, 3, -5, 4};
	int start = 0;
	int end = 0;
	int len = sizeof(arr) / sizeof(*arr);
	
	printf("max sub arry starts: %d ,ends: %d ,and sum is: %d \n",
			start, end, MaxSubArry(arr, len, &start, &end));

	return 0;
}


int MaxSubArry(int *arr, int len, int *start, int *end)
{
	int max_so_far = INT_MIN;
	int max_ending = 0;
	int temp_indx = 0;
	int i = 0;
	
	for (;i < len ; ++i)
	{
		max_ending += arr[i];
		
		if (max_so_far < max_ending)
		{
			max_so_far = max_ending;
			*start = temp_indx;
			*end = i;
		}
		
		if (max_ending < 0)
		{
			max_ending = 0;
			temp_indx = i + 1;
		}
	}
	
	return max_so_far;
}



