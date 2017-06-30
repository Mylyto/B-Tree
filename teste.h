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
void resultadoTeste(TTeste t);
void alturaTeste(TTeste * t);
void acessoRemocao(TTeste * t);
void comparacaoRemocao(TTeste * t);
void acessoInsercao(TTeste * t);
void comparacaoInsercao(TTeste * t);
void acessoPesquisa(TTeste * t);
void comparacaoPesquisa(TTeste * t);
void acessoTotal(TTeste * t);
void comparacaoTotal(TTeste * t);

#endif
