#include <stdio.h>
#include <stdlib.h>
#include "matriz_esparsa.h"

SPARSE *createSP(int nrows, int ncols, int constant) {
	SPARSE *sparse =  malloc(sizeof(SPARSE));
	sparse->nrows = nrows;
	sparse->ncols = ncols;
	sparse->constant = constant;

	// malloc for indice
	sparse->row_index = calloc(nrows, sizeof(SPARSE_ELEM *));

	return sparse;
}

int putSP(SPARSE *sparse, int row, int col, int elem) {
	if (!sparse) return INVALID_SPARSE;
	if (row < 0 || col < 0 || 
		row >= sparse->nrows || col >= sparse->ncols) {
		return INVALID_POS;
	}

	SPARSE_ELEM **rp = &sparse->row_index[row];
	while (*rp && ((*rp)->col < col)) rp = &(*rp)->right;

	if (*rp  && (*rp)->col == col ) {
		(*rp)->elem = elem;
	} else {
		SPARSE_ELEM *new = malloc(sizeof(SPARSE_ELEM));
		new->row = row;
		new->col = col;
		new->elem = elem;
		new->right = *rp;
		*rp = new;
	}

	return SUCCESS;
}

int getSP(SPARSE *sparse, int row, int col){
	if (!sparse) 
    return 0;
	if (row < 0 || col < 0 || row >= sparse->nrows || col >= sparse->ncols)
		return 0;

	SPARSE_ELEM **rp = &sparse->row_index[row];

	while (*rp && ((*rp)->col < col)) rp = &(*rp)->right;

	if (*rp && (*rp)->col == col) return (*rp)->elem;
	
	return sparse->constant;
}

int removeSP(SPARSE *sparse, int row, int col) {
	if (!sparse) 
    return INVALID_SPARSE;
	if (row < 0 || col < 0 || row >= sparse->nrows || col >= sparse->ncols)
		return INVALID_POS;

	SPARSE_ELEM **rp = &sparse->row_index[row];
	SPARSE_ELEM *aux;

	while(*rp && (*rp)->col < col && (rp = &(*rp)->right));

	if (*rp && (*rp)->col == col) {
		aux = *rp;
		*rp = (*rp)->right;
		free(aux);
	}

	return SUCCESS;
}

int imprimir_matriz(SPARSE *matriz){
  if (!matriz) return INVALID_SPARSE;
  
  SPARSE_ELEM *paux;
  printf("-1 %d %d\n", matriz->nrows, matriz->ncols);
  for (int i = 0; i < matriz->nrows; i++) {
    for (paux = matriz->row_index[i]; paux != NULL; paux = paux->right) {
    printf("%d %d %d\n", paux->row, paux->col, paux->elem);
    }
  }

  return SUCCESS;
}

int freeSP(SPARSE *sparse) {
	if (!sparse) 
    return INVALID_SPARSE;

	SPARSE_ELEM *p;

	for (int i = 0; i < sparse->nrows; i++) {
    p = sparse->row_index[i];
		while (p) {
			sparse->row_index[i] = p->right;
			free(p);
      p = sparse->row_index[i];
		}
	}
	free(sparse->row_index);
	free(sparse);

  return SUCCESS;
}

//EX
int putSP_Add(SPARSE *sparse, int row, int col, int elem) {
	if (!sparse) return INVALID_SPARSE;
	if (row < 0 || col < 0 || 
		row >= sparse->nrows || col >= sparse->ncols) {
		return INVALID_POS;
	}

	SPARSE_ELEM **rp = &sparse->row_index[row];
	while (*rp && ((*rp)->col < col)) rp = &(*rp)->right;

	if (*rp && (*rp)->col == col ) {
		(*rp)->elem = (*rp)->elem + elem;
    if((*rp)->elem == 0) removeSP(sparse, row, col);
	} else {
		SPARSE_ELEM *new = malloc(sizeof(SPARSE_ELEM));
		new->row = row;
		new->col = col;
		new->elem = elem;
		new->right = *rp;
		*rp = new;
	}

	return SUCCESS;
}

SPARSE *somar_matriz(SPARSE *m1, SPARSE *m2){
  if(!m1 || !m2)  
    return NULL;
  if(m1->nrows != m2->nrows || m1->ncols != m2->ncols )
    return NULL;

  SPARSE * r = createSP(m1->nrows, m1->ncols,0);
  SPARSE_ELEM *paux;

  for (int i = 0; i < m1->nrows; i++) {
    for (paux = m1->row_index[i]; paux != NULL; paux = paux->right) {
      putSP_Add(r, paux->row, paux->col, paux->elem); 
    }
  }

  for (int i = 0; i < m2->nrows; i++) {
    for (paux = m2->row_index[i]; paux != NULL; paux = paux->right) {
      putSP_Add(r, paux->row, paux->col, paux->elem); 
    }
  }

  return r;
}

SPARSE *multiplicar_matriz(SPARSE *m1, SPARSE *m2){
  if(!m1 || !m2)  return NULL;
  if(m1->ncols != m2->nrows ) return NULL;

  SPARSE * r = createSP(m1->nrows, m2->ncols,0);
  int aux;

  SPARSE_ELEM *p_m1, *p_m2;

  //multiplica
  for(int i=0;i<r->nrows;i++){
    p_m1 = m1->row_index[i];
    if(p_m1){
      int flag=1;
      while(flag){
        for(int j=0;j<r->ncols;j++){
          aux= p_m1->elem * getSP(m2, p_m1->col, j);
          if(aux)putSP_Add(r, i, j, aux);
        }
        
        if(p_m1->right) p_m1 = p_m1->right;
        else flag = 0;
      }
    }
  }

  return r;
}