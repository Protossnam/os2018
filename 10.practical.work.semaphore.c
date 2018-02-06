#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<semaphore.h>

#define BUFFER_SIZE (10)

typedef struct {
	char type;	// 0=fried chicken, 1=French fries
	int amount;	// pieces or weight
	char unit;	// 0=piece, 1=gram
} item;

item buffer[BUFFER_SIZE];
int first = 0;
int last = 0;
int m=0;

sem_t semaphore;

// 2 (not) atomic functions for mutex Start HERE!

void wait(int S) {
	while (S <= 0) return;
	S--;
}

void signal(int S) {
	S++;
}

// End HERE

void produce(item *i) {
	while ((first + 1) % BUFFER_SIZE == last) {
		return;
	}
	// Using mutex
	wait(m);
	memcpy(&buffer[first], i, sizeof(item));
	first = (first + 1) % BUFFER_SIZE;
	signal(m);
}

item *consume() {
	item *i = malloc(sizeof(item));
	while (first == last) {
		return NULL;
	}
	// Using mutex
	wait(m);
	memcpy(i, &buffer[last], sizeof(item));
	last = (last + 1) % BUFFER_SIZE;
	signal(m);
	return i;
}

void display(item i) {
	printf("Type: %d - Amount(s): %d - Unit: %d\n",i.type,i.amount,i.unit);
}

void *thread_Producer(void *param) {
	item fc, Ff1, Ff2;

	fc.type = 0;
        fc.amount = 5;
        fc.unit = 0;

	Ff1.type = 1;
        Ff1.amount = 7;
        Ff1.unit = 1;

	Ff2.type = 1;
	Ff2.amount = 15;
	Ff2.unit = 1;

	produce(&fc);
	produce(&Ff1);
	produce(&Ff2);
}

void *thread_Consumer(void *param) {
	display(*consume());
	display(*consume());
}

int main()
{
	pthread_t tid1,tid2;
	pthread_create(&tid1, NULL, thread_Producer, NULL);
 	pthread_create(&tid2, NULL, thread_Consumer, NULL);
	
	pthread_join(tid1, NULL);	
	pthread_join(tid2, NULL);

	return 0;
}
