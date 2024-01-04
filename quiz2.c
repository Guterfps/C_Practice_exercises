#include<stdio.h>
#include<string.h>
#include<ctype.h>

void ReverseInPlace(char *str);
void TF(int num);

int main()
{
	char test[] = "Hello world";
	
	TF(30);
	printf("reverse before : %s \n", test);
	ReverseInPlace(test);
	printf("reverse after : %s \n", test);
	
	return 0;
}


void ReverseInPlace(char *str)
{
	char *start = str;
	int null_char = 1;
	char *end = str + strlen(str) - null_char;
	char temp = '\0';
	
	while (start < end)
	{
		temp = *start;
		*start = tolower(*end);
		*end = tolower(temp);
		++start;
		--end;
	}
}

void TF(int num)
{
	int counter = 1;
	
	while (counter <= num)
	{
		if (0 == counter % 15)
		{
			printf("TF\n");
		}
		else if (0 == counter % 3)
		{
			printf("T\n");
		}
		else if (0 == counter % 5)
		{
			printf("F\n");
		}
		else
		{
			printf("%d\n", counter);
		}
		++counter;
	}
}


