
#include <stdio.h>
#include <stdlib.h>

typedef struct node node_t;

struct node
{
	void *data;
	node_t *left;
	node_t *right;
};


node_t *BSTToSortedList(node_t *root);

node_t *CreateNewNode(void *data);
node_t *InsertNode(node_t *root, void *data);
node_t *UtilFunc(node_t *node);
void CleanUp(node_t *node);

int CmpFunc(const void *data1, const void *data2);
void PrintList(node_t *node);
void PrintPreorderTree(node_t *root);

int main(void)
{
	int arr[] = {1,10,42,2,25,3,0,-1};
	size_t len = sizeof(arr) / sizeof(*arr);
	node_t *root = NULL;
	size_t i = 0;
	
	for (; i < len; ++i)
	{
		root = InsertNode(root, arr + i);
	}
	
	printf("tree Preorder:	");
	PrintPreorderTree(root);
	printf("\n");
	
	root = BSTToSortedList(root);
	
	printf("sorted DLL from BST:	");
	PrintList(root);
	
	CleanUp(root);
	
	return 0;
}

node_t *BSTToSortedList(node_t *root)
{
	if (NULL == root)
	{
		return root;
	}
	
	root = UtilFunc(root);
	
	while (NULL != root->left)
	{
		root = root->left;
	}
	
	return root;
}

node_t *UtilFunc(node_t *node)
{
	if (NULL == node)
	{
		return node;
	}
	
	if (NULL != node->left)
	{
		node_t *left = UtilFunc(node->left);
		
		for (; NULL != left->right; left = left->right) {/*empty loop*/}
		
		left->right = node;
		node->left = left;
	}
	
	if (NULL != node->right)
	{
		node_t *right = UtilFunc(node->right);
		
		for (; NULL != right->left; right = right->left) {/*empty loop*/}
		
		right->left = node;
		node->right = right;
	}
	
	return node;
}

node_t *InsertNode(node_t *root, void *data)
{
	if (NULL == root)
	{
		return CreateNewNode(data);
	}
	
	if (0 < CmpFunc(root->data, data))
	{
		root->left = InsertNode(root->left, data);
	}
	else if (0 > CmpFunc(root->data, data))
	{
		root->right = InsertNode(root->right, data);
	}
	
	return root;
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
	while (NULL != node)
	{
		node_t *temp = node;
		node = node->right;
		free(temp);
		temp = NULL;
	}
}

void PrintList(node_t *node)
{
	while (NULL != node)
	{
		printf("%d,", *(int *)(node->data));
		node = node->right;
	}
	printf("\n");
}

void PrintPreorderTree(node_t *root)
{
	if (NULL == root)
	{
		return;
	}
	
	printf("%d,", *(int *)(root->data));
	PrintPreorderTree(root->left);
	PrintPreorderTree(root->right);
}

int CmpFunc(const void *data1, const void *data2)
{
	return (*(int *)data1 - *(int *)data2);
}


