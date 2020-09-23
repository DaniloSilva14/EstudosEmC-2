#include <stdio.h>
#include <stdlib.h>
#include "ArrayList.h"

ArrayList *new_arrayList(){
  ArrayList *arrayList;
  arrayList = (ArrayList*)calloc(1, sizeof(ArrayList));
  arrayList->tamMaiorVetor = 10;
  return arrayList;
}

int add_arrayList(ArrayList *arrayList, ITEM aux){
  if(!arrayList) return INVALID_ARRAYLIST;

  ITEM *item = malloc(sizeof(ITEM));
  item->chave = aux.chave;
  item->valor = aux.valor;
  
  if(!arrayList->inicio){
    NO *new = (NO *)calloc(1, sizeof(NO));
    arrayList->inicio = new;
    arrayList->inicio->tamanho = arrayList->tamMaiorVetor;
    arrayList->inicio->list = malloc                                   (arrayList->inicio->tamanho * sizeof(ITEM));
  }

  NO *p = arrayList->inicio; 

  while(p->next && (p = p->next)); 
  
  if(p->ultimoElem == p->tamanho){
    arrayList->tamMaiorVetor =                              arrayList->tamMaiorVetor*2;

    NO *aux = (NO *)calloc(1, sizeof(NO));
    p->next = aux;
    p = p->next;
   
    p->tamanho = arrayList->tamMaiorVetor;

    p->list = calloc(1,p->tamanho * sizeof(ITEM **));
  }
  
  p->list[p->ultimoElem].chave = item->chave;
  p->list[p->ultimoElem].valor = item->valor;
  p->list[p->ultimoElem].posGlobal = arrayList->qtd_elementos;

  p->ultimoElem = p->ultimoElem+1;
  arrayList->qtd_elementos++; 

  return SUCCESS;
}

void print_arrayList(ArrayList *arrayList){
  NO *paux = arrayList->inicio;
  int index=0;

  while(paux != NULL){

    for(int i=0; i<paux->ultimoElem; i++){
      printf("%d: ", index++);
      print_item(paux->list[i]);
    }

    printf("\n\n");
    paux = paux->next;
  }
}

void clear_arrayList(ArrayList *arrayList){
  NO *p = arrayList->inicio;
  while(p){
    arrayList->inicio = p->next;
    free(p);
    p = arrayList->inicio;
  }
  free(p);
  arrayList->qtd_elementos= 0;
  arrayList->tamMaiorVetor=10;
}

int busca_binaria_chave(ITEM *list, int tam, int key){
  if(!list) return  INVALID_LIST;
  int menor = 0, meio,  maior = tam - 1;

  while (menor <= maior ){
		meio = (menor + maior) / 2;
		if (key == list[meio].chave) 
			return meio;
		else 
			if (key < list[meio].chave)
				maior = meio - 1;
			else 
				menor = meio + 1;
  }
  return INVALID_POS;
}

int contains_arrayList(ArrayList *arrayList, int chave){
  if(!arrayList) return  INVALID_ARRAYLIST;

  int count = 0;
  NO *p = arrayList->inicio;

  while(p){
    count = busca_binaria_chave(p->list,p->ultimoElem, chave);
    if(count>-1) return 1;
    p = p->next;
  }

  return 0;
}

int indexOf_arrayList(ArrayList *arrayList, int chave){
  if(!arrayList) return  INVALID_ARRAYLIST;

  int count = 0;
  NO *p = arrayList->inicio;

  while(p){
    count = busca_binaria_chave(p->list,p->ultimoElem, chave);
    if(count>-1) return p->list[count].posGlobal;
    p = p->next;
  }

  return 0;
}

int busca_binaria_pos(ITEM *list, int tam, int key){
  if(!list) return  INVALID_LIST;
  int menor = 0, meio,  maior = tam - 1;

  while (menor <= maior ){
		meio = (menor + maior) / 2;
		if (key == list[meio].posGlobal)
      return meio;
		else 
      if (key < list[meio].posGlobal)
        maior = meio - 1;
		  else 
        menor = meio + 1;
  }
  return -1;
}

ITEM *get_arrayList(ArrayList *arrayList, int pos){
  if(!arrayList) return  NULL;
  
  int count;
  NO *p = arrayList->inicio;

  while(p){
    count = busca_binaria_pos(p->list,p->ultimoElem,pos);
    if(count>-1){
      print_item(p->list[count]);
      return &p->list[count];
    } 
    p = p->next;
  }
  return NULL;
}

int isEmpty_arrayList(ArrayList *arrayList){
  if(!arrayList) return  INVALID_ARRAYLIST;
  if(!arrayList->qtd_elementos)
    return 1;
  return 0;
}

void swap(ITEM *a, ITEM *b){
  ITEM temp = *a;
  *a = *b;
  *b = temp;
}

