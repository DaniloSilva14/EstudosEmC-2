#include <stdio.h>
#include <stdlib.h>//malloc
#include <string.h>//memset
#include <math.h>//cos, M_PI/

//Funcoes
double *alocar_vetor(int );
void print_vetor(double *,int );
void dct_ii(double *,double *,double );

int main() {
  double *vet_read, *vet_dct_ii;
  int n,i;

  //le tamanho e aloca vetor de leitura
  scanf("%d",&n);
  vet_read = alocar_vetor(n);
  if(vet_read == NULL){
    printf(" no vetor de leitura");
    return 0;
  }

  //recebe os dados
  for(i=0;i<n;i++)
    scanf("%lf",&vet_read[i]);

  //aloca vetor dos dados do dct_ii
  vet_dct_ii = alocar_vetor(n);
  if(vet_read == NULL){
    printf(" no vetor dct_ii");
    return 0;
  }
  
  //processamento dct_ii
  dct_ii(vet_read,vet_dct_ii,n);

  //print dos velores dct_ii
  print_vetor(vet_dct_ii, n);

  return 0;
}

double *alocar_vetor(int n){
  double *v;    
  if (n < 1) {
    printf ("erro: tamanho vetor");
    return NULL;
  }

  v = (double *) malloc (n * sizeof(double));

  if (v == NULL) {
    printf ("erro: memoria");
    return NULL;
  }

  return v;
}

void dct_ii(double *vet_read,double *vet_dct_ii,double n){
  int i,j;
  double aux;

  //limpa o vetor, já que a funcao de alocacao de memoria usada no codigo e feita com malloc
  memset(vet_dct_ii, 0, n * sizeof(double));

  //posicao por posicao fazendo o calculo
  for(i=0;i<n;i++){
    //percorre o vet_read para calcula o valor de uma casa do novo vetor
    for(j=0;j<n;j++){
      aux = cos((M_PI/n)*(j+1.0/2.0)*i);
      //somatorio, ele faz calculo e acrescenta toda vez que passa pelo laço
      vet_dct_ii[i]+=vet_read[j]*aux;
    }
  }
}

void print_vetor(double *vetor,int n){
  int i;

  for(i=0;i<n;i++)
    printf("%lf\n",vetor[i]);

}
