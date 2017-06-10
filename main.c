#include <stdio.h>
#include <stdlib.h>
#include "aluno.h"
#include "arvoreB.h"

int main(int argc, char const *argv[]) {
  char nome[15];
  int mat, n1, n2, n3, nf, i = 0;
  TAluno aluno;
  TPagina paginaRaiz;
  FILE * arq;
  arq = fopen("nomes.txt","r");
  if(arq==NULL){printf("ERRO COM ARQUIVO\n"); return 0;}
  inicializaB(&paginaRaiz);
  paginaRaiz.qtd = 0;
  while (fscanf(arq, "%d %s %d %d %d %d", &mat, nome, &n1, &n2, &n3, &nf) != EOF) { // Lendo arquivo de Entrada
    insereAluno(&aluno, nome, mat, n1, n2, n3, nf);
    insereB(&paginaRaiz, aluno);
    printf("%d ", paginaRaiz.vecAluno[i++].matricula);
    //buscaB(&paginaRaiz, mat);
  }
  return 0;
}
