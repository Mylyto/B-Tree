#include <stdio.h>
#include <stdlib.h>
#include "aluno.h"
#include "arvoreB.h"

int main(int argc, char const *argv[]) {
  char nome[15];
  TTeste t;
  int mat, n1, n2, n3, nf;
  TAluno aluno;
  TPagina * paginaRaiz;
  FILE * arq;
  arq = fopen("teste.txt","r");
  if(arq==NULL){printf("ERRO COM ARQUIVO\n"); return 0;}
  inicializaB(&paginaRaiz);
  iniTeste(&t);
  while (fscanf(arq, "%d %s %d %d %d %d", &mat, nome, &n1, &n2, &n3, &nf) != EOF) { // Lendo arquivo de Entrada
    insereAluno(&aluno, nome, mat, n1, n2, n3, nf);
    insereB(aluno, &paginaRaiz);
  }
alturaB(&paginaRaiz, &t);
buscaB(paginaRaiz, 2640, &t);
printf("Removendo 2640\n");
removeB(&paginaRaiz, 2640);
printf("Pesquisando 2640\n");
buscaB(paginaRaiz, 2640, &t);
printf("\nFinalizado com sucesso...\n");
  return 0;
}
