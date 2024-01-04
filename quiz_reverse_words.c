#include <stdio.h>

char *ReverseWords(char *str);
void Reverse(char* begin, char* end);

int main()
{
	char str[] = "I am a student";
	
	printf("reverse words in string: %s\n", ReverseWords(str));
	
	return 0;
}

char *ReverseWords(char *str)
{
   char *word_begin = NULL;
   char *temp = str;
 
    while ('\0' != *temp)
    {
        if ((NULL == word_begin) && (' ' != *temp))
        {
            word_begin = temp;
        }
        if (word_begin && ((' ' == *(temp + 1)) || ('\0' == *(temp + 1))))
        {
            Reverse(word_begin, temp);
            word_begin = NULL;
        }
        ++temp;
    }
    Reverse(str, temp - 1);
    
    return str;
}

void Reverse(char *begin, char *end)
{   
    while (begin < end) 
    {
        *begin = *begin ^ *end;
        *end = *begin ^ *end;
        *begin = *begin ^ *end;
        ++begin;
        --end;
    }
}
