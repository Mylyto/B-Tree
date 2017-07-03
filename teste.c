// Adriano Martins: 2640
// Antônio Almeida: 2632

#include "teste.h"
#include <stdlib.h>
#include <stdio.h>

/* Funções que inicializam e incrementam as variáveis responsáveis por
fazer a contagem de comparações e acessos, bem como armazenar a altura
da árvore.*/


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

void alturaTeste(TTeste * t, int a){
  t->altura = a;
}

void comparacaoRemocao(TTeste * t, int peso){
    t->comparacaoRemocao = t->comparacaoRemocao + (1*peso);
}

void comparacaoInsercao(TTeste * t, int peso){
    t->comparacaoInsercao = t->comparacaoInsercao + (1*peso);
}

void comparacaoPesquisa(TTeste * t, int peso){
    t->comparacaoPesquisa = t->comparacaoPesquisa + (1*peso);
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
