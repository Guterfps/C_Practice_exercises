
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

typedef struct min_stack min_stack_t;

struct min_stack
{
	stack_t *min_stack;
	stack_t *num_stack;
};

min_stack_t *MinStackCreate(size_t capacity);
void MinStackDestroy(min_stack_t *stack);
void MinStackPush(min_stack_t *stack, int *num);
int MinStackPop(min_stack_t *stack);
int GetMinValue(min_stack_t *stack);
int MinStackPeek(min_stack_t *stack);

int main(void)
{
	int arr[] = {5 ,1, -3, 2, -10, 10, 0, 1, 25};
	size_t i = 0;
	size_t len = sizeof(arr) / sizeof(*arr);
	min_stack_t *min_stack = MinStackCreate(20);
	
	printf("push test: \n\n");
	for (; i < len; ++i)
	{
		MinStackPush(min_stack, arr + i);
		printf("peek stack: %d\n", MinStackPeek(min_stack));
		printf("min value in stack: %d\n", GetMinValue(min_stack));
	}
	
	printf("\n\n pop test: \n\n");
	for (; i > 0; --i)
	{
		printf("peek stack: %d\n", MinStackPeek(min_stack));
		printf("min value in stack: %d\n", GetMinValue(min_stack));
		MinStackPop(min_stack);
	}
	
	MinStackDestroy(min_stack);
	
	return 0;
}

min_stack_t *MinStackCreate(size_t capacity)
{
	min_stack_t *new_stack = (min_stack_t *)malloc(sizeof(min_stack_t));
	if (NULL == new_stack)
	{
		return NULL;
	}
	
	new_stack->min_stack = StackCreate(capacity);
	new_stack->num_stack = StackCreate(capacity);
	
	return new_stack;
}

void MinStackDestroy(min_stack_t *stack)
{
	StackDestroy(stack->num_stack);
	StackDestroy(stack->min_stack);
	free(stack);
	stack = NULL;
}

void MinStackPush(min_stack_t *stack, int *num)
{
	if (StackIsEmpty(stack->num_stack))
	{
		StackPush(stack->min_stack, num);
	}
	else if(*(int *)StackPeek(stack->min_stack) > *num)
	{
		StackPush(stack->min_stack, num);
	}
	
	StackPush(stack->num_stack, num);
}

int MinStackPop(min_stack_t *stack)
{
	int pop_num = *(int *)StackPop(stack->num_stack);
	
	if (*(int *)StackPeek(stack->min_stack) == pop_num)
	{
		StackPop(stack->min_stack);
	}
	
	return pop_num;
}

int GetMinValue(min_stack_t *stack)
{
	return (*(int *)StackPeek(stack->min_stack));
}

int MinStackPeek(min_stack_t *stack)
{
	return (*(int *)StackPeek(stack->num_stack));
}


