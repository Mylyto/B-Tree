// Adriano Martins: 2640
// Antônio Almeida: 2632

#ifndef ARVOREB_H_INCLUDED
#define ARVOREB_H_INCLUDED

#include "aluno.h"
#include "teste.h"
#define M 2
#define MM  (M * 2)
#define FALSE 0
#define TRUE  1

typedef struct pag * apontador;

typedef struct pag{
  short int qtd;
  TAluno vecAluno[2*M];
  apontador vecFilho[2*M+1];
}TPagina;

void Inicializa(TPagina ** pag);
void alturaB(TPagina ** raiz, TTeste * t);
void alt(TPagina ** pag, int * altura, TTeste * t);
void Pesquisa(int mat, TPagina * ap, TTeste * t);
void Pesquisa_(int mat, TAluno * aluno, TPagina * ap, TTeste * t);

void InsereNapagina(TPagina * ap,TAluno aluno, TPagina * apDir, TTeste * t);
void Ins(TAluno aluno, TPagina * ap, short *Cresceu,TAluno *alunoRetorno,  TPagina ** apRetorno, TTeste * t);
void Insere(TAluno aluno, TPagina **ap, TTeste * t);

void Reconstitui(TPagina * apPag, TPagina * apPai,int PosPai, short *Diminuiu, TTeste * t);
void Antecessor(TPagina * ap, int Ind,TPagina * apPai, short *Diminuiu, TTeste * t);
void Ret(int Ch, TPagina * *ap, short *Diminuiu, TTeste * t);
void Retira(int Ch, TPagina ** ap, TTeste * t);

void ImprimeI(TPagina * p, int nivel);
void Imprime(TPagina * p);
void TestaI(TPagina * p, int pai, short direita);
void Testa(TPagina * p);

#endif
