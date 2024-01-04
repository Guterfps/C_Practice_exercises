
#include <stdio.h>
#include <stdlib.h>

void *AlignedMalloc(size_t bytes, size_t align);
void AlignedFree(void *ptr);

int main(void)
{
	int *test1 = NULL;
	int *test2 = NULL;
	int *test3 = NULL;
	int *test4 = NULL;
	
	printf("test1:	");
	test1 = AlignedMalloc(10, 2);
	(0 == ((size_t)test1 % 2)) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("test2:	");
	test2 = AlignedMalloc(5, 8);
	(0 == ((size_t)test2 % 8)) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("test3:	");
	test3 = AlignedMalloc(50, 16);
	(0 == ((size_t)test3 % 16)) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("test4:	");
	test4 = AlignedMalloc(100, 32);
	(0 == ((size_t)test4 % 32)) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	AlignedFree(test1);
	AlignedFree(test2);
	AlignedFree(test3);
	AlignedFree(test4);
	
	return 0;
}

void *AlignedMalloc(size_t bytes, size_t align)
{
	size_t *user_p = NULL;
	size_t *malloc_p = NULL;
	size_t offset = align + sizeof(size_t);
	size_t address = 0;
	
	malloc_p = (size_t *)malloc(bytes + offset);
	if (NULL == malloc_p)
	{
		return NULL;
	}
	
	address = (size_t)malloc_p + offset;
	user_p = (size_t *)(address - (address & (align - 1)));
	*(user_p - 1) = (size_t)malloc_p;
	
	return user_p;
}

void AlignedFree(void *ptr)
{
	free((void *)(*((size_t *)ptr - 1)));
}

