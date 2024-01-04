
#include <stdio.h>		/*printf()*/
#include <assert.h>		/*assert()*/
#include <stdlib.h>		/*malloc()*/

typedef struct node
{
	void *data;
	struct node *next;
} node_t;

node_t *PushNode(node_t *head, void *data);
void DestroyList(node_t *head);
void PrintList(node_t *head);

node_t *FindNthElementFromLast(node_t *head, size_t n);

size_t CountList(node_t *head);

int main(void)
{
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	node_t *head = NULL;
	node_t *test_node = NULL;

	
	head = PushNode(head, &d);
	PushNode(head, &c);
	PushNode(head, &b);
	test_node = PushNode(head, &a);

	PrintList(head);
	printf("%d\n", *(int *)test_node->data);
	(test_node == FindNthElementFromLast(head, 3)) ? 
	printf("SUCCESS\n") : printf("FAIL\n");
	
	(d == *(int *)FindNthElementFromLast(head, 1)->data) ? 
	printf("SUCCESS\n") : printf("FAIL\n");
	(c == *(int *)FindNthElementFromLast(head, 2)->data) ? 
	printf("SUCCESS\n") : printf("FAIL\n");
	(a == *(int *)FindNthElementFromLast(head, 4)->data) ? 
	printf("SUCCESS\n") : printf("FAIL\n");

	DestroyList(head);
	
	return 0;
}

node_t *FindNthElementFromLast(node_t *head, size_t n)
{
	node_t *runner = head;
	size_t counter = CountList(head) - n;
	
	while (counter--)
	{
		runner = runner->next;
	}
	
	return runner;
}


node_t *PushNode(node_t *head, void *data)
{
	node_t *new_node = NULL;
	
	assert(NULL != data);
	
	new_node = (node_t *)malloc(sizeof(node_t));
	if (NULL == new_node)
	{
		return NULL;
	}
	
	if (NULL == head)
	{
		new_node->data = data;
		new_node->next = NULL;
	}
	else
	{
		new_node->data = head->data;
		new_node->next = head->next;
		head->data = data;
		head->next = new_node;
	}
	
	return new_node;
}

void DestroyList(node_t *head)
{
	node_t *temp_node = NULL;
	
	assert(NULL != head);
	
	while (NULL != head)
	{
		temp_node = head;
		head = head->next;
		free(temp_node);
		temp_node = NULL;
	}
}

size_t CountList(node_t *head)
{
	size_t counter = 0;
	node_t *runer = NULL;
	
	assert(NULL != head);
	
	runer = head;
	
	while (NULL != runer)
	{
		++counter;
		runer = runer->next;
	}

	return counter;
}

void PrintList(node_t *head)
{
	assert(NULL != head);
	
	while (NULL != head)
	{
		printf("%d", *(int *)(head->data));
		head = head->next;
	}
	printf("\n");
}
