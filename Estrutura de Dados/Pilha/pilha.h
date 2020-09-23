#ifndef _PILHA_H_
#define _PILHA_H_

#define SUCCESS		0
#define INVALID_STACK	-1
#define EMPTY_STACK	-2

struct elem {
	void *elem;
	struct elem *next;
};

struct pilha {
	struct elem *top;
	int counter;
};

typedef struct pilha PILHA;
typedef struct elem ELEM;

PILHA *pilha_create();
int pilha_push(PILHA *, void *);
void *pilha_pop(PILHA *, int *);
void *pilha_top(PILHA *, int *);
int pilha_size(PILHA *);
int pilha_free(PILHA *);

#endif