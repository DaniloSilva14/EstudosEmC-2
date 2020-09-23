#include <stdio.h>
#include <stdlib.h>
#include <complex.h>//double complex 
#include <string.h>//memset
#include "funcoes.h"

int main(){
	int C, n = 0;
  char *nomeArq = NULL;

  nomeArq = (char*)malloc(10*sizeof(char));

  scanf("%s",nomeArq);
  scanf("%d",&C);

  FILE *arq;
  unsigned char *vetor = NULL;
  
  arq = fopen(nomeArq, "rb");
  if (!arq)
    printf("erro na abertura do arq!\n");
  else{
    while(!feof(arq)){
      vetor = (unsigned char*)realloc(vetor, (n+1)*sizeof(unsigned char));
      fscanf(arq,"%c",&vetor[n]);
      n++;
    }
  }
  n--;

  fclose(arq);
  printf("%d\n",n);
  
  //calculo transformada
  double complex *coef;
  coef = transformadaFourier(vetor,n);

  //calculo magnitude
  double *magnitude;
  magnitude=magnitudeFourier(coef,n);

  //coef relevantes do audio original
  printf("%d\n",coefRelevantes(magnitude, n));

  int *pos_coef = malloc(C * sizeof(int));
  double *maior;  
  double complex *aux = malloc(C * sizeof(double complex)); 

  maior = setMaiorRelevancia(coef, magnitude, pos_coef, aux, n, C);

  //maiores magnitudes (0 a C)
  for(int i =0;i<C;i++){
    printf("%d ",(int) maior[i]);
  }
  printf("\n");
  
  //voltando os coeficientes para pos original
  memset(coef, 0, (n/2 +1)*sizeof(double complex));
  voltandoPosicoesOriginais(coef,pos_coef, aux, C);
  
  //calculo inversa
  inversaFourier(coef, vetor,n);    
  for(int i=0;i<n;i++){
    printf("%d\n",vetor[i]);
  }  

  //liberado ponteiros
  free(nomeArq);
  free(maior);
  free(pos_coef);  
  free(aux); 
  free(magnitude); 
  free(coef); 
  free(vetor);  
    
  return 0;
}
