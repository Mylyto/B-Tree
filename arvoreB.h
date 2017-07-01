// Adriano Martins: 2640
// Antônio Almeida: 2632

#ifndef ARVOREB_H_INCLUDED
#define ARVOREB_H_INCLUDED

#include "aluno.h"
#include "teste.h"
#define m 2

typedef struct pag * apontador;

typedef struct pag{
  short int qtd;
  TAluno vecAluno[2*m];
  apontador filho[2*m+1];
}TPagina;

void inicializaB(TPagina ** raiz);

void alturaB(TPagina ** raiz, TTeste * t);
void alt(TPagina ** pag, int * altura, TTeste * t);

void buscaB(TPagina * pag, int mat, TTeste * t);

void ins(TAluno a, TPagina ** pag, int * cresceu, TAluno *meio, TPagina ** pagRetorno);
void insereB(TAluno a, TPagina ** pag);
void inserePagina(TPagina ** pag, TAluno a, TPagina ** pagDir);

void removeB(TPagina ** pag, int mat);
void rem(TPagina ** pag, int mat, int * diminui);
void antecessor(TPagina ** pag, int ind, TPagina ** pagPai, int * diminui);
void reconstitui(TPagina ** pag, TPagina ** pagPai, int posPai, int * diminui);

#endif
