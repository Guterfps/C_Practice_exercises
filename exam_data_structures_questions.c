
#include <stdio.h>
#include <stddef.h>
#include <assert.h>
#include <stdlib.h>

#define WORD_SIZE (sizeof(size_t))

typedef struct fsa
{
	size_t free_block;
} fsa_t;

typedef struct vsa
{
	size_t vsa_size;
} vsa_t;

typedef struct block
{
	size_t size;
} block_t;

typedef struct node Node;

struct node
{
	Node *next;
};

typedef struct sll_node sll_node_t;

struct sll_node
{
	void *data;
	sll_node_t *next;
};

typedef struct slist
{
	sll_node_t *first_node;
	sll_node_t *dummy;
} slist_t;

typedef struct dlist_node dlist_node_t;

struct dlist_node
{
	dlist_node_t *next;
	dlist_node_t *prev;
};

#define Q_SIZE 3

typedef struct Queue
{
	char m_queue[Q_SIZE];
	size_t m_elements_in_q;
	size_t m_first_element_index;
} q_t;

typedef struct point
{
	size_t x;
	size_t y;
} point_t;


void *FSAMalloc(fsa_t *fsa);
void FSAFree(fsa_t *fsa, void *block);
block_t *VSAMalloc(vsa_t *vsa, size_t block_size);
void VSAFree(block_t *block);
Node *Flip(Node *node);
int IsLoopInList(Node *head);
void OpenLoopInList(Node *head);
int IsIntersectionInLists(Node *list1, Node *list2);
void SeperateIntersection(Node *list1, Node *list2);
void *SLLRemove(sll_node_t *node);
dlist_node_t *DLLInsertBefore(dlist_node_t *node);
void DLLRemove(dlist_node_t *node);
int FindMissingNum(int *arr, size_t len);
int QueuePushChar(q_t *q, char c);
int QueuePopChar(q_t *q);
int IsInsideBitMapShape(size_t bitmap[5][5], point_t *point);

size_t AlignBlockSize(size_t block_size);
int IsEndOfVsa(vsa_t *vsa, block_t *block);
size_t GetBlockSize(block_t *block);
int IsBlockFree(block_t *block);
void SetBlockNotFree(block_t *block);
void SetNextBlock(vsa_t *vsa, block_t *block, size_t old_size);
block_t *GetNextBlock(block_t *block);
size_t SizeOfList(Node *list);
Node *MoveNode(Node *node, size_t steps);

int main(void)
{
	int arr[1024] = {0};
	size_t len = sizeof(arr) / sizeof(*arr);
	size_t i = 0;
	q_t cq = {0};
	point_t point1 = {0,1};
	point_t point2 = {3,1};
	size_t bitmap[5][5] = { {0,0,1,1,0},
							{0,1,0,0,1},
							{0,1,0,1,0},
							{0,1,1,0,0},
							{0,0,0,0,0} };
	
	for (; i < 25; ++i)
	{
		arr[i] = i;
	}
	for (; i < len; ++i)
	{
		arr[i] = i + 1;
	}
	
	printf("missing num: %d \n", FindMissingNum(arr, len));
	printf("char queue test: \n");
	
	(0 == QueuePushChar(&cq, 'a')) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	(0 == QueuePushChar(&cq, 'h')) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	(0 == QueuePushChar(&cq, 'i')) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	(-1 == QueuePushChar(&cq, 'i')) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	(0 == QueuePopChar(&cq)) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	(0 == QueuePopChar(&cq)) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	(0 == QueuePushChar(&cq, 'a')) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	(0 == QueuePushChar(&cq, 'a')) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	(-1 == QueuePushChar(&cq, 'a')) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	(0 == QueuePopChar(&cq)) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	(0 == QueuePopChar(&cq)) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	(0 == QueuePopChar(&cq)) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	(-1 == QueuePopChar(&cq)) ? 
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	printf("bitmap test: \n");
	(0 == IsInsideBitMapShape(bitmap, &point1)) ?
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	(1 == IsInsideBitMapShape(bitmap, &point2)) ?
	printf("SUCCESS ✅️\n") : printf("FAIL ❌️\n");
	
	return 0;
}

