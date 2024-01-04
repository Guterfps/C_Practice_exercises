
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_RANGE 100

int num_hist[NUM_RANGE] = {0};

size_t GetNonRepeatingRandom(void);
void ResetHistogram(void);
int IsDupInArr(size_t *arr, size_t len);

int main(void)
{
	size_t arr[NUM_RANGE] = {0};
	size_t len = sizeof(arr) / sizeof(*arr);
	size_t arr2[NUM_RANGE] = {0};
	size_t len2 = sizeof(arr2) / sizeof(*arr2);
	size_t i = 0;
	
	for(; i < len; ++i)
	{
		arr[i] = GetNonRepeatingRandom();
	}
	
	printf("non repiting random nums: \n");
	for(i = 0; i < len; ++i)
	{
		printf("%ld,", arr[i]); 
	}
	printf("\n");
	
	!IsDupInArr(arr, len) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	for(i = 0; i < len; ++i)
	{
		arr2[i] = GetNonRepeatingRandom();
	}
	
	printf("test2:	");
	!IsDupInArr(arr2, len2) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	return 0;
}

size_t GetNonRepeatingRandom(void)
{
	static size_t counter = 0;
	size_t rand_num = 0;
	
	srand(time(NULL));
	
	if (NUM_RANGE == counter)
	{
		ResetHistogram();
		counter = 0;
	}
	
	do
	{
		rand_num = rand() % NUM_RANGE;
	}
	while (0 != num_hist[rand_num]);
	
	num_hist[rand_num] = 1;
	++counter;
	
	return (rand_num);
}

void ResetHistogram(void)
{
	size_t i = 0;
	
	for (; i < NUM_RANGE; ++i)
	{
		num_hist[i] = 0;
	}
}

int IsDupInArr(size_t *arr, size_t len)
{
	size_t i = 0;
	size_t xor = 0;
	
	for (i = 0; i < len; ++i)
	{
		xor = arr[i] ^ xor;
	}
	
	for (i = 0; i < NUM_RANGE; ++i)
	{
		xor = i ^ xor;
	}
	
	return xor;
}
