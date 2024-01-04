#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int IsRotation(char *s1, char *s2);
void ShiftLeft(char *str);

int main()
{
	char str1[] = "121234";
	char str2[] = "121234";
	
	printf("is raotation : %d \n", IsRotation(str1, str2));
	
	return 0;
}


int IsRotation(char *s1, char *s2)
{
	char *rotating = s1;
	size_t counter = 0;
	
	while (counter < strlen(s1))
	{
		if (0 == strcmp(rotating, s2))
		{
			return 1;
		}
		ShiftLeft(rotating);
		++counter;
	}
	
	return 0;
}


void ShiftLeft(char *str)
{
	char shift = *str;
	char *temp = str;
	
	while ('\0' != *temp)
	{
		*temp = *(temp + 1);
		++temp;
	}
	*(temp - 1) = shift;
}