//Professor Adenilson ICC2
void HeapFy(ITEM *vetor, int p,int m){
  int f = 2*p + 1;

  if(f<m){
    if((f+1)<m){
      if(vetor[f+1].chave>vetor[f].chave){
        f++;
      }
    }
    if(vetor[p].chave<vetor[f].chave){
	    swap(&vetor[p],&vetor[f]);
      HeapFy(vetor,f,m);
    }
  }
}

//Professor Adenilson ICC2
void HeapSort(ITEM *vetor,int n){
    for(int i = n-1;i>=0;i--){
        HeapFy(vetor,i,n);
    }

    for(int i=n-1;i>0;i--){
      swap(&vetor[0],&vetor[i]);
      HeapFy(vetor,0,i);
    }
}

int set_arrayList(ArrayList *arrayList,int pos,ITEM element){
  if(!arrayList) return  INVALID_ARRAYLIST;

  NO *p = arrayList->inicio;
  int flag = 1;
  while(p && flag){
    for(int i=0;i< p->tamanho && flag;i++){
      if(p->list[i].posGlobal == pos){
        p->list[i].chave = element.chave;
        p->list[i].valor = element.valor;
        flag = 0;
      }
    }
    p = p->next;
  }

  p = arrayList->inicio;
  ITEM *list = (ITEM*)malloc(arrayList->qtd_elementos*sizeof(ITEM));
  int count = 0;

  while(p != NULL){
    for(int i=0; i < p->ultimoElem; i++){
      list[count].chave = p->list[i].chave;
      list[count].valor = p->list[i].valor;
      count++;
    }
    p = p->next;
  }

  HeapSort(list, arrayList->qtd_elementos);

  p = arrayList->inicio;
  count = 0;

  while(p != NULL){
    for(int i=0; i < p->ultimoElem; i++){
      p->list[i].chave = list[count].chave;
      p->list[i].valor = list[count].valor;  
      p->list[i].posGlobal = count;  
      count++; 
    }
    p = p->next;
  }

  return SUCCESS;
}


int remove_arrayList(ArrayList *arrayList, int pos){
  if(!arrayList) return  INVALID_ARRAYLIST;

  if(pos < 0 || pos > arrayList->qtd_elementos)
    return INVALID_POS;

  NO *p = arrayList->inicio;
  int flag = 1;
  while(p && flag){
    for(int i=0;i< p->tamanho && flag;i++){
      if(p->list[i].posGlobal == pos){
        p->list[i].chave = -1;
        p->list[i].valor = -1;
        flag = 0;
      }
    }
    p = p->next;
  }

  p = arrayList->inicio;
  ITEM *list = (ITEM*)malloc((arrayList->qtd_elementos)*sizeof(ITEM));
  int count = 0;

  while(p!= NULL){
    for(int i=0; i < p->ultimoElem; i++){
      list[count].chave = p->list[i].chave;
      list[count].valor = p->list[i].valor;
      count++;
    }
    p = p->next;
  }

  HeapSort(list, arrayList->qtd_elementos);

  int tam = arrayList->qtd_elementos;
  clear_arrayList(arrayList);

  for(int i=0;i<tam-1;i++){
    list[i].chave = list[i+1].chave;
    list[i].valor = list[i+1].valor;
  }

  ITEM new;
  for(int i = 0;i < tam-1;i++){
    new.chave = list[i].chave;
    new.valor = list[i].valor;
    add_arrayList(arrayList,new);
  }

  return SUCCESS;
}


int size_arrayList(ArrayList *arrayList){
  if(!arrayList) return INVALID_ARRAYLIST;
  return arrayList->qtd_elementos;
}

ArrayList *subArray_arrayList(ArrayList *arrayList){
  if(!arrayList) return NULL;

  int beginIndex, endIndex, aux_qtd = 0;
  scanf("%d %d", &beginIndex, &endIndex);

  ArrayList *new;
  new = new_arrayList();
  new->qtd_elementos = endIndex-beginIndex;

  NO *p = arrayList->inicio;

  while(p != NULL && aux_qtd < new->qtd_elementos){
    for(int i=0; i < p->ultimoElem && beginIndex<endIndex ; i++){
      if(p->list[i].posGlobal == beginIndex){
          add_arrayList(new, p->list[i]);
          aux_qtd++;
          beginIndex++;
        }
      }
    p = p->next;
  }

  print_arrayList(new);
  
  return new;
}

int destruct_arrayList(ArrayList *arrayList){
  if(!arrayList)  return INVALID_ARRAYLIST;
 
  NO *p = arrayList->inicio;

  while(p){
    arrayList->inicio = p->next;
    free(p);
    p = arrayList->inicio;
  }

  free(p);
  free(arrayList);

  return SUCCESS;
}