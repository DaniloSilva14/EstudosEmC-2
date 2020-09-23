#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArrayList.h"

int main() {
  char *op = NULL;
  ArrayList *arrayList;
  int aux;
  ITEM item;

  op = (char *) realloc(op, 7 *sizeof(char));

  arrayList = new_arrayList();

  do{
    scanf("%s",op);

    switch(op[0]){
      //add
      case 'a':
        scanf("%d %d",&item.chave,&item.valor);
        add_arrayList(arrayList,item);
      break;

      //print
      case 'p':
        print_arrayList(arrayList);
      break;

      //tamanho
      case 't':
        printf("%d\n", size_arrayList(arrayList));
      break;

      //vazia
      case 'v':
        printf("%d\n", isEmpty_arrayList(arrayList));
      break; 
      
      //contem
      case 'c':
        scanf("%d",&aux);
        
        printf("%d\n",contains_arrayList(arrayList, aux));
      break; 

      //indice
      case 'i':
        scanf("%d",&aux);
        aux = indexOf_arrayList(arrayList, aux);
        if(aux>0)
          printf("%d\n",aux);
      break; 

      //get
      case 'g':
        scanf("%d",&aux);
        get_arrayList(arrayList, aux);
      break; 

      //remover
      case 'r':
        scanf("%d",&aux);
        remove_arrayList(arrayList, aux);
      break;

      case 's':
        switch(op[1]){
          //sub
          case 'u':
            subArray_arrayList(arrayList);
          break;

          //set
          case 'e':
            scanf("%d",&aux);
            scanf("%d %d",&item.chave,&item.valor);
            set_arrayList(arrayList, aux, item);
          break;
        }
      break;
    }
  }while(strcmp(op,"sair")!=0);

  free(op);
	destruct_arrayList(arrayList);

  return 0;
}
