#include <stdlib.h>
#include <complex.h>
#include <math.h>

double complex *transformadaFourier(unsigned char *vetor, int n){
  double complex soma;
  double complex *coef;

  coef = malloc((n/2 +1)*sizeof(double complex));

  for(int k=0;k<n/2 + 1;k++){
    soma=0;
    for(int t=0;t<n;t++){
      soma+=vetor[t]/(cos(2*M_PI*k*t/n)+sin(2*M_PI*k*t/n)*I);
    }

    if(k) 
      coef[k]=2*soma/n;
    else 
      coef[0]=soma/n;
  }

  return coef;
}

double *magnitudeFourier(double complex *coef, int n){
  double *magnitude;

  magnitude=malloc((n/2+1)*sizeof(double));

  for(int i=0;i<n/2 + 1;i++){
    magnitude[i]=sqrt(pow(creal(coef[i]),2)+pow(cimag(coef[i]),2));
  }

  return magnitude;
}

int coefRelevantes(double *magnitude, int n){
  int cont = 0;

  for(int i=0;i<n/2 + 1;i++){
    if(magnitude[i]>0.1)
      cont++;
  }

  return cont;
}

double *setMaiorRelevancia(double complex *coef,double *magnitude, int *pos_coef, double complex *aux, int n, int C){
  double *maior;
  maior = malloc(C* sizeof(double ));
  
  for(int i=0;i<C;i++){
    maior[i]=magnitude[i];
    pos_coef[i]=i;
    for(int j=0;j<n/2 +1;j++){
      if(magnitude[j]>maior[i]){
        maior[i]=magnitude[j];
        pos_coef[i]=j;
      }
    }
    magnitude[pos_coef[i]]=0;
    aux[i]=coef[pos_coef[i]];
  }

  return maior;
}

void voltandoPosicoesOriginais(double complex*coef, int *pos_coef, double complex *aux, int C){
  for(int i=0;i<C;i++)
    coef[pos_coef[i]]=aux[i];
}

void inversaFourier(double complex *coef,unsigned char *vetor, int n){
  double complex soma;

  for(int i=0;i<n;i++){
    soma=0;
    for(int j=0;j<n/2 +1;j++){
      soma+=coef[j]*(cos(2*M_PI*j*i/n)+sin(2*M_PI*j*i/n)*I);
    }
    vetor[i]=round(soma);
  }
}