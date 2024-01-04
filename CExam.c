
#include <stdio.h>
#include <stddef.h>
#include <limits.h>

int FlipDigitsInNum(int num);
unsigned char MirrorByte(unsigned char byte);
void PrintByte(unsigned char c);
void PrintInt(int num);
int FlipBit(int val, unsigned int n);
size_t CountSetBits(unsigned char byte);
char RotateLeft(char byte, unsigned int nbits);
void SwapPointers(int **p1, int **p2);
size_t StrLen(const char *str);
int StrCmp(const char *s1, const char *s2);
char *StrCpy(char *dest, const char *src);
char *StrNCpy(char *dest, const char *src, size_t n);
char *StrCat(char *dest, const char *src);
unsigned long GetNFibonacciElement(unsigned int n);
char *IntToString(char *str, int num);
size_t NumOfDigs(int num);
int MultBy8(int num);
void SwapTwoInts1(int *a, int *b);
void SwapTwoInts2(int *a, int *b);
void SwapTwoInts3(int *a, int *b);

int main(void)
{
	int test_flip_num = -123;
	unsigned char test_mirror = 'W';
	int test_flip_bit = 123;
	int *test_swap1 = &test_flip_num;
	int *test_swap2 = &test_flip_bit;
	char str[] = "ahi";
	char str2[] = "Ahi";
	char str3[] = "ahi";
	char copy1[10] = {0};
	char copy2[10] = {0};
	char test_itoa[11] = {0};
	int a = 1;
	int b = 2;
	
	printf("-123 fliped is: %d\n",  FlipDigitsInNum(test_flip_num));
	
	printf("a in bits: ");
	PrintByte(test_mirror);
	printf("mirror in bits: ");
	PrintByte(MirrorByte(test_mirror));
	
	printf("123 in bits: ");
	PrintInt(test_flip_bit);
	printf("123 flip bit: ");
	PrintInt(FlipBit(test_flip_bit, 3));
	
	printf("num of set bits in W: %ld \n", CountSetBits(test_mirror));
	
	printf("W in bits: ");
	PrintByte(test_mirror);
	printf("W after rotate left 3: ");
	PrintByte(RotateLeft('W', 3));
	
	SwapPointers(&test_swap1, &test_swap2);
	printf("num1: %d, num2: %d\n", test_flip_num, test_flip_bit);
	printf("p1 value: %d, p2 value: %d\n", *test_swap1, *test_swap2);
	
	printf("len of %s: %ld \n", str, StrLen(str));
	
	printf("%s comp %s: %d \n", str2, str, StrCmp(str2, str));
	printf("%s comp %s: %d \n", str3, str, StrCmp(str3, str));
	
	StrCpy(copy1, str);
	StrNCpy(copy2, str, 2);
	printf("strcopy: %s\n", copy1);
	printf("strNcopy: %s\n", copy2);
	
	StrCat(str3, str2);
	printf("str cat: %s\n", str3);
	
	printf("fibonacci 2: %ld \n", GetNFibonacciElement(2));
	printf("fibonacci 3: %ld \n", GetNFibonacciElement(3));
	printf("fibonacci 4: %ld \n", GetNFibonacciElement(4));
	printf("fibonacci 5: %ld \n", GetNFibonacciElement(5));
	printf("fibonacci 83: %ld \n", GetNFibonacciElement(83));
	
	printf("%d to string: %s\n", 0, IntToString(test_itoa, 0));
	printf("%d to string: %s\n", -123, IntToString(test_itoa, -123));
	printf("%d to string: %s\n", 25, IntToString(test_itoa, 25));
	
	printf("0 * 8 = %d\n", MultBy8(0));
	printf("-123 * 8 = %d\n", MultBy8(-123));
	printf("123 * 8 = %d\n", MultBy8(123));
	
	printf("before swap: a = %d, b = %d \n", a, b);
	SwapTwoInts1(&a, &b);
	printf("swap1: a = %d, b = %d \n", a, b);
	SwapTwoInts2(&a, &b);
	printf("swap2: a = %d, b = %d \n", a, b);
	SwapTwoInts3(&a, &b);
	printf("swap3: a = %d, b = %d \n", a, b);
	
	return 0;
}


int FlipDigitsInNum(int num)
{
	int result = 0;
	int sign = 1;
	
	if (num < 0)
	{
		sign = -1;
		num *= sign;
	}
	
	while (num)
	{
		result *= 10;
		result += num % 10;
		num /= 10;
	}
	
	return (result * sign);
}

