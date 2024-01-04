
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Check2And6(unsigned char c);
int Check2Or6(unsigned char c);
void Swap3_5(unsigned char *c);
void SwapInts(int *a, int *b);
void SwapPInts(int **a, int **b);
void SwapPVoids(void **a, void **b);
int *CreateArr(size_t size);
int **CreateMat(size_t row, size_t col);
void ResetArr(int *arr, size_t size);
void ResetMat(int **mat, size_t row, size_t col);

void FreeLoop(int **mat, size_t n);

int main(void)
{
	unsigned char c1 = 42;
	unsigned char c2 = 40;
	unsigned char c3 = 10;
	unsigned char c4 = 8;
	unsigned char c5 = 62;
	unsigned char c6 = 58;
	unsigned char c7 = 46;
	int a = 1;
	int b = 2;
	int *p1 = &a;
	int *p2 = &b;
	void *p3 = &p1;
	void *p4 = &p2;
	int *arr = NULL;
	size_t size = 10;
	size_t i = 0;
	int status = 1;
	int **mat = NULL;
	size_t j = 0;
	
	printf("Check2And6 test:	");
	Check2And6(c1) ? printf("SUCCESS ✅️,") : printf("FAIL ❌️,");
	!Check2And6(c2) ? printf("SUCCESS ✅️,") : printf("FAIL ❌️,");
	!Check2And6(c3) ? printf("SUCCESS ✅️,") : printf("FAIL ❌️,");
	!Check2And6(c4) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("Check2Or6 test:		");
	Check2Or6(c1) ? printf("SUCCESS ✅️,") : printf("FAIL ❌️,");
	Check2Or6(c2) ? printf("SUCCESS ✅️,") : printf("FAIL ❌️,");
	Check2Or6(c3) ? printf("SUCCESS ✅️,") : printf("FAIL ❌️,");
	!Check2Or6(c4) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("Swap3_5 test:\n");
	printf("before swap: %d, ", c1);
	Swap3_5(&c1);
	printf("after swap: %d\n", c1);
	printf("before swap: %d, ", c5);
	Swap3_5(&c5);
	printf("after swap: %d\n", c5);
	printf("before swap: %d, ", c6);
	Swap3_5(&c6);
	printf("after swap: %d\n", c6);
	printf("before swap: %d, ", c7);
	Swap3_5(&c7);
	printf("after swap: %d\n", c7);
	
	printf("SwapInts test:\n");
	printf("before swap: a = %d and b = %d, ", a, b);
	SwapInts(&a, &b);
	printf("after swap: a = %d and b = %d\n", a, b);
	
	printf("SwapPInts test:\n");
	printf("before swap: p1 points to %d and p2 points to %d\n", *p1, *p2);
	SwapPInts(&p1, &p2);
	printf("after swap: p1 points to %d and p2 points to %d\n", *p1, *p2);
	
	printf("SwapPVoids test:\n");
	printf("before swap: p3 = %p and p4 = %p\n", p3, p4);
	SwapPVoids(&p3, &p4);
	printf("after swap: p3 = %p and p4 = %p\n", p3, p4);
	
	printf("create and set arr test:	");
	arr = CreateArr(size);
	for (; i < size; ++i)
	{
		arr[i] = i;
	}
	
	ResetArr(arr, size);
	for (i = 0; (i < size) && status; ++i)
	{
		status = !arr[i];
	}
	
	status ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("create and set matrix test:	");
	mat = CreateMat(size, size);
	for (i = 0; i < size; ++i)
	{
		for (j = 0; j < size; ++j)
		{	
			mat[i][j] = i + j;
		}
	}
	
	ResetMat(mat, size, size);
	for (i = 0; i < size && status; ++i)
	{
		for (j = 0; (j < size) && status; ++j)
		{
			status = !mat[i][j];
		}
	}
	
	status ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	free(arr);
	FreeLoop(mat, size);
	free(mat);
	
	return 0;
}

int Check2And6(unsigned char c)
{
	return ((c & (1 << 1)) && (c & (1 << 5)));
}

int Check2Or6(unsigned char c)
{
	return ((c & (1 << 1)) || (c & (1 << 5)));
}

void Swap3_5(unsigned char *c)
{
	unsigned char bit1 =  (*c >> 2) & 1;
	unsigned char bit2 =  (*c >> 4) & 1;
	unsigned char x = (bit1 ^ bit2);

	x = (x << 2) | (x << 4);
	*c ^= x;
}

void SwapInts(int *a, int *b)
{
	if (a != b)
	{
		*a ^= *b;
		*b ^= *a;
		*a ^= *b;
	}
}

void SwapPInts(int **a, int **b)
{
	if (a != b)
	{
		*(size_t *)a ^= *(size_t *)b;
		*(size_t *)b ^= *(size_t *)a;
		*(size_t *)a ^= *(size_t *)b;
	}
}

void SwapPVoids(void **a, void **b)
{
	SwapPInts((int **)a, (int **)b);
}

int *CreateArr(size_t size)
{
	int *new_arr = (int *)malloc(size * sizeof(int));
	
	return new_arr;
}

int **CreateMat(size_t row, size_t col)
{
	size_t i = 0;
	int **new_mat = (int **)malloc(row * sizeof(int *));
	if (NULL == new_mat)
	{
		return NULL;
	}
	
	for (; i < row; ++i)
	{
		new_mat[i] = (int *)malloc(col * sizeof(int));
		if (NULL == new_mat[i])
		{
			FreeLoop(new_mat, i);
			free(new_mat);
			new_mat = NULL;
			return NULL;
		}
	}
	
	return new_mat;
}

void FreeLoop(int **mat, size_t n)
{
	size_t i = 0;
	
	for (; i < n; ++i)
	{
		free(mat[i]);
		mat[i] = NULL;
	}
}

void ResetArr(int *arr, size_t size)
{
	memset(arr, 0, size * sizeof(int));
}

void ResetMat(int **mat, size_t row, size_t col)
{
	size_t i = 0;
	
	for (; i < row; ++i)
	{
		memset(mat[i], 0, col * sizeof(int));
	}
}
