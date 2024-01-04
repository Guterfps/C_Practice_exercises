#include <stdio.h>
#include <ctype.h>
#include <stddef.h>

#define MAX3(a, b, c) ( (a > b) && (a > c) ? a : (b > c ? b : c) )
#define TO_LOWER(a) ( islower(a) ? a : tolower(a) )
#define OFFSET(s, f) ( offsetof(s, f) )

typedef struct
{
	char c;
	void *ptr;
	int x;
	double d;
} str_t;

int main()
{
	printf("MAX3(10, 15, 5) : %d \n",  MAX3(10, 15, 5));
	printf("TO_LOWER(B)  : %c \n",  TO_LOWER('B'));
	printf("OFFSET(str_t, c)  : %ld \n",  OFFSET(str_t, c));
	printf("OFFSET(str_t, x)  : %ld \n",  OFFSET(str_t, x));
	printf("OFFSET(str_t, d)  : %ld \n",  OFFSET(str_t, d));
	printf("OFFSET(str_t, ptr)  : %ld \n",  OFFSET(str_t, ptr));
	
	
	return 0;
}