void *FSAMalloc(fsa_t *fsa)
{
	size_t next_free_block = 0;
	void *allocated_block = NULL;
	
	assert(NULL != fsa);
	
	if (0 == fsa->free_block)
	{
		return NULL;
	}
	
	allocated_block = (void *)((char *)fsa + fsa->free_block);
	next_free_block = *(size_t *)allocated_block;
	fsa->free_block = next_free_block;
	
	return allocated_block;
}

void FSAFree(fsa_t *fsa, void *block)
{
	size_t next_free_block = 0;
	
	assert(NULL != fsa);
	assert(NULL != block);
	
	next_free_block = fsa->free_block;
	*(size_t *)block = next_free_block;
	fsa->free_block = (size_t)block - (size_t)fsa;
}

block_t *VSAMalloc(vsa_t *vsa, size_t block_size)
{
	block_t *runner = NULL;
	
	assert(NULL != vsa);
	
	runner = (block_t *)((char *)vsa + sizeof(vsa_t));
	block_size = AlignBlockSize(block_size) + sizeof(block_t);
	
	while (!IsEndOfVsa(vsa, runner))
	{
		if (block_size <= GetBlockSize(runner) &&
			IsBlockFree(runner))
		{
			size_t old_size = GetBlockSize(runner);
			runner->size = block_size;
			SetBlockNotFree(runner);
			SetNextBlock(vsa, runner, old_size);
			
			return ((block_t *)((char *)runner + sizeof(block_t)));
		}
		runner = GetNextBlock(runner);
	}
	
	return NULL;
}

void VSAFree(block_t *block)
{
	assert(NULL != block);
	
	block->size = GetBlockSize(block);
}

size_t AlignBlockSize(size_t block_size)
{
	size_t reminder = block_size % WORD_SIZE;
	
	block_size += reminder ? (WORD_SIZE - reminder) : 0;
	
	return block_size;
}

int IsEndOfVsa(vsa_t *vsa, block_t *block)
{
	assert(NULL != vsa);
	assert(NULL != block);
	
	return (vsa->vsa_size >= ((size_t)block - (size_t)vsa));
}

size_t GetBlockSize(block_t *block)
{
	assert(NULL != block);
	
	return ((block->size & 1) ? (block->size - 1) : block->size);
}

int IsBlockFree(block_t *block)
{
	assert(NULL != block);
	
	return (!(block->size & 1));
}

void SetBlockNotFree(block_t *block)
{
	assert(NULL != block);
	
	block->size += 1;
}

block_t *GetNextBlock(block_t *block)
{
	assert(NULL != block);
	
	return ((block_t *)((char *)block + GetBlockSize(block)));
}

void SetNextBlock(vsa_t *vsa, block_t *block, size_t old_size)
{
	block_t *next_block = NULL;
	size_t next_block_size = 0;
	
	assert(NULL != block);
	assert(NULL != vsa);
	
	next_block = GetNextBlock(block);
	next_block_size = old_size - GetBlockSize(block);
	
	if (!IsEndOfVsa(vsa, next_block))
	{
		if (next_block_size > sizeof(block_t))
		{
			next_block->size = next_block_size;
		}
		else
		{
			block->size += sizeof(block_t);
		}
	}
}

Node *Flip(Node *node)
{
	Node *n_node = NULL;
	Node *p_node = NULL;
	
	while (NULL != node)
	{
		n_node = node->next;
		node->next = p_node;
		p_node = node;
		node = n_node;
	}
	
	return p_node;
}

int IsLoopInList(Node *head)
{
	Node *slow = NULL;
	Node *fast = NULL;
	
	assert(NULL != head);
	
	slow = head;
	fast = head->next->next;
	
	while (fast && fast->next && (fast != slow))
	{
		slow = slow->next;
		fast = fast->next->next;
	}
	
	return ((slow == fast) ? 1 : 0);
}

void OpenLoopInList(Node *head)
{
	Node *slow = NULL;
	Node *fast = NULL;
	
	assert(NULL != head);
	
	if (!IsLoopInList(head)) {return;}
	
	slow = head;
	fast = head->next;
	
	while (fast != slow)
	{
		slow = slow->next;
		fast = fast->next->next;
	}
	
	slow = head;
	
	while (fast->next != slow)
	{
		slow = slow->next;
		fast = fast->next;
	}
	
	fast->next = NULL;
}

