// Adriano Martins: 2640
// Antônio Almeida: 2632

#include <stdio.h>
#include <stdlib.h>
#include "aluno.h"
#include "arvoreB.h"
#include "teste.h"

int main(int argc, char const *argv[]) {
  // Declarado TADS
  TPagina * pagina;
  TAluno aluno;
  TTeste teste;
  // Declarando variáveis auxiliares
  int matricula, nota1, nota2, nota3, notaFinal;
  char nome[40];
  int op, flag = 0;
  // Lista de arquivos
  FILE *itensInsercao, *itensRemocao, *itensBusca, *arqAlunos;
  FILE *arqSaidaI, *arqSaidaR,*arqSaidaB;

  arqAlunos = fopen("nomes.txt", "r");
  itensInsercao = fopen("insercao.txt", "r");
  itensRemocao = fopen("remocao.txt", "r");
  itensBusca = fopen("busca.txt", "r");
  arqSaidaI = fopen("saidaInsercao.txt", "w");
  arqSaidaR = fopen("saidaRemocao.txt", "w");
  arqSaidaB = fopen("saidaBusca.txt", "w");

  // Iniciando TADS
  iniTeste(&teste);
  Inicializa(&pagina);

  if(arqAlunos==NULL||itensRemocao==NULL||itensInsercao==NULL||itensBusca==NULL||
    arqSaidaI==NULL||arqSaidaR==NULL||arqSaidaB==NULL){
    printf("ERRO COM O(S) ARQUIVO(S)\n");
    return 0;
  }

  // Lendo 10K de alunos e os inserindo para criar a árvore inicial
  while (fscanf(arqAlunos, "%d %s %d %d %d %d", &matricula, nome, &nota1, &nota2, &nota3, &notaFinal) != EOF) {
    insereAluno(&aluno, nome, matricula, nota1, nota2, nota3, notaFinal);
    Insere(aluno, &pagina, &teste);
  }
  Testa(pagina);

  // Inserindo 100 alunos para teste
  while (fscanf(itensInsercao, "%d %s %d %d %d %d", &matricula, nome, &nota1, &nota2, &nota3, &notaFinal) != EOF) {
    // Zerando o contador de acesso e comparações
    iniTeste(&teste);
    insereAluno(&aluno, nome, matricula, nota1, nota2, nota3, notaFinal);
    Insere(aluno, &pagina,&teste);
    alturaB(&pagina, &teste);
    fprintf(arqSaidaI, "%d %d %d\n", teste.altura, teste.comparacaoInsercao, teste.acessoInsercao);
  }
  Testa(pagina);

  // Pesquisando 100 alunos para teste
  while (fscanf(itensBusca, "%d %s %d %d %d %d", &matricula, nome, &nota1, &nota2, &nota3, &notaFinal) != EOF) {
    // Zerando o contador de acesso e comparações
    iniTeste(&teste);
    Pesquisa(matricula, pagina,&teste);
    alturaB(&pagina, &teste);
    fprintf(arqSaidaB, "%d %d %d\n", teste.altura, teste.comparacaoPesquisa, teste.acessoPesquisa);
  }
  Testa(pagina);

  // Removendo 100 alunos para teste
  while (fscanf(itensRemocao, "%d %s %d %d %d %d", &matricula, nome, &nota1, &nota2, &nota3, &notaFinal) != EOF) {
    // Zerando o contador de acesso e comparações
    iniTeste(&teste);
    Retira(matricula,&pagina, &teste);
    alturaB(&pagina, &teste);
    fprintf(arqSaidaR, "%d %d %d\n", teste.altura, teste.comparacaoRemocao, teste.acessoRemocao);
  }

  Testa(pagina);
  system("cls");
  system("clear");
  printf("TESTES FINALIZADOS, RESULTADOS COM M VIGENTE NOS ARQUIVOS DE SAIDA\n");
  printf("\nINSERCAO, REMOCAO E BUSCA MANUAIS \n");
  // Menu para operações manuais na estrutura
  while (1) {
    printf("\n1-INSERIR 2-REMOVER 3-BUSCAR 0-SAIR\n");
    scanf("%d", &op);
    switch (op) {
      case 1:
        printf("INSERIR:\n");
        setbuf(stdin, NULL);
        printf("NOME:          "); scanf("%[a-z A-Z]s", nome); ;
        printf("MATRICULA:     "); scanf("%d",&matricula);
        while (1) {
          printf("PRIMEIRA NOTA: "); scanf("%d",&nota1);
          printf("SEGUNDA  NOTA: "); scanf("%d",&nota2);
          printf("TERCEIRA NOTA: "); scanf("%d",&nota3);
          if(nota1>33||nota2>33||nota3>34){
            printf("NOTAS INVALIDAS...TENTE NOVAMENTE\n" );
          }else{
            break;
          }
        }
        insereAluno(&aluno,nome,matricula,nota1, nota2, nota3, nota1+nota2+nota3);
        Insere(aluno, &pagina, &teste);
        break;
      case 2:
        printf("REMOVER:\n");
        printf("MATRICULA:     "); scanf("%d",&matricula);
        Retira(matricula, &pagina, &teste);
        break;
      case 3:
        printf("BUSCAR:\n");
        printf("MATRICULA:     "); scanf("%d",&matricula);
        Pesquisa(matricula, pagina, &teste);
        break;
      case 4:
        // Operação extra (oculta no menu) que faz a impressão dos registros da árvore
        Imprime(pagina);
        break;
      case 0:
        flag = 1;
        break;
      default: printf("VALOR INVALIDO, TENTE NOVAMENTE\n");op=0;
    }
    if(!flag){

    }else{
        // Fechando arquivos
        fclose(itensBusca);
        fclose(itensInsercao);
        fclose(itensRemocao);
        fclose(arqAlunos);
        fclose(arqSaidaI);
        fclose(arqSaidaR);
        fclose(arqSaidaB);
        printf("PROGRAMA FINALIZADO\n");
        return 0;
    }
  }
}
