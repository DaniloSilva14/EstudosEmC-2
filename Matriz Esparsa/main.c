#include <stdio.h>
#include "matriz_esparsa.h"

int main(){
  char op;
  int nr_linhas, nr_colunas, valor;

  scanf("%c", &op);

  //lendo a matriz a
  scanf("%d %d %d", &valor, &nr_linhas, &nr_colunas);
  SPARSE * A = createSP(nr_linhas, nr_colunas,0);
  while (scanf("%d %d %d", &nr_linhas, &nr_colunas, &valor) && nr_linhas != -1){
    putSP(A, nr_linhas, nr_colunas, valor);
  }

  //lendo a matriz b
  SPARSE * B = createSP(nr_colunas, valor,0);
  while (scanf("%d %d %d", &nr_linhas, &nr_colunas, &valor) != EOF){
    putSP(B, nr_linhas, nr_colunas, valor);
  }

  SPARSE *C = NULL;
  if (op == 'M'){
    C = multiplicar_matriz(A,B);
  } else if (op == 'A'){
    C = somar_matriz(A,B);
  }

  imprimir_matriz(C);
  freeSP(A);
  freeSP(B);
  freeSP(C);
  
  return 0;
}