unsigned char MirrorByte(unsigned char byte)
{
	unsigned char mirror = 0;
	size_t counter = CHAR_BIT;

	while (--counter)
	{
		mirror += 1 & byte;
		mirror <<= 1;
		byte >>= 1;
	}

	return mirror;
}

void PrintByte(unsigned char c)
{
	unsigned char i = 1 << (CHAR_BIT - 1);
	
	for (; i; i >>= 1)
	{
		(i & c) ? printf("1") : printf("0");
	}
	printf("\n");
}

void PrintInt(int num)
{
	unsigned int i = 1 << (sizeof(int) * CHAR_BIT - 1);
	
	for (; i; i >>= 1)
	{
		(i & num) ? printf("1") : printf("0");
	}
	printf("\n");
}

int FlipBit(int val, unsigned int n)
{
	return (val ^ (1 << (n - 1)));
}

size_t CountSetBits(unsigned char byte)
{
	size_t counter = 0;
	
	while (byte)
	{
		byte &= (byte - 1);
		++counter;
	}
	
	return counter;
}

char RotateLeft(char byte, unsigned int nbits)
{
	nbits &= (CHAR_BIT - 1);
	
	return ((byte << nbits) | (byte >> (CHAR_BIT - nbits)));
}

void SwapPointers(int **p1, int **p2)
{
	*(size_t *)p1 = *(size_t *)p1 ^ *(size_t *)p2;
	*(size_t *)p2 = *(size_t *)p1 ^ *(size_t *)p2;
	*(size_t *)p1 = *(size_t *)p1 ^ *(size_t *)p2;
}

size_t StrLen(const char *str)
{
	size_t counter = 0;
	const char *runer = str;
	
	while ('\0' != *runer)
	{
		++counter;
		++runer;
	}
	
	return counter;
}

int StrCmp(const char *s1, const char *s2)
{
	const char *runer1 = s1;
	const char *runer2 = s2;
	
	while (*runer1 == *runer2 && '\0' != *runer1)
	{
		++runer1;
		++runer2;
	}
	
	return (*runer1 - *runer2);
}

char *StrCpy(char *dest, const char *src)
{
	char *dest_run = dest;
	const char *src_run = src;
	
	while ('\0' != *src_run)
	{
		*dest_run = *src_run;
		++dest_run;
		++src_run;
	}
	*dest_run = '\0';
	
	return dest;
}


char *StrNCpy(char *dest, const char *src, size_t n)
{
	char *dest_run = dest;
	const char *src_run = src;
	
	while (n--)
	{
		*dest_run = *src_run;
		++dest_run;
		++src_run;
	}
	*dest_run = '\0';
	
	return dest;
}

char *StrCat(char *dest, const char *src)
{
	return (StrCpy(dest + StrLen(dest), src));
}

unsigned long GetNFibonacciElement(unsigned int n)
{
	unsigned long elem1 = 1;
	unsigned long elem2 = 1;
	
	if (n < 3)
	{
		return elem1;
	}
	n -= 2;
	
	while (--n)
	{
		elem2 = elem1 + elem2;
		elem1 = elem2 - elem1;
	}
	
	return (elem1 + elem2);
}

char *IntToString(char *str, int num)
{
	char *runer = str;
	
	if (0 == num)
	{
		*runer = '0';
		++runer;
	}
	
	if (num < 0)
	{
		*runer = '-';
		++runer;
		num *= -1;
	}
	
	runer += NumOfDigs(num);
	*runer = '\0';
	--runer;
	
	while (num)
	{
		*runer = '0' + num % 10;
		--runer;
		num /= 10;
	}
	
	return str;
}

size_t NumOfDigs(int num)
{
	size_t counter = 0;
	
	while (num)
	{
		num /= 10;
		++counter;
	}
	
	return counter;
}

int MultBy8(int num)
{
	int sign = 0;
	
	if (num < 0)
	{
		sign = 1 << (sizeof(int) * CHAR_BIT - 1);
		num ^= sign;
	}
	
	return ((num << 3) | sign);
}

void SwapTwoInts1(int *a, int *b)
{
	*a = *a + *b;
	*b = *a - *b;
	*a = *a - *b;
}

void SwapTwoInts2(int *a, int *b)
{
	*a = *a * *b;
	*b = *a / *b;
	*a = *a / *b;
}

void SwapTwoInts3(int *a, int *b)
{
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}


