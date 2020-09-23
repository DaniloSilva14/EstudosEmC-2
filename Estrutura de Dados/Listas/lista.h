#ifndef _LISTA_
#define _LISTA_

//Lista duplamente encadeada

#define SUCCESS 	0
#define INVALID_LIST 	-1
#define REMOVE_ERROR 	-2
#define GET_ERROR 	-3
#define INVALID_POS 	-4
#define ELEM_NOT_FOUND  -5

struct elem{
	void *elem;
	struct elem* prev;
	struct elem* next;
};
typedef struct elem ELEM;

struct lista {
	ELEM *first;
	ELEM *last;
	int (*cmp)(void *, void *);
	int counter;
};
typedef struct lista LISTA;

LISTA *lista_create(int (*)(void *, void *));
int lista_add(LISTA *, int, void *);
int lista_add_first(LISTA *, void *);
int lista_add_last(LISTA *, void *);
void *lista_get(LISTA *, int, int *);
int lista_free(LISTA *);
int lista_remove(LISTA *, int);
int lista_equential_search(LISTA *, void *, int *);
int lista_size(LISTA *);
int lista_sort(LISTA *);
LISTA *lista_copy(LISTA *);

#endif