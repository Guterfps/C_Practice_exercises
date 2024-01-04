
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int IsBraketsBalanced(const char *str);
int IsCharMach(char c1, char c2);

int main(void)
{
	char *str1 = "[()](){[()]}";
	char *str2 = "[{}(])";
	char *str3 = "[x * (y+5)]";
	char *str4 = "{(a-6) / [b-8]}";
	char *str5 = "}(n){";
	
	IsBraketsBalanced(str1) ? printf("Balanced\n") : printf("not Balanced\n");
	IsBraketsBalanced(str2) ? printf("Balanced\n") : printf("not Balanced\n");
	IsBraketsBalanced(str3) ? printf("Balanced\n") : printf("not Balanced\n");
	IsBraketsBalanced(str4) ? printf("Balanced\n") : printf("not Balanced\n");
	IsBraketsBalanced(str5) ? printf("Balanced\n") : printf("not Balanced\n");
	
	return 0;
}

int IsBraketsBalanced(const char *str)
{
	char *stack = (char *)calloc(strlen(str), sizeof(char));
	size_t top = 0;
	size_t i = 0;
	
	if (NULL == stack)
	{
		return -1;
	} 
	
	while ('\0' != str[i])
	{
		if (str[i] == '{' || str[i] == '[' || str[i] == '(')
		{
			++top;
			stack[top] = str[i];
		}
		
		if (str[i] == '}' || str[i] == ']' || str[i] == ')')
		{
			if (!IsCharMach(stack[top], str[i]))
			{
				free(stack);
				stack = NULL;
				return 0;
			}
			stack[top] = 0;
			--top;
		}
		++i;
	}
	
	if ((0 == stack[0]) && (0 == top))
	{
		free(stack);
		stack = NULL;
		return 1;
	}
	else
	{
		free(stack);
		stack = NULL;
		return 0;
	}
}

int IsCharMach(char c1, char c2)
{
	if ('(' == c1 && ')' == c2)
	{
		return 1;
	}
	else if ('[' == c1 && ']' == c2)
	{
		return 1;
	}
	else if ('{' == c1 && '}' == c2)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
