// Adriano Martins: 2640
// Ant�nio Almeida: 2632

#include "aluno.h"
#include <string.h>

// Fun��o auxiliar que atribui valores para um aluno qualquer
void insereAluno(TAluno * a, char * n, int m, int n1, int n2, int n3, int nf){
  strcpy(a->nome, n);
  a->matricula = m;
  a->nota1 = n1;
  a->nota2 = n2;
  a->nota3 = n3;
  a->notaF = nf;
}
