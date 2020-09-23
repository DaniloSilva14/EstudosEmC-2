#ifndef _SPARSE_H_
#define _SPARSE_H_

#define SUCCESS			             0
#define INVALID_SPARSE	        -1
#define INVALID_POS		          -2
#define NOT_FOUND		            -3

struct sparse_elem {
	int row, col;
	int elem;
	struct sparse_elem *right, *bottom;
};

struct sparse {
	int nrows, ncols;
	int constant;
	struct sparse_elem **row_index, **col_index;
};

typedef struct sparse SPARSE;
typedef struct sparse_elem SPARSE_ELEM;

SPARSE *createSP(int, int, int);
int putSP(SPARSE *, int, int, int);
int getSP(SPARSE *, int, int);
int removeSP(SPARSE *, int, int);
int freeSP(SPARSE *);

//EX
int putSP_Add(SPARSE *sparse, int row, int col, int elem);
SPARSE *somar_matriz(SPARSE *m1, SPARSE *m2);
SPARSE *multiplicar_matriz(SPARSE *m1, SPARSE *m2);

int imprimir_matriz(SPARSE *matriz);

#endif