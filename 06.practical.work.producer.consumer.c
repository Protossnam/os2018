#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define BUFFER_SIZE (10)

typedef struct {
	char type;	// 0=fried chicken, 1=French fries
	int amount;	// pieces or weight
	char unit;	// 0=piece, 1=gram
} item;

item buffer[BUFFER_SIZE];
int first = 0;
int last = 0;

void produce(item *i) {
	while ((first + 1) % BUFFER_SIZE == last) {
		return;
	}
	memcpy(&buffer[first], i, sizeof(item));
	first = (first + 1) % BUFFER_SIZE;
}

item *consume() {
	item *i = malloc(sizeof(item));
	while (first == last) {
		return NULL;
	}
	memcpy(i, &buffer[last], sizeof(item));
	last = (last + 1) % BUFFER_SIZE;
	return i;
}

void display(item i) {
	printf("Type: %d - Amount(s): %d - Unit: %d\n",i.type,i.amount,i.unit);
}

int main()
{
	item fc, Ff; 		// fc - fried chicken, Ff - French fries
	
	fc.type = 0;
	fc.amount = 5;
	fc.unit = 0;
	
	Ff.type = 1;
	Ff.amount = 7;
	Ff.unit = 1;

	produce(&fc);
	produce(&Ff);

	item *rts = consume(); 	// rts - ready to serve
	if (rts != NULL) display(*rts);

	return 0;
}
