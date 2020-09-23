#ifndef FUNCOES_H
#define FUNCOES_H

double complex *transformadaFourier(unsigned char *, int );

double *magnitudeFourier(double complex *, int );

int coefRelevantes(double *, int );

double *setMaiorRelevancia(double complex *, double *, int *, double complex *, int , int );

void voltandoPosicoesOriginais(double complex *, int *pos_coef, double complex *, int );

void inversaFourier(double complex *,unsigned char *, int );

#endif