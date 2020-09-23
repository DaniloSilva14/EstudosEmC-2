#include <stdlib.h>
#include <stdio.h>
#include "fila.h"

int main(int argc, char *argv[]) {
	int error;
	int a=1,b=2,c=3;

	printf("Criando fila...\n");
	FILA *myqueue = fila_create();

	fila_enqueue(myqueue, &a);
	fila_enqueue(myqueue, &b);
	fila_enqueue(myqueue, &c);
	printf("Counter = %d\n", fila_size(myqueue));

	void *elem;
	while ((elem = fila_dequeue(myqueue, &error)) && 1) {
		printf("%d\n", *((int *) elem));
	}

	printf("Liberando fila...\n");
	fila_free(myqueue);

	return 0;
}
