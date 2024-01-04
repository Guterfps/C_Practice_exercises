
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

node_t *FindIntersection(node_t *head_1, node_t *head_2);
size_t CountList(node_t *head);
node_t *SeparateIntersection(node_t *head1, node_t *head2);

int main(void)
{
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	int num1 = 1;
	int num2 = 2;
	node_t *head1 = NULL;
	node_t *head2 = NULL;
	node_t *test_node = NULL;
	node_t *test_intersection = NULL;
	
	head1 = PushNode(head1, &a);
	PushNode(head1, &b);
	test_node = PushNode(head1, &c);
	PushNode(head1, &d);
	
	head2 = PushNode(head2, &num2);
	PushNode(head2, &num1);
	test_intersection = FindIntersection(head1, head2);
	printf("intersection: ");
	(NULL == test_intersection) ? printf(" SUCCESS\n") : 
								  printf(" FAIL\n");
	head2->next->next = test_node;
	test_intersection = FindIntersection(head1, head2);
	PrintList(head1);
	PrintList(head2);
	printf("intersection: ");
	(test_intersection == test_node) ? printf(" SUCCESS\n") : 
										printf(" FAIL\n");
	
	SeparateIntersection(head1, head2);
	PrintList(head1);
	PrintList(head2);
	test_intersection = FindIntersection(head1, head2);
	printf("intersection: ");
	(NULL == test_intersection) ? printf(" SUCCESS\n") : 
								  printf(" FAIL\n");

	DestroyList(head1);
	DestroyList(head2);
	
	return 0;
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

node_t *FindIntersection(node_t *head_1, node_t *head_2)
{
	size_t counter1 = 0;
	size_t counter2 = 0;
	size_t dif = 0;
	node_t *long_list = NULL;
	node_t *Short_list = NULL;
	
	assert(NULL != head_1);
	assert(NULL != head_2);
	
	counter1 = CountList(head_1);
	counter2 = CountList(head_2);
	
	if (counter1 > counter2)
	{
		dif = counter1 - counter2;
		long_list = head_1;
		Short_list = head_2;
	}
	else
	{
		dif = counter2 - counter1;
		long_list = head_2;
		Short_list = head_1;
	}
	
	while (0 != dif)
	{
		long_list = long_list->next;
		--dif;
	}
	
	while ((NULL != long_list) && (long_list != Short_list))
	{
		long_list = long_list->next;
		Short_list = Short_list->next;
	}
	
	return long_list;
}

node_t *SeparateIntersection(node_t *head1, node_t *head2)
{
	node_t *intersection = NULL;
	
	assert(NULL != head1);
	assert(NULL != head2);
	
	intersection = FindIntersection(head1, head2);
	
	while (head1->next != intersection)
	{
		head1 = head1->next;
	}
	
	head1->next = NULL;
	
	return head1;
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
