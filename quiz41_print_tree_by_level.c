
#include <stdio.h>
#include <stdlib.h>

typedef struct node node_t;
typedef struct qnode qnode_t;

struct node
{
	void *data;
	node_t *left;
	node_t *right;
};

typedef struct tree
{
	node_t *root;
} tree_t;

struct qnode
{
	void *data;
	qnode_t *next;
};

typedef struct queue
{
	size_t size;
	qnode_t *front;
	qnode_t *back;
} queue_t;

void LevelBlevelPrint(tree_t *tree, queue_t *queue);

node_t *CreateNewNode(void *data);
void CleanUp(node_t *node);

size_t QueueSize(queue_t *q);
int Enqueue(queue_t *q, void *data);
void *Dequeue(queue_t *q);
qnode_t *NewQnode(void *data);

int main(void)
{
	int arr[] = {1,2,3,4,5,6,7};
	tree_t tree = {NULL};
	queue_t q = {0, NULL, NULL};
	
	node_t *root = CreateNewNode(arr);
    root->left = CreateNewNode(arr + 1);
    root->right = CreateNewNode(arr + 2);
    root->left->left = CreateNewNode(arr + 3);
    root->left->right = CreateNewNode(arr + 4);
    root->right->left = CreateNewNode(arr + 5);
	root->right->right = CreateNewNode(arr + 6);
	
	tree.root = root;
	
	LevelBlevelPrint(&tree, &q);
	
	CleanUp(root);
	
	return 0;
}

void LevelBlevelPrint(tree_t *tree, queue_t *queue)
{
	node_t *root = tree->root;
	node_t *curr = NULL;
	
	Enqueue(queue, root);
	Enqueue(queue, NULL);
	
	while (1 < QueueSize(queue))
	{
		curr = Dequeue(queue);
		
		if (NULL == curr)
		{
			Enqueue(queue, NULL);
			printf("\n");
		}
		else
		{
			if (NULL != curr->left)
			{
				Enqueue(queue, curr->left);
			}
			
			if (NULL != curr->right)
			{
				Enqueue(queue, curr->right);
			}
			
			printf("%d,", *(int *)(curr->data));
		}
	}
	Dequeue(queue);
	printf("\n");
}

size_t QueueSize(queue_t *q)
{
	return (q->size);
}

int Enqueue(queue_t *q, void *data)
{	
	qnode_t *new_node = NewQnode(data);
	if (NULL == new_node)
	{
		return -1;
	}
	
	if (NULL == q->front)
	{
		q->front = q->back = new_node;
		++q->size;
		
		return 0;
	}
	
	q->back->next = new_node;
	q->back = new_node;
	++q->size;
	
	return 0;
}

void *Dequeue(queue_t *q)
{
	void *pop_data = NULL;
	
	if (0 < q->size)
	{
		qnode_t *temp = q->front;
		q->front = q->front->next;
		q->back = (NULL == q->front) ? NULL : q->back;
		--q->size;
		
		pop_data = temp->data;
		free(temp);
		temp = NULL;
	}
	
	return pop_data;
}

qnode_t *NewQnode(void *data)
{
	qnode_t *new_node = (qnode_t *)malloc(sizeof(qnode_t));
	if (NULL == new_node)
	{
		return NULL;
	}
	
	new_node->data = data;
	new_node->next = NULL;
	
	return new_node;
}

node_t *CreateNewNode(void *data)
{
	node_t *new_node = (node_t *)malloc(sizeof(node_t));
	if (NULL == new_node)
	{
		return NULL;
	}
	
	new_node->data = data;
	new_node->left = new_node->right = NULL;
	
	return new_node;
}

void CleanUp(node_t *node)
{
	if (NULL == node)
	{
		return;
	}
	
	CleanUp(node->left);
	CleanUp(node->right);
	
	free(node);
	node = NULL;	
}

