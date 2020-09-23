#include <stdlib.h>
#include "lista.h"

LISTA *lista_create(int (*cmp)(void *, void *)) {
	LISTA *list; 
	list = (LISTA *) calloc(1, sizeof(LISTA)); 
	list->cmp = cmp;
	return list;
}

int lista_add(LISTA *list, int pos, void *elem) {
	if (!list) return INVALID_LIST;
	if (pos < 0 || pos > list->counter) return INVALID_POS;

	ELEM *new; // Stack (8 bytes)
	new = (ELEM *) calloc(1, sizeof(ELEM));
	new->elem = elem;

	// percorrer até a  posição pos
	int counter = 0; // Stack (4 bytes)
	ELEM **p = &list->first;
	while (counter++ < pos && (p = &(*p)->next));

	if (*p) {
		new->prev = (*p)->prev;
		new->next = *p;
		(*p)->prev = new;
		*p = new;
	} else {
		*p = new;
		new->prev = list->last;
		list->last = new;
	}

	list->counter++;

	return SUCCESS;

}

int lista_add_first(LISTA *list, void *elem) {
	return lista_add(list, 0, elem);
}

int lista_add_last(LISTA *list, void *elem) {
	if (!list) return INVALID_LIST;
	return lista_add(list, list->counter, elem);
}

void *lista_get(LISTA *list, int pos, int *error) {
	if (!list) {
		*error = INVALID_LIST;
		return NULL;
	}

	if (pos < 0 || pos >= list->counter) {
		*error = INVALID_POS;
		return NULL;
	}

	int counter = 0;
	ELEM *p = list->first;
	while (counter++ < pos && (p = p->next));

	*error = SUCCESS;

	return p->elem;
}

int lista_free(LISTA *list) {
	if (!list) return INVALID_LIST;

	ELEM *p = list->first;
	while (p && p->next != NULL) {
		p = p->next;
		free(p->prev);
	}
	free(p);
	free(list);

	return SUCCESS;
}

int lista_remove(LISTA *list, int pos) {
	if (!list) return INVALID_LIST;
	if (pos < 0 || pos >= list->counter) return INVALID_POS;

	ELEM *p = list->first;
	int counter = 0;
	while (counter++ < pos && (p = p->next));
	
	if (p->prev)
		p->prev->next = p->next;
	else
		list->first = p->next;

	if (p->next)
		p->next->prev = p->prev;
	else
		list->last = p->prev;
	free(p);
	list->counter--;

	return SUCCESS;
}

int lista_sequential_search(
		LISTA *list, void *elem, int *error) {
	if (!list) {
		*error = INVALID_LIST;
		return -1;
	}

	int i;
	ELEM *p = list->first;
	for (i = 0; i < list->counter; i++) {
		if (!list->cmp(p->elem, elem)) {
			*error = SUCCESS;
			return i;
		}
		p = p->next;
	}
	*error = ELEM_NOT_FOUND;
	return -1;
}

int lista_size(LISTA *list) {
	if (!list) return INVALID_LIST;
	return list->counter;
}

int lista_sort(LISTA *list) {
	if (!list) return INVALID_LIST;

	void *aux;
	int i, j, error;
	for (i = 0; i < list->counter; i++) {
		ELEM *e0 = lista_get(list, i, &error);
		for (j = i+1; j < list->counter; j++) {
			ELEM *e1 = lista_get(list, j, &error);
			if (list->cmp(e1->elem, e0->elem) < 0) {
				aux = e0->elem;
				e0->elem = e1->elem;
				e1->elem = aux;
			}
		}
	}

	return SUCCESS;
}

LISTA *lista_copy(LISTA *list) {
	if (!list) return NULL;

	int i, error;
	LISTA *nlist = lista_create(list->cmp);

	for (i = 0; i < list->counter; i++) {
		lista_add(nlist, i, lista_get(list, i, &error));
	}

	return nlist;
}