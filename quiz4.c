#include<stdio.h>


int IsSumFound(int *arr, int sum, int len);


int main()
{
	int arr[] = {2, 4, 7, 12 ,14};
	int len = sizeof(arr) / sizeof(*arr);
	
	printf("Is Sum %d : %d \n", 21, IsSumFound(arr, 21, len));
	printf("Is Sum %d : %d \n", 4, IsSumFound(arr, 4, len));
	printf("Is Sum %d : %d \n", 30, IsSumFound(arr, 30, len));
	printf("Is Sum %d : %d \n", 6, IsSumFound(arr, 6, len));
	printf("Is Sum %d : %d \n", 10, IsSumFound(arr, 10, len));
	
	return 0;
}

int IsSumFound(int *arr, int sum, int len)
{
	int *start = arr;
	int *end = arr + len - 1;
	
	while (start != end)
	{
		if ((*start + *end) > sum)
		{
			--end;
		}
		else if ((*start + *end) < sum)
		{
			++start;
		}
		else
		{
			return 1;
		}
	}
	
	return 0;
}


