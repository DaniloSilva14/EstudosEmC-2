#ifndef ITEM_H
#define ITEM_H

struct item{
  int valor;
  int chave;
  int posGlobal;
};

typedef struct item ITEM;

void print_item(ITEM );

#endif