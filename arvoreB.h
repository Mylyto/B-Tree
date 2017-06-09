#ifndef ARVOREB_H_INCLUDED
#define ARVOREB_H_INCLUDED

#include "aluno.h"
#define m 2

typedef struct pag * apontador;

typedef struct pag{
  short int qtd;
  TAluno vecAluno[2*m];
  apontador filho[2*m+1];
}TPagina;

typedef apontador teste;

void inicializaB(TPagina * raiz);
void alturaB(TPagina * raiz, int * altura);
void buscaB(TPagina * raiz, int mat);
void insereB(TPagina * raiz, TAluno a);
void insereB2(TPagina * raiz, TAluno a, TAluno * meio, int pos, TPagina ** novosFilhos);
void removeB(TPagina * raiz, int mat);

#endif
