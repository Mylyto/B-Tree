#include "teste.h"
#include <stdlib.h>
#include <stdio.h>
void iniTeste(TTeste * t){
  t->altura = 0;
  t->acessoRemocao = 0;
  t->comparacaoRemocao = 0;
  t->acessoInsercao = 0;
  t->comparacaoInsercao = 0;
  t->acessoPesquisa = 0;
  t->comparacaoPesquisa = 0;
  t->acessoTotal = 0;
  t->comparacaoTotal = 0;
}
void resultadoTeste(TTeste t){

}
void alturaTeste(TTeste * t){
  t->altura++;
}
void comparacaoRemocao(TTeste * t){
    t->comparacaoRemocao++;
}
void comparacaoInsercao(TTeste * t){
    t->comparacaoInsercao++;
}
void comparacaoPesquisa(TTeste * t){
    t->comparacaoPesquisa++;
}

void comparacaoTotal(TTeste * t){
  t->comparacaoTotal = t->comparacaoPesquisa + t->comparacaoInsercao + t->comparacaoRemocao;
}
void acessoRemocao(TTeste * t){
  t->acessoRemocao++;
}
void acessoInsercao(TTeste * t){
  t->acessoInsercao++;
}
void acessoPesquisa(TTeste * t){
  t->acessoPesquisa++;
}
void acessoTotal(TTeste * t){
  t->acessoTotal = t->acessoPesquisa + t->acessoInsercao + t->acessoRemocao;
}
