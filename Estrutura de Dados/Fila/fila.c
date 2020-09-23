#include <stdlib.h>
#include "fila.h"

FILA *fila_create() {
	return (FILA *) calloc(1, sizeof(FILA));
}

int fila_enqueue(FILA *fila, void *elem) {
	if (!fila) return INVALID_QUEUE;

	ELEM *qelem = (ELEM *) malloc(sizeof(ELEM));
	qelem->elem = elem;
	qelem->next = NULL;

	if (!fila->counter) fila->first = qelem;
	else fila->last->next = qelem;
	fila->last = qelem;
	fila->counter++;
	return SUCCESS;
}

void *fila_dequeue(FILA *fila, int *error) {
	if (!fila) {
		*error = INVALID_QUEUE;
		return NULL;
	}

	if (!fila->counter) {
		*error = EMPTY_QUEUE;
		return NULL;
	}

	void *e;
	ELEM *elem = fila->first;
	fila->first = elem->next;
	fila->counter--;
	e = elem->elem;
	free(elem);
	if (!fila->counter) fila->last = NULL;

	*error = SUCCESS;
	return e;
}

void *fila_first(FILA *fila, int *error) {
	if (!fila) {
		*error = INVALID_QUEUE;
		return NULL;
	}

	if (!fila->counter) {
		*error = EMPTY_QUEUE;
		return NULL;
	}

	*error = SUCCESS;
	return fila->first->elem;
}

int fila_size(FILA *fila) {
	if (!fila) return  INVALID_QUEUE;
	return fila->counter;
}

int fila_free(FILA *fila) {
	if (!fila) return INVALID_QUEUE;
	int i;
	ELEM *elem;
	for (i = 0; i < fila->counter; i++) {
		elem = fila->first;
		fila->first = elem->next;
		free(elem);
	}
	free(fila);

	return SUCCESS;
}