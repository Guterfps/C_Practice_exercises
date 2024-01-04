
#include <stdio.h>


void StringPermutations(char *str, size_t start, size_t end);
void SwapLoop(char *str, size_t start, size_t end);
void Swap(char *a, char *b);

int main(void)
{
	char str[] = "ahi";
	size_t len = sizeof(str) / sizeof(*str);
	char str2[] = "ABCD";
	size_t len2 = sizeof(str2) / sizeof(*str2);
	
	StringPermutations(str, 0, len - 1);
	printf("\n");
	StringPermutations(str2, 0, len2 - 1);
	printf("\n");
	
	return 0;
}

void StringPermutations(char *str, size_t start, size_t end)
{	
	if (start == end)
	{
		printf("%s, ", str);
	}
	else
	{
		SwapLoop(str, start, end);
	}
}

void SwapLoop(char *str, size_t start, size_t end)
{
	size_t i = 0;
	
	for (i = start; i < end; ++i)
	{
		Swap(str + start, str + i);
		StringPermutations(str, start + 1, end);
		Swap(str + start, str + i);
	}
}

void Swap(char *a, char *b)
{
	if (a != b)
	{
		*a ^= *b;
		*b ^= *a;
		*a ^= *b;
	}
}


