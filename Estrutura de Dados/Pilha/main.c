#include <stdlib.h>
#include <stdio.h>
#include "pilha.h"

int main(int argc, char *argv[]) {
	int error;
	int a=1,b=2,c=3;

	printf("Criando Pilha...\n");
	PILHA *mystack = pilha_create();

	pilha_push(mystack, &a);
	pilha_push(mystack, &b);
	pilha_push(mystack, &c);
	printf("Size = %d\n", pilha_size(mystack));

	void *elem;
	while ((elem = pilha_pop(mystack, &error)) && 1) {
		printf("%d\n", *((int *) elem));
	}

	printf("Liberando Pilha...\n");
	pilha_free(mystack);

	return 0;
}
