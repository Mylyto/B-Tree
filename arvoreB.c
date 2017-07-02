// Adriano Martins: 2640
// Antônio Almeida: 2632

#include "arvoreB.h"
#include "teste.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Função responsável por inicializar a àrvore, atribuindo NULL à raiz
void Inicializa(TPagina ** pag){
  *pag = NULL;
}
// Função responsável por calcular a altura da árvore
void alturaB(TPagina ** raiz, TTeste * t){
  int altura = 0;// Contador usado para percorrer árvore de acordo com a chave à ser procurada
  alt(raiz, &altura, t);
  alturaTeste(t, altura);// Atribui a altura à variável do TAD Teste
  //printf("%d\n",altura );
}
// Função auxiliar que percorre a árvore incrementando a altura
void alt(TPagina ** pag, int * altura, TTeste * t){
  if((*pag) == NULL){// Se a página atual for nula, decrementa 1
    *altura= *altura -1;
    return;
  }else{/// Enquanto não for nula, percorre sub-árvore à esquerda incrementando a altura
    *altura= *altura + 1;
    alt(&(*pag)->vecFilho[0], altura, t);
    return;
  }
}

void Pesquisa(int mat, TPagina * ap, TTeste * t){
  TAluno a;
  Pesquisa_(mat,&a,ap,t);
  if(a.matricula==-1)
    printf("MATRICULA NÃO ENCONTRADA\n");
  else
    printf("ALUNO: %s MATRICULA: %d NOTA FINAL: %d\n", a.nome, a.matricula, a.notaF);
}

