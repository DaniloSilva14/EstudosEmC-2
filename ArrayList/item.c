#include <stdio.h>
#include "item.h"

void print_item(ITEM elem){
  printf("%d/",elem.chave);
  printf("%d\n",elem.valor);
}