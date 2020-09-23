#ifndef _FILA_
#define _FILA_

#define SUCCESS		0
#define INVALID_QUEUE	-1
#define EMPTY_QUEUE	-2

struct elem {
	void *elem;
	struct elem *next;
};

struct fila {
	struct elem *first, *last;
	int counter;
};

typedef struct fila FILA;
typedef struct elem ELEM;

FILA *fila_create();
int fila_enqueue(FILA *, void *);
void *fila_dequeue(FILA *, int *);
void *fila_first(FILA *, int *);
int fila_size(FILA *);
int fila_free(FILA *);

#endif