#include <stdlib.h>
#include <stdio.h>
#include "lista.h"

int compare(int *e0, int *e1) {
	if (*e0 == *e1) return 0;
	else if (*e0 < *e1) return -1;
	else return +1;
}

int main(int argc, char *argv[]) {
	LISTA *mylist;
	int i, error, elem0 = 5, elem1=2, elem2 = 3;

	mylist = (LISTA *) 
		lista_create((int (*)(void*, void*))&compare);

	printf("size: %d\n", lista_size(mylist));

	lista_add(mylist, 0, &elem0); // 2 5 3
	lista_add(mylist, 0, &elem1);
	lista_add(mylist, 2, &elem2);

	for (i = 0; i < lista_size(mylist); i++) {
		int *v = (int *) lista_get(mylist, i, &error);
		printf("Valor %d na posicao %d\n", *v, i);
	}

	printf("size: %d\n",  lista_size(mylist));

	lista_free(mylist);

	return 0;
}
