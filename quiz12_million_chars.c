#include <stdio.h>
#include <stddef.h>
#include<stdlib.h>

static size_t Histogram[256] = {0};

void MillionChars(unsigned char c);
size_t CountSetBits(long num);

int main(void)
{
	unsigned char c = 0;
	printf("num of bits in long: %ld \n", CountSetBits((long)12345));
	
	system("stty -icanon");
	while (1)
	{
		c = getchar();
		MillionChars(c);
	}
	system("stty icanon");
	
	return 0;
}

void MillionChars(unsigned char c)
{
	size_t max = 0;
	unsigned char temp_char = 0;
	size_t i = 0;
	
	if ('0' == c)
	{
		for (; i < 256; ++i)
		{
			if (max < Histogram[i])
			{
				max = Histogram[i];
				temp_char = i;
			}
			
			Histogram[i] = 0;
		}
		printf("\nmax char is: %c number of press: %ld \n", temp_char, max);
	}
	else
	{
		Histogram[(int)c] += 1;
	}
}

size_t CountSetBits(long num)
{
	size_t counter = 0;
	
	for (; num; ++counter)
	{
		num &= (num - 1);
	}
	
	return counter;
}

