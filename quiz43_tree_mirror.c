
#include <stdio.h>
#include <stdlib.h>

typedef struct node node_t;

struct node
{
	void *data;
	node_t *left;
	node_t *right;
};

void MirrorTree(node_t *root);
void Swap(node_t *node);

node_t *CreateNewNode(void *data);
void CleanUp(node_t *node);
void PrintTree(node_t *root);

int main(void)
{
	int arr[] = {1,2,3,4,5,6,7};
	node_t *root = CreateNewNode(arr);
    root->left = CreateNewNode(arr + 1);
    root->right = CreateNewNode(arr + 2);
    root->left->left = CreateNewNode(arr + 3);
    root->left->right = CreateNewNode(arr + 4);
    root->right->left = CreateNewNode(arr + 5);
	root->right->right = CreateNewNode(arr + 6);
	
	printf("tree before mirror:\n");
	PrintTree(root);
	printf("\n");
	
	MirrorTree(root);
	
	printf("tree after mirror:\n");
	PrintTree(root);
	printf("\n");
	
	CleanUp(root);
	
	return 0;
}

void MirrorTree(node_t *root)
{
	if (NULL != root)
	{
		Swap(root);
		MirrorTree(root->left);
		MirrorTree(root->right);
	}
}

void PrintTree(node_t *root)
{
	if (NULL != root)
	{
		PrintTree(root->left);
		printf("%d, ", *(int *)(root->data));
		PrintTree(root->right);
	}
}

void Swap(node_t *node)
{
	node_t *temp = node->left;
	node->left = node->right;
	node->right = temp;
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

