#include <stdio.h>
#include <stddef.h>

long *SumIntPairsToLongs(int ints[], size_t numOfElements);

int main(void)
{
	int nums[] = {1,6,456,-3,8,12};
	size_t len = sizeof(nums) / sizeof(*nums);
	size_t i = 0;
	
	for (; i < len; ++i)
	{
		printf("%d ", nums[i]);
	}
	printf("\n");
	
	SumIntPairsToLongs(nums, len);
	
	for (i = 0; i < (len / 2); ++i)
	{
		printf("%ld ", *((long *)nums + i));
	}
	printf("\n");
	
	return 0;
}

long *SumIntPairsToLongs(int ints[], size_t numOfElements)
{
	long *longs = (long *)ints;
	size_t i = 0, j = 0;
	
	for (; j < numOfElements; ++i, j += 2)
	{
		longs[i] = ints[j] + ints[j + 1];
	}
	
	return longs;
}