int IsIntersectionInLists(Node *list1, Node *list2)
{
	size_t len1 = SizeOfList(list1);
	size_t len2 = SizeOfList(list2);
	size_t diff = 0;
	
	assert(NULL != list1);
	assert(NULL != list2);
	
	if (len1 > len2)
	{
		diff = len1 - len2;
		list1 = MoveNode(list1, diff);
	}
	else
	{
		diff = len2 - len1;
		list2 = MoveNode(list2, diff);
	}
	
	while ((NULL != list1) && (list1 != list2))
	{
		list1 = list1->next;
		list2 = list2->next;
	}
	
	return ((list1 == list2 ? 1 : 0));
}

void SeperateIntersection(Node *list1, Node *list2)
{
	size_t len1 = SizeOfList(list1);
	size_t len2 = SizeOfList(list2);
	size_t diff = 0;
	
	assert(NULL != list1);
	assert(NULL != list2);
	
	if (!IsIntersectionInLists(list1, list2)) {return;}
	
	if (len1 > len2)
	{
		diff = len1 - len2;
		list1 = MoveNode(list1, diff);
	}
	else
	{
		diff = len2 - len1;
		list2 = MoveNode(list2, diff);
	}
	
	while (list1->next != list2->next)
	{
		list1 = list1->next;
		list2 = list2->next;
	}
	
	list1->next = NULL;
}

size_t SizeOfList(Node *list)
{
	size_t counter = 0;
	
	while (NULL != list)
	{
		list = list->next;
		++counter;
	}
	
	return counter;
}

Node *MoveNode(Node *node, size_t steps)
{
	assert(NULL != node);
	
	while (steps--)
	{
		node = node->next;
	}
	
	return node;
}

void *SLLRemove(sll_node_t *node)
{
	void *data = NULL;
	sll_node_t *remove = NULL;
	
	assert(NULL != node);
	assert(NULL != node->next);
	
	remove = node->next;
	data = node->data;
	
	if (NULL == node->next->next)
	{
		((slist_t *)(remove->data))->dummy = node;
	}
	
	node->data = remove->data;
	node->next = remove->next;
	
	free(remove);
	remove = NULL;
	
	return data;
}

dlist_node_t *DLLInsertBefore(dlist_node_t *node)
{
	dlist_node_t *new_node = NULL;
	
	assert(NULL != node);
	
	new_node = (dlist_node_t *)malloc(sizeof(dlist_node_t));
	if (NULL == new_node)
	{
		return NULL;
	}
	
	new_node->next = node;
	new_node->prev = node->prev;
	
	node->prev->next = new_node;
	node->prev = new_node; 
	
	return new_node;
}

void DLLRemove(dlist_node_t *node)
{
	assert(NULL != node);
	
	node->prev->next = node->next;
	node->next->prev = node->prev;
	
	free(node);
	node = NULL;
}

int FindMissingNum(int *arr, size_t len)
{
	int xor_n = 0;
	int xor_arr = 0;
	size_t i = 0;
	
	assert(NULL != arr);
	
	for (; i < len; ++i)
	{
		xor_arr ^= arr[i];
	}
	
	for (i = 0; i < (len + 1); ++i)
	{
		xor_n ^= i;
	}
	
	return (xor_n ^ xor_arr);
}

int QueuePushChar(q_t *q, char c)
{
	size_t last_element_index = 0;
	
	assert(NULL != q);
	
	if (Q_SIZE == q->m_elements_in_q) 
	{
		return -1;
	}
	
	last_element_index = (q->m_first_element_index + q->m_elements_in_q) 
							% Q_SIZE;
	q->m_queue[last_element_index] = c;
	q->m_elements_in_q += 1;
	
	return 0;
}

int QueuePopChar(q_t *q)
{
	assert(NULL != q);
	
	if (0 == q->m_elements_in_q) 
	{
		return -1;
	}
	
	q->m_first_element_index = (q->m_first_element_index + 1) % Q_SIZE;
	q->m_elements_in_q -= 1;
	
	return 0;
}

int IsInsideBitMapShape(size_t bitmap[5][5], point_t *point)
{
	size_t counter = 0;
	int i = point->x;
	int status = 1;
	
	assert(NULL != bitmap);
	assert(NULL != point);
	
	for (; i < 5; ++i)
	{
		counter += bitmap[point->y][i];
	}
	
	status &= (counter & 1);
	counter = 0;
	
	for (i = point->x; i >= 0; --i)
	{
		counter += bitmap[point->y][i];
	}
	status &= (counter & 1);
	
	return status;
}

