
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "stack.h"

#define NUM_OF_CHARS 985084

typedef struct node Node;
typedef struct tree_node node_t;

struct node
{
	void *data;
	Node *next;
};

enum children
{
	LEFT = 0,
	RIGHT,
	NUM_OF_CHILDREN
};

struct tree_node
{
	int data;
	node_t *child[NUM_OF_CHILDREN];
};

Node *IterFlip(Node *node);
Node *RecFlip(Node *node);
int MaxSubArr(int *arr, size_t size, size_t *start, size_t *end);
void RecStackSort(stack_t *stack);
void RecStackSortInsert(stack_t *stack, int *data);
int sort_chars_in_file(const char *file_name, char *result);
int CmpFunc(const void *a, const void *b);
int IterInsert(node_t *root, int data);
node_t *RecInsert(node_t *root, int data);
void ArrInsert(int *tree, size_t size, int data);
void ReverseSrt(char *start, char *end);
void StrPermutations(char *str, size_t l, size_t r);

node_t *NewNode(int data);
void Swap(char *a, char *b);

void FlipListTest(void);
void SortStackTest(void);

int main(void)
{
	int arr[] = {-2,1,-3,4,-1,2,1,-5,4};
	size_t size = sizeof(arr) / sizeof(*arr);
	size_t start = 0;
	size_t end = 0;
	const char *file = "/usr/share/dict/american-english";
	char result[NUM_OF_CHARS] = {0};
	size_t i = 0;
	int status = 1;
	char str[] = "ah yakar";
	char perm[] = "ahi";
	
	FlipListTest();
	printf("\n");
	
	printf("max sub array test:	");
	(6 == MaxSubArr(arr, size, &start, &end)) ? 
	printf("SUCCESS ✅️,") : printf("FAIL ❌️,");
	(3 == start) ? 
	printf("SUCCESS ✅️,") : printf("FAIL ❌️,");
	(6 == end) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("\n");
	
	SortStackTest();
	printf("\n");
	
	printf("sort chars in file:	");
	sort_chars_in_file(file, result);
	
	for (; (i < NUM_OF_CHARS - 1) && status; ++i)
	{
		status = (result[i] <= result[i + 1]);
	}
	
	status ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	printf("\n");
	
	printf("reverse string test:\n");
	printf("string before: %s\n", str);
	ReverseSrt(str, str + sizeof(str) - 2);
	printf("string after: %s\n", str);
	printf("\n");
	
	printf("permutations test: ");
	StrPermutations(perm, 0, sizeof(perm) - 2);
	printf("\n");
	
	return 0;
}

Node *IterFlip(Node *node)
{
	Node *prev = NULL;
	Node *next = NULL;
	
	while (NULL != node)
	{
		next = node->next;
		node->next = prev;
		prev = node;
		node = next;
	}
	
	return prev;
}

Node *RecFlip(Node *node)
{
	Node *rest_of_list = NULL;
	
	if (NULL == node->next)
	{
		return node;
	}
	
	rest_of_list = RecFlip(node->next);
	node->next->next = node;
	node->next = NULL;
	
	return rest_of_list;
}

int MaxSubArr(int *arr, size_t size, size_t *start, size_t *end)
{
	int max_so_far = INT_MIN;
	int max_end_here = 0;
	size_t i = 0;
	size_t s = 0;
	
	for (; i < size; ++i)
	{
		max_end_here += arr[i];
		
		if (max_so_far < max_end_here)
		{
			max_so_far = max_end_here;
			*start = s;
			*end = i;
		}
		
		if (max_end_here < 0)
		{
			max_end_here = 0;
			s = i + 1;
		}
	}
	
	return max_so_far;
}

void RecStackSort(stack_t *stack)
{	
	int *top = NULL;
	
	if (StackIsEmpty(stack))
	{
		return;
	}
	
	top = (int *)StackPop(stack);
	RecStackSort(stack);
	RecStackSortInsert(stack, top);
}

void RecStackSortInsert(stack_t *stack, int *data)
{
	int *element = NULL;
	
	if (StackIsEmpty(stack) || (*data >= *(int *)StackPeek(stack)))
	{
		StackPush(stack, data);
		return;
	}
	
	element = (int *)StackPop(stack);
	RecStackSortInsert(stack, data);
	StackPush(stack, element);
}

int sort_chars_in_file(const char *file_name, char *result)
{
	FILE *f = NULL;
	size_t fsize = 0;
	
	f = fopen(file_name, "rb");
	if (NULL == f)
	{
		return -1;
	}
	
	fseek(f, 0, SEEK_END);
	fsize = ftell(f);
	fseek(f, 0, SEEK_SET);
	fread(result, fsize, 1, f);
	fclose(f);
	
	qsort(result, fsize, sizeof(char), &CmpFunc);
	
	return 0;
}