// Pesquisa por um aluno que foi cadastrado através da chave (matrícula)
void Pesquisa_(int mat, TAluno *x, TPagina * ap, TTeste * t){
  long i = 1;// Contador usado para percorrer árvore de acordo com a chave à ser procurada
  if (ap == NULL){// Caso ainda não tenha encontrado e o próximo apontador seja nulo
    x->matricula = -1;
    return;
  }
  // Enquanto a matrícula procurada é maior que a chave atual e o contador menor que a qtde de itens na página
  while (i < ap->qtd && mat > ap->vecAluno[i-1].matricula)
    i++;
  comparacaoPesquisa(t,i);
  if (mat == ap->vecAluno[i-1].matricula){// Matrícula encontrada
    comparacaoPesquisa(t,1);
    *x = ap->vecAluno[i-1];
    return;
  }
  // Caso contrário, se a matrícula for menor, chama recursivamente para filho i-1
  if (mat < ap->vecAluno[i-1].matricula){
    comparacaoPesquisa(t,2);
    if(ap->vecFilho[i-1]!=NULL)acessoPesquisa(t);
    Pesquisa_(mat, x, ap->vecFilho[i-1],t);
  }else{
    comparacaoPesquisa(t,3);
    if(ap->vecFilho[i-1]!=NULL)acessoPesquisa(t);
    Pesquisa_(mat, x, ap->vecFilho[i],t);// Chegou ao fim da página e a chave procurada ainda é maior, portanto chama recursivamente para o último filho
  }
}
// Função responsável por inserir registro na página e mantê-la ordenada
void InsereNapagina(TPagina * ap,TAluno aluno, TPagina * apDir, TTeste * t){

  short naoAchouPosicao;
  int k;
  k = ap->qtd;
  naoAchouPosicao = (k > 0);
    // Percorre de trás para frente, quando a chave da posição atual for menor é feita a inserção
  while (naoAchouPosicao){
    comparacaoRemocao(t,1);
    comparacaoInsercao(t,1);
    if (aluno.matricula >= ap->vecAluno[k-1].matricula){
      // Verifica se a posição foi encontrada
        naoAchouPosicao = FALSE;
        break;
      }
      ap->vecAluno[k] = ap->vecAluno[k-1];
      ap->vecFilho[k+1] = ap->vecFilho[k];
      k--;
      if (k < 1) naoAchouPosicao = FALSE;// Verifica se chegou no início da página
    }
    // Registro é inserido na página
  ap->vecAluno[k] = aluno;
  ap->vecFilho[k+1] = apDir;
  ap->qtd++;
}
// Função auxilar na inserção de alunos
void Ins(TAluno aluno, TPagina * ap, short *Cresceu, TAluno *alunoRetorno,  TPagina ** apRetorno, TTeste * t){
  long i = 1;// Contador é declarado e utilizado para identificar ponto de inserção na página
  long j;
  TPagina * apTemp;
  if (ap == NULL){
    *Cresceu = TRUE; (*alunoRetorno) = aluno; (*apRetorno) = NULL;
    return;
  }
  while (i < ap->qtd && aluno.matricula > ap->vecAluno[i-1].matricula)
    i++;
  comparacaoInsercao(t,i);
  if (aluno.matricula == ap->vecAluno[i-1].matricula){// Verificando se a matricula já existe
    comparacaoInsercao(t,1);
    printf("MATRICULA INVALIDA\n");
    *Cresceu = FALSE;
    return;
  }
  if (aluno.matricula < ap->vecAluno[i-1].matricula)
      i--;
  comparacaoInsercao(t,2);
  if(ap->vecFilho[i]!=NULL)
      acessoInsercao(t);
  Ins(aluno, ap->vecFilho[i], Cresceu, alunoRetorno, apRetorno,t);
  if (!*Cresceu)
      return; // Verifica se a árvore não precisa crescer
  if (ap->qtd < MM){// Verifica se há espaÇo no nó para inserir na página
      InsereNapagina(ap, *alunoRetorno, *apRetorno,t);
      *Cresceu = FALSE;
      return;
  }// Caso não haja, aloca-se uma pagina temporãria
  /* Overflow: Pagina tem que ser dividida */
  apTemp = (TPagina *)malloc(sizeof(TPagina));
  acessoInsercao(t);
  apTemp->qtd = 0;  apTemp->vecFilho[0] = NULL;
  if (i < M + 1){ // Verifica se o item está na esquerda ou direita para pegar o item do meio
    InsereNapagina(apTemp, ap->vecAluno[MM-1], ap->vecFilho[MM],t);
    ap->qtd--;
    InsereNapagina(ap, *alunoRetorno, *apRetorno,t);
  }else{
    InsereNapagina(apTemp, *alunoRetorno, *apRetorno,t);
  }
  // Reinsere os itens da divisão de página na página temporária
  for (j = M + 2; j <= MM; j++)
    InsereNapagina(apTemp, ap->vecAluno[j-1], ap->vecFilho[j],t);
  ap->qtd = M;
  apTemp->vecFilho[0] = ap->vecFilho[M+1];
  *alunoRetorno = ap->vecAluno[M];
  *apRetorno = apTemp;
}
// Função responsável por realizar a inserção de alunos
void Insere(TAluno aluno, TPagina * *ap, TTeste * t){
  short Cresceu;// Flag para sinalizar crescimento vertical da árvore
  TAluno alunoRetorno;
  TPagina *apRetorno, *apTemp;
  Ins(aluno, *ap, &Cresceu, &alunoRetorno, &apRetorno,t);
  if (Cresceu){// Verifica se a àrvore cresceu para cima
    apTemp = (TPagina *)malloc(sizeof(TPagina));// Aloca página temporária
    acessoInsercao(t);
    apTemp->qtd = 1;
    apTemp->vecAluno[0] = alunoRetorno;// O elemento do meio se torna o primeiro
    apTemp->vecFilho[1] = apRetorno;// Filho da esquerda é página de retorno na recursão
    apTemp->vecFilho[0] = *ap;// Antiga raiz se torna filho à esquerda
    *ap = apTemp;// Página temporária se torna a nova raiz
    acessoInsercao(t);
  }
}
// Auxilia na remoção reorganizando a àrvore de forma que suas propriedades sejam mantidas
void Reconstitui(TPagina * apPag, TPagina * apPai, int PosPai, short *Diminuiu, TTeste * t){
  TPagina *Aux;  long DispAux, j;
  if (PosPai < apPai->qtd){
    Aux = apPai->vecFilho[PosPai+1];  DispAux = (Aux->qtd - M + 1) / 2;
    apPag->vecAluno[apPag->qtd] = apPai->vecAluno[PosPai];
    apPag->vecFilho[apPag->qtd + 1] = Aux->vecFilho[0];  apPag->qtd++;
    if (DispAux > 0){
      for (j = 1; j < DispAux; j++)
        InsereNapagina(apPag, Aux->vecAluno[j-1], Aux->vecFilho[j],t);
      apPai->vecAluno[PosPai] = Aux->vecAluno[DispAux-1];  Aux->qtd -= DispAux;
      for (j = 0; j < Aux->qtd; j++) Aux->vecAluno[j] = Aux->vecAluno[j + DispAux];
      for (j = 0; j <= Aux->qtd; j++) Aux->vecFilho[j] = Aux->vecFilho[j + DispAux];
      *Diminuiu = FALSE;
    }else {
      for (j = 1; j <= M; j++)
          InsereNapagina(apPag, Aux->vecAluno[j-1], Aux->vecFilho[j],t);
        free(Aux);
        for (j = PosPai + 1; j < apPai->qtd; j++){
          apPai->vecAluno[j-1] = apPai->vecAluno[j];
	        apPai->vecFilho[j] = apPai->vecFilho[j+1];
	      }
        apPai->qtd--;
        if (apPai->qtd >= M) *Diminuiu = FALSE;
      }
  } else {
    Aux = apPai->vecFilho[PosPai-1]; DispAux = (Aux->qtd - M + 1) / 2;
    for (j = apPag->qtd; j >= 1; j--)
      apPag->vecAluno[j] = apPag->vecAluno[j-1];
    apPag->vecAluno[0] = apPai->vecAluno[PosPai-1];
    for (j = apPag->qtd; j >= 0; j--)
      apPag->vecFilho[j+1] = apPag->vecFilho[j];
    apPag->qtd++;
      if (DispAux > 0){
        for (j = 1; j < DispAux; j++)
          InsereNapagina(apPag, Aux->vecAluno[Aux->qtd - j],Aux->vecFilho[Aux->qtd - j + 1],t);
        apPag->vecFilho[0] = Aux->vecFilho[Aux->qtd - DispAux + 1];
        apPai->vecAluno[PosPai-1] = Aux->vecAluno[Aux->qtd - DispAux];
        Aux->qtd -= DispAux;  *Diminuiu = FALSE;
      }else{
        for (j = 1; j <= M; j++)
            InsereNapagina(Aux, apPag->vecAluno[j-1], apPag->vecFilho[j],t);
        free(apPag);
        apPai->qtd--;
        if (apPai->qtd >= M)  *Diminuiu = FALSE;
        }
    }
}
// Função que faz a troca de registros caso o aluno à ser removido não esteja numa página folha
void Antecessor(TPagina * ap, int Ind,TPagina * apPai, short *Diminuiu, TTeste * t){
  if (apPai->vecFilho[apPai->qtd] != NULL){
    if(apPai->vecFilho[apPai->qtd]!=NULL)
      acessoRemocao(t);
    Antecessor(ap, Ind, apPai->vecFilho[apPai->qtd], Diminuiu,t);
    if (*Diminuiu)
    Reconstitui(apPai->vecFilho[apPai->qtd], apPai, apPai->qtd, Diminuiu,t);
    return;
  }
  ap->vecAluno[Ind-1] = apPai->vecAluno[apPai->qtd - 1];
  apPai->qtd--;  *Diminuiu = (apPai->qtd < M);
}
// Função auxiliar que percorre àrvore a procura da página onde se encontra registro à ser removido
void Ret(int Ch, TPagina ** ap, short *Diminuiu, TTeste * t){
  long j, Ind = 1;
  TPagina * Pag;// Árvore auxiliar utilizada como cópia para percorrer
  if (*ap == NULL){// Chegou ao fim sem encontrar ou a árvore está vazia
    printf("MATRICULA NAO ENCONTRADA\n"); *Diminuiu = FALSE;
    return;
  }
  Pag = *ap;
  // Percorre a página incrementando índice utilizado na recursão
  while (Ind < Pag->qtd && Ch > Pag->vecAluno[Ind-1].matricula)
    Ind++;
  comparacaoRemocao(t,Ind);
  if (Ch == Pag->vecAluno[Ind-1].matricula){// Caso o aluno seja encontrado
    comparacaoRemocao(t,1);
    if (Pag->vecFilho[Ind-1] == NULL){// Verifica se é folha
      Pag->qtd--;// Decrementa quantidade de registros na página
      *Diminuiu = (Pag->qtd < M);// Flag recebe 1 caso a página fique com menos de M registros
      for (j = Ind; j <= Pag->qtd; j++){// Laço rearranja o vetor da página após remoção
        Pag->vecAluno[j-1] = Pag->vecAluno[j];
        Pag->vecFilho[j] = Pag->vecFilho[j+1];
      }
      return;
    }
    /* TPagina nao e folha: trocar com antecessor */
    acessoRemocao(t);
    Antecessor(*ap, Ind, Pag->vecFilho[Ind-1], Diminuiu,t);// Se não for folha movimenta o antecessor
    if (*Diminuiu)
      Reconstitui(Pag->vecFilho[Ind-1], *ap, Ind - 1, Diminuiu,t);// Verifica se diminuiu para fazer a reconstituição
    return;
  }
  comparacaoRemocao(t,2);
  if (Ch > Pag->vecAluno[Ind-1].matricula)
    Ind++;// Se a matrícula for maior percorre o filho à direita do pai
  acessoRemocao(t);
  Ret(Ch, &Pag->vecFilho[Ind-1], Diminuiu,t);
  if (*Diminuiu)
    Reconstitui(Pag->vecFilho[Ind-1], *ap, Ind - 1, Diminuiu,t);// Verifica se diminuiu para fazer a reconstituição
}
// Função responsável por realizar a remoção à partir da matrícula do aluno
void Retira(int Ch, TPagina * *ap, TTeste * t){
  short Diminuiu;
  TPagina * Aux;
  Ret(Ch, ap, &Diminuiu,t);
  if (Diminuiu && (*ap)->qtd == 0){// Verifica se a página ficou vazia e libera memória
    Aux = *ap;
    *ap = Aux->vecFilho[0];
    acessoRemocao(t);
    free(Aux);
  }
}







