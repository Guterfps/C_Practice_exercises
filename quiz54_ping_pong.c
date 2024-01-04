
#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

void *DoPing(void *arg);
void *DoPong(void *arg);

sem_t sem_ping = {0};
sem_t sem_pong = {0};

int main(void)
{
	pthread_t thread1 = {0};
	pthread_t thread2 = {0};
	
	sem_init(&sem_ping, 0, 0);
	sem_init(&sem_pong, 0, 0);
	
	pthread_create(&thread2 , NULL, &DoPong, NULL);
	pthread_create(&thread1 , NULL, &DoPing, NULL);
	
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	
	sem_destroy(&sem_ping);
	sem_destroy(&sem_pong);
	
	return 0;
}

void *DoPing(void *arg)
{
	int i = 11;
	(void)arg;
	
	while (i--)
	{
		printf("PING\n");
		sem_post(&sem_ping);
		sem_wait(&sem_pong);
	}
	
	return NULL;
}

void *DoPong(void *arg)
{
	int i = 11;
	(void)arg;
	
	while (i--)
	{
		sem_wait(&sem_ping);
		printf("PONG\n");
		sem_post(&sem_pong);
	}
	
	return NULL;
}

