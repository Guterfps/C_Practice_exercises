#include <stdio.h>
#include <stddef.h>

#define WORD_SIZE sizeof(void *)

void *MemCpy(void *dest, const void * src, size_t n);

int main(void)
{
	const char *str = "ah yakar ahiiiii";
	char str_dest[100] = {0};
	
	MemCpy(str_dest, str + 3,10);
	
	printf("%s\n", str_dest);
	
	
	
	return 0;
}


void *MemCpy(void *dest, const void * src, size_t n)
{
	unsigned char *temp_dest = (unsigned char *)dest;
	unsigned char *temp_src = (unsigned char *)src;

	
	while (WORD_SIZE <= n)
	{
		*(size_t *)temp_dest = *(size_t *)temp_src;
		temp_dest += WORD_SIZE;
		temp_src += WORD_SIZE;
		n -= WORD_SIZE;
	}
	
	while (n > 0)
	{
		*temp_dest = *temp_src;
		++temp_dest;
		++temp_src;
		--n;
	}
	
	return dest;
}