void ImprimeI(TPagina * p, int nivel){
  long i;
  if (p == NULL) return;
  printf("Nivel %d : ", nivel);
  for (i = 0; i < p->qtd; i++)
    printf("%ld ",(long)p->vecAluno[i].matricula);
  putchar('\n');
  nivel++;
  for (i = 0; i <= p->qtd; i++)
    ImprimeI(p->vecFilho[i], nivel);
}

void Imprime(TPagina * p){
  int  n = 0; ImprimeI(p, n);
}

void TestaI(TPagina * p, int pai, short direita){
  int i;
  int antecessor = 0;
  if (p == NULL) return;
  if (p->vecAluno[0].matricula > pai && direita == FALSE){
    printf("Erro: filho %d maior que pai %d\n", p->vecAluno[0].matricula, pai);
    return;
  }
  for (i = 0; i < p->qtd; i++){
    if (p->vecAluno[i].matricula <= antecessor){
      printf("Erro: irmao %ld maior que irmao a esquerda %d\n",
        (long)p->vecAluno[i].matricula, antecessor);
        return;
      }
      antecessor = p->vecAluno[i].matricula;
    }
  for (i = 0; i < p->qtd; i++)
    TestaI(p->vecFilho[i], p->vecAluno[i].matricula, FALSE);
  TestaI(p->vecFilho[p->qtd], p->vecAluno[i].matricula, TRUE);
}

void Testa(TPagina * p){
  int i;
  if (p == NULL) return;
  for (i = 0; i < p->qtd; i++)
    TestaI(p->vecFilho[i], p->vecAluno[i].matricula, FALSE);
  TestaI(p->vecFilho[p->qtd], p->vecAluno[i].matricula, TRUE);
}
