// Adriano Martins: 2640
// Ant�nio Almeida: 2632

#ifndef TESTE_H_INCLUDED
#define TESTE_H_INCLUDED

typedef struct st {
  int altura;
  int acessoRemocao, comparacaoRemocao;
  int acessoPesquisa, comparacaoPesquisa;
  int acessoInsercao, comparacaoInsercao;
  int acessoTotal, comparacaoTotal;
}TTeste;


void iniTeste(TTeste * t);

void alturaTeste(TTeste * t, int a);

void acessoRemocao(TTeste * t);
void comparacaoRemocao(TTeste * t, int peso);

void acessoInsercao(TTeste * t);
void comparacaoInsercao(TTeste * t, int peso);

void acessoPesquisa(TTeste * t);
void comparacaoPesquisa(TTeste * t, int peso);


#endif
