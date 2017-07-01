// Adriano Martins: 2640
// Antônio Almeida: 2632

#ifndef  ALUNO_H_INCLUDED
#define ALUNO_H_INCLUDED

typedef struct {
  char nome[15];
  int matricula;
  int nota1, nota2, nota3, notaF;
}TAluno;

void insereAluno(TAluno * a, char * n, int m, int n1, int n2, int n3, int nf);

#endif
