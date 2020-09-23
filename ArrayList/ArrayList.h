#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H
#include "item.h"

#define SUCCESS 0
#define INVALID_ARRAYLIST -1
#define INVALID_POS -2
#define INVALID_LIST -3

struct no {
  ITEM *list;//lista interna
  int ultimoElem;//ultimo colocado
  int tamanho;//tamanho da lista interna
  struct no *next;
};

typedef struct no NO;

struct ArrayList{
  NO *inicio;//primeiro no
  int qtd_elementos;//qtd total do arrayList
  int tamMaiorVetor;
};

typedef struct ArrayList ArrayList;

//Cria a ArrayList e aloca toda memoria necessaria
ArrayList *new_arrayList();
//adiciona elemento ao arraylist
int add_arrayList(ArrayList *arrayList,ITEM );
//imprime toda a lista
void print_arrayList(ArrayList *arrayList);
//remove os no deixa apenas o descritor
void clear_arrayList(ArrayList *);

int busca_binaria_chave(ITEM *, int , int );
int busca_binaria_pos(ITEM *, int , int );

//verifica no arraylist se existe um elemento com a chave informada
int contains_arrayList(ArrayList *arrayList, int chave);
//recupera um ITEM na posicao informada
ITEM *get_arrayList(ArrayList *arrayList, int pos);
//retorna qual a posicao do primeiro elemento com a chave informada
int indexOf_arrayList(ArrayList *arrayList, int chave);
//verifica se o arraylist esta vazio
int isEmpty_arrayList(ArrayList *arrayList);
//retorna o tamanho total do arraylist
int size_arrayList(ArrayList *arrayList);

//ordenador Professor Adenilson ICC2
void swap(ITEM *a, ITEM *b);
void HeapFy(ITEM *vetor, int p,int m);
void heapSort(ITEM *vetor, int n);
//um novo subarray no intervalo [beginIndex, endIndex[
ArrayList *subArray_arrayList(ArrayList *arrayList);
//modifica um elemento do arraylist
int set_arrayList(ArrayList *arrayList, int pos, ITEM element);
//remove um elemento do arraylist
int remove_arrayList(ArrayList *arrayList, int pos);
//desaloca memoria alocada pelo arraylist
int destruct_arrayList(ArrayList *arrayList);

#endif