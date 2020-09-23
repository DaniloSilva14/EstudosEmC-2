#include <stdlib.h>
#include "pilha.h"

PILHA *pilha_create() {
	return (PILHA *) calloc(1, sizeof(PILHA));
}

int pilha_push(PILHA *pilha, void *elem) {
	if (!pilha) return INVALID_STACK;
	ELEM *e = (ELEM *) malloc(sizeof(ELEM));
	e->elem = elem;
	e->next = pilha->top;
	pilha->top = e;
	pilha->counter++;

	return SUCCESS;
}

void *pilha_pop(PILHA *pilha, int *error) {
	if (!pilha) {
		*error = INVALID_STACK;
		return NULL;
	}

	if (!pilha->counter) {
		*error = EMPTY_STACK;
		return NULL;
	}

	void *e;
	ELEM *elem = pilha->top;
	pilha->top = elem->next;
	e = elem->elem;
	free(elem);
	pilha->counter--;

	*error = SUCCESS;
	return e;
}

void *pilha_top(PILHA *pilha, int *error) {
	if (!pilha) {
		*error = INVALID_STACK;
		return NULL;
	}

	if (!pilha->counter) {
		*error = EMPTY_STACK;
		return NULL;
	}

	*error = SUCCESS;
	return pilha->top->elem;
}

int pilha_size(PILHA *pilha) {
	if (!pilha) return INVALID_STACK;
	return pilha->counter;
}

int pilha_free(PILHA *pilha) {
	if (!pilha) return INVALID_STACK;
	int i;
	ELEM *e;
	for (i = 0; i < pilha->counter; i++) {
		e = pilha->top;
		pilha->top = e->next;
		free(e);
	}
	free(pilha);
	return SUCCESS;
}