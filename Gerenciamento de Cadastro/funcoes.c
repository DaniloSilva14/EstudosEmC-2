#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

void cadastra(USER *users,int i){
  if(!users) 
    //return NULL;
    return ;

  users[i].primeiroNome=(char *)malloc(15 * sizeof(char));  
  users[i].ultimoNome=(char *)malloc(15 * sizeof(char));
  users[i].cpf=(char *)malloc(11 * sizeof(char));
  users[i].tell=(char *)malloc(20 * sizeof(char));

  scanf("%s",users[i].primeiroNome);
  scanf("%s",users[i].ultimoNome);
  scanf("%s",users[i].cpf);
  scanf("%s",users[i].tell); 
}

void buscarCPF(USER *users,int i,char *auxCPF){
  if(!users) 
    //return NULL;
    return ;

  for(int j=0;j<i;j++){
    if(strcmp(users[j].cpf,auxCPF)==0){
      printf("Primeiro Nome: %s\n", users[j].primeiroNome);
      printf("Ultimo Nome: %s\n", users[j].ultimoNome);
      printf("CPF: %s\n", users[j].cpf);
      printf("Telefone: %s\n", users[j].tell);
      printf("-----------------------------\n");
    }
  }
}

void dump(USER *users,int i){
  if(!users) 
    //return NULL;
    return ;

  for(int j=0;j<i;j++){
    printf("Primeiro Nome: %s\n", users[j].primeiroNome);
    printf("Ultimo Nome: %s\n", users[j].ultimoNome);
    printf("CPF: %s\n", users[j].cpf);
    printf("Telefone: %s\n", users[j].tell);
    printf("-----------------------------\n");
  }
}

int removeUSER(USER *users, int i,char *auxCPF){
  if(!users) 
    //return NULL;
    return 0;

  for(int j = 0; j < i; j++){
    if(strcmp(users[j].cpf,auxCPF) == 0){
      if(i!=1 && j<(i-1)){
        for(int k = j; k < i-1; k++){
          strcpy(users[k].primeiroNome,users[k+1].primeiroNome);
          strcpy(users[k].ultimoNome, users[k+1].ultimoNome);
          strcpy(users[k].cpf, users[k+1].cpf);
          strcpy(users[k].tell, users[k+1].tell);
        }
      }
      i--;
    }     
  }
  return i;
}

void libera(USER *users,int i){
  if(!users) 
    //return NULL;
    return ;

  for(int j=0;j<i;j++){
    free(users[j].primeiroNome);
    free(users[j].ultimoNome);
    free(users[j].cpf);
    free(users[j].tell);
  }
}