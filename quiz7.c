#include<stdio.h>

int NumOfCoupelBits(char c);
void Swap1(int *num1, int *num2);
void Swap2(int *num1, int *num2);
void Swap3(int *num1, int *num2);
int NumOfSetBits(long int num);


int main()
{
	int num1 = 1;
	int num2 = 2;
	
	printf("%d \n", NumOfCoupelBits('v'));
	
	printf("num1: %d num2: %d \n", num1, num2);
	Swap1(&num1, &num2);
	printf("num1: %d num2: %d \n", num1, num2);
	Swap2(&num1, &num2);
	printf("num1: %d num2: %d \n", num1, num2);
	Swap3(&num1, &num2);
	printf("num1: %d num2: %d \n", num1, num2);
	
	printf("num of set bits: %d \n", NumOfSetBits((long int)97));
	
	return 0;
}


int NumOfCoupelBits(char c)
{
	int counter = 0;
	int size = sizeof(char) * 8 - 1;
	
	while (size > 1)
	{
		if (((1 << size) & c) && ((1 << (size - 1)) & c))
		{
			++counter;
		}
		--size;
	}
	
	return counter;
}

void Swap1(int *num1, int *num2)
{
	int temp = *num1;
	*num1 = *num2;
	*num2 = temp;
}

void Swap2(int *num1, int *num2)
{
	*num1 = *num1 + *num2;
	*num2 = *num1 - *num2;
	*num1 = *num1 - *num2;
}

void Swap3(int *num1, int *num2)
{
	*num1 = *num1 ^ *num2;
	*num2 = *num1 ^ *num2;
	*num1 = *num1 ^ *num2;
}

int NumOfSetBits(long int num)
{
	int counter = 0;
	
	while (num)
	{
		num &= (num - 1);
		++counter;
		printf("num of loops: %d \n", counter);
	}
	
	return counter;
}


