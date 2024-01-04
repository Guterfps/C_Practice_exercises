

#include <stdio.h>

typedef struct node node_t;

struct node
{
	int data;
	node_t *next;
};

int IsLoop(node_t *head);
void OpenLoop(node_t *head);
void PrintList(node_t *head);


int main(void)
{
	node_t head = {1, NULL};
	node_t node2 = {2, NULL};
	node_t node3 = {3, NULL};
	node_t node4 = {4, NULL};
	node_t node5 = {5, NULL};
	
	head.next = &node2;
	node2.next = &node3;
	node3.next = &node4;
	node4.next = &node5;
	
	!IsLoop(&head) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	node5.next = &head;
	IsLoop(&head) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	OpenLoop(&head);
	!IsLoop(&head) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	PrintList(&head);
	
	node5.next = &node3;
	IsLoop(&head) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	OpenLoop(&head);
	!IsLoop(&head) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	PrintList(&head);
	
	node5.next = &node5;
	IsLoop(&head) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	OpenLoop(&head);
	!IsLoop(&head) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	PrintList(&head);
	
	node5.next = &node4;
	IsLoop(&head) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	OpenLoop(&head);
	!IsLoop(&head) ? printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	PrintList(&head);
	
	return 0;
}

int IsLoop(node_t *head)
{
	node_t *slow = head;
	node_t *fast = head;
	
	if (NULL == head || NULL == head->next)
	{
		return 0;
	}
	
	fast = fast->next;
	
	while ((NULL != fast) && (NULL != fast->next) && (slow != fast))
	{
		slow = slow->next;
		fast = fast->next->next;
	}
	
	if (fast == slow)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void OpenLoop(node_t *head)
{
	node_t *temp_head = head;
	node_t *m_point = head;
	
	if (!IsLoop(head))
	{
		return;
	}
	
	m_point = m_point->next;
	
	while (temp_head != m_point)
	{
		temp_head = temp_head->next;
		m_point = m_point->next->next;
	}
	
	temp_head = head;
	
	while (temp_head != m_point->next)
	{
		temp_head = temp_head->next;
		m_point = m_point->next;
	}
	
	m_point->next = NULL;
}

void PrintList(node_t *head)
{
	while (NULL != head)
	{
		printf("%d, ", head->data);
		head = head->next;
	}
	printf("\n");
}

