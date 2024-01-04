
#include <stdio.h>

#include "stack.h"

typedef struct queue
{
	stack_t *enqueue;
	stack_t *dequeue;
} s_queue_t;

void Enqueue(s_queue_t *queue, void *data);
void *Dequeue(s_queue_t *queue);

int main(void)
{
	int a = 1;
	int b = 2;
	int c = 3;
	s_queue_t new_queue = {NULL};
	
	new_queue.enqueue = StackCreate(10);
	new_queue.dequeue = StackCreate(10);
	
	Enqueue(&new_queue, &a);
	Enqueue(&new_queue, &b);
	Enqueue(&new_queue, &c);

	
	printf("%d\n", *(int *)Dequeue(&new_queue));
	printf("%d\n", *(int *)Dequeue(&new_queue));
	
	Enqueue(&new_queue, &c);
	Enqueue(&new_queue, &a);
	Enqueue(&new_queue, &c);
	
	printf("%d\n", *(int *)Dequeue(&new_queue));
	printf("%d\n", *(int *)Dequeue(&new_queue));
	printf("%d\n", *(int *)Dequeue(&new_queue));
	printf("%d\n", *(int *)Dequeue(&new_queue));
	
	StackDestroy(new_queue.enqueue);
	StackDestroy(new_queue.dequeue);
	
	return 0;
}

void Enqueue(s_queue_t *queue, void *data)
{
	StackPush(queue->enqueue, data);
}

void *Dequeue(s_queue_t *queue)
{
	void *poped_data = NULL;
	
	while (!StackIsEmpty(queue->enqueue))
	{
		StackPush(queue->dequeue, StackPop(queue->enqueue));
	}
	
	poped_data = StackPop(queue->dequeue);
	
	while (!StackIsEmpty(queue->dequeue))
	{
		StackPush(queue->enqueue, StackPop(queue->dequeue));
	}
	
	return poped_data;
}


