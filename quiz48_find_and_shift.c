
#include <stdio.h>
#include <stddef.h>
#include <string.h>

#define WORD_SIZE (sizeof(size_t))

int FindChar(char *arr, size_t len, char c);
char *NCircShift(char *arr, size_t len, size_t n);

int main(void)
{
	char arr[] = "ahi";
	char arr2[] = {'a','h',' ','y','a','k','a','r'};
	
	printf("find char:	");
	FindChar(arr, sizeof(arr), 'a') ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("find char:	");
	FindChar(arr, sizeof(arr), 'h') ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("find char:	");
	FindChar(arr, sizeof(arr), 'i') ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("find char:	");
	!FindChar(arr, sizeof(arr), 't') ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("\nshift arr of chars: %s%c", arr2, '\0');
	NCircShift(arr2, sizeof(arr2), 2);
	printf(" => %s%c ", arr2, '\0');
	printf("\nshift arr of chars: %s%c", arr2, '\0');
	NCircShift(arr2, sizeof(arr2), 8);
	printf(" => %s%c ", arr2, '\0');
	printf("\nshift arr of chars: %s%c", arr2, '\0');
	NCircShift(arr2, sizeof(arr2), 20);
	printf(" => %s%c ", arr2, '\0');
	printf("\nshift arr of chars: %s%c", arr2, '\0');
	NCircShift(arr2, sizeof(arr2), 2);
	printf(" => %s%c ", arr2, '\0');
	printf("\n");
	
	return 0;
}

int FindChar(char *arr, size_t len, char c)
{
	int status = 1;
	
	while (len--)
	{
		status *= *arr++ ^ c;
	}
	
	return !status;
}

char *NCircShift(char *arr, size_t len, size_t n)
{
	size_t temp = 0;
	
	n %= len;
	
	while (WORD_SIZE <= n)
	{
		temp = *(size_t *)arr;
		memmove(arr, arr + WORD_SIZE, len - WORD_SIZE);
		memcpy(arr + len - WORD_SIZE, &temp, WORD_SIZE);
		n -= WORD_SIZE;
	}
	
	while (n--)
	{
		char c = *arr;
		memmove(arr, arr + 1, len - 1);
		*(arr + len - 1) = c;
	}
	
	return arr;
}