int CmpFunc(const void *a, const void *b)
{
	return (*(char *)a - *(char *)b);
}

int IterInsert(node_t *root, int data)
{
	node_t *new_node = NULL;
	node_t *prev = NULL;
	node_t *temp = NULL;
	size_t child = 0;
	
	new_node = NewNode(data);
	if (NULL == new_node)
	{
		return -1;
	}
	
	temp = root;
	
	while (NULL != temp)
	{
		child = temp->data < data;
		prev = temp;
		temp = temp->child[child];
	}
	
	child = prev->data < data;
	prev->child[child] = new_node;
	
	return 0;
}

node_t *RecInsert(node_t *root, int data)
{
	size_t child = 0;
	
	if (NULL == root)
	{
		return NewNode(data);
	}
	
	child = root->data < data;
	root->child[child] = RecInsert(root->child[child], data);
	
	return root;
}

void ArrInsert(int *tree, size_t size, int data)
{
	size_t i = 0;
	
	while ((i < size) && (0 != tree[i]))
	{
		i = (tree[i] > data) ? i * 2 + 1 : i * 2 + 2;
	}
	
	if (i < size)
	{
		tree[i] = data;
	}
}

node_t *NewNode(int data)
{
	node_t *new_node = (node_t *)malloc(sizeof(node_t));
	if (NULL == new_node)
	{
		return NULL;
	}
	
	new_node->data = data;
	new_node->child[LEFT] = new_node->child[RIGHT] = NULL;
	
	return new_node;
}

void ReverseSrt(char *start, char *end)
{
	if (start < end)
	{
		Swap(start, end);
		ReverseSrt(start + 1, end - 1);
	}
}

void StrPermutations(char *str, size_t l, size_t r)
{
	size_t i = 0;
	
	if (l == r)
	{
		printf("%s,", str);
	}
	else
	{
		for (i = l; i <= r; ++i)
		{
			Swap(str + l, str + i);
			StrPermutations(str, l + 1, r);
			Swap(str + l, str + i);
		}
	}
}

void Swap(char *a, char *b)
{
	char temp = *a;
	*a = *b;
	*b = temp;
}

void FlipListTest(void)
{
	Node head = {NULL};
	Node node1 = {NULL}, node2 = {NULL}, node3 = {NULL};
	
	head.next = &node1;
	node1.next = &node2;
	node2.next = &node3;
	node3.next = NULL;
	
	printf("recursive tests: \n");
	printf("Flip list test1:	");
	(&node3 == RecFlip(&node3)) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("Flip list test2:	");
	(&node3 == RecFlip(&head)) ? 
	printf("SUCCESS ✅️,") : printf("FAIL ❌️,");
	(NULL == head.next) ? printf("SUCCESS ✅️,") : printf("FAIL ❌️,");
	(&node1 == node2.next) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("Flip list test3:	");
	(&head == RecFlip(&node3)) ? 
	printf("SUCCESS ✅️,") : printf("FAIL ❌️,");
	(NULL == node3.next) ? printf("SUCCESS ✅️,") : printf("FAIL ❌️,");
	(&node2 == node1.next) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	head.next = &node1;
	node1.next = &node2;
	node2.next = &node3;
	node3.next = NULL;
	
	printf("iterative tests: \n");
	printf("Flip list test1:	");
	(&node3 == IterFlip(&node3)) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("Flip list test2:	");
	(&node3 == IterFlip(&head)) ? 
	printf("SUCCESS ✅️,") : printf("FAIL ❌️,");
	(NULL == head.next) ? printf("SUCCESS ✅️,") : printf("FAIL ❌️,");
	(&node1 == node2.next) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("Flip list test3:	");
	(&head == IterFlip(&node3)) ? 
	printf("SUCCESS ✅️,") : printf("FAIL ❌️,");
	(NULL == node3.next) ? printf("SUCCESS ✅️,") : printf("FAIL ❌️,");
	(&node2 == node1.next) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
}

void SortStackTest(void)
{
	stack_t *stack = NULL;
	int arr[] = {1, 0 ,-1, 3, 7, 25, 420, 3, 123, 0};
	size_t len = sizeof(arr) / sizeof(*arr);
	size_t i = 0;
	int status = 1;
	
	stack = StackCreate(len);
	
	for (i = 0; i < len; ++i)
	{
		StackPush(stack, arr + i);
	}
	
	RecStackSort(stack);
	
	for(i = 0; (i < len - 1) && status; ++i)
	{
		status = (*(int *)StackPop(stack) >= *(int *)StackPeek(stack));
	}
	
	printf("sort stack test:	");
	status ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	StackDestroy(stack);
	stack = NULL;
}

