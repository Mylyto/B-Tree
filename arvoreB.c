// Adriano Martins: 2640
// Antônio Almeida: 2632

#include "arvoreB.h"
#include "teste.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Função responsável por inicializar a àrvore, atribuindo NULL à raiz
void inicializaB(TPagina ** p){
  *p = NULL;
}

// Pesquisa por um aluno que foi cadastrado através da chave (matrícula)
void buscaB(TPagina * pag, int mat, TTeste * t){
  int i = 1; // Contador usado para percorrer árvore de acordo com a chave à ser procurada

  if(pag==NULL){ // Caso ainda não tenha encontrado e o próximo apontador seja nulo
    printf("A %d matricula nao foi cadastrada...", mat);
  }else{ // Enquanto a matrícula procurada é maior que a chave atual e o contador menor que a qtde de itens na página
    while (mat > pag->vecAluno[i-1].matricula && i < pag->qtd) {
      comparacaoPesquisa(t);
      i++;
    }
    if(mat == pag->vecAluno[i-1].matricula){ // Matrícula encontrada
      comparacaoPesquisa(t);
      printf("Matricula Encontrada: %d   Aluno: %s   Nota Final: %d\n",
      pag->vecAluno[i-1].matricula, pag->vecAluno[i-1].nome,pag->vecAluno[i-1].notaF );
      return;
    }else if(mat < pag->vecAluno[i-1].matricula ){ // Caso contrário, se a matrícula for menor, chama recursivamente para filho i-1
      comparacaoPesquisa(t);
      acessoPesquisa(t);
      buscaB(pag->filho[i-1], mat, t);
    }else{ // Chegou ao fim da página e a chave procurada ainda é maior, portanto chama recursivamente para o último filho
      comparacaoPesquisa(t);
      acessoPesquisa(t);
      buscaB(pag->filho[i], mat, t);
    }
  }
}

// Função responsável por calcular a altura da árvore
void alturaB(TPagina ** raiz, TTeste * t){
  int altura = 0, i;

  alt(raiz, &altura, t);
  for(i = 0; i < altura; i++) // Atribui a altura à variável do TAD Teste
    alturaTeste(t);
  printf("Altura %d\n", altura);
}

// Função auxiliar que percorre a árvore incrementando a altura
void alt(TPagina ** pag, int * altura, TTeste * t){
  if((*pag) == NULL){ // Se a página atual for nula, decrementa 1
    *altura= *altura -1;
    return;
  }else{ // Enquanto não for nula, percorre sub-árvore à esquerda incrementando a altura
    *altura= *altura + 1;
    alt(&(*pag)->filho[0], altura, t);
    return;
  }
}

// Função responsável por realizar a inserção de alunos
void insereB(TAluno a, TPagina ** pag){
  int cresceu; // Flag para sinalizar crescimento vertical da árvore
  TAluno meio;
  TPagina * pagRetorno;
  TPagina * pagTemp;

  ins(a, pag, &cresceu, &meio, &pagRetorno);
  if(cresceu){ // Verifica se a àrvore cresceu para cima
    pagTemp = (TPagina*)malloc(sizeof(TPagina)); // Aloca página temporária
    if(pagTemp == NULL) printf("Erro em Alocar\n");
    pagTemp->qtd = 1;
    pagTemp->vecAluno[0] = meio; // O elemento do meio se torna o primeiro
    pagTemp->filho[1] = pagRetorno; // Filho da esquerda é página de retorno na recursão
    pagTemp->filho[0] = *pag; // Antiga raiz se torna filho à esquerda
    *pag = pagTemp; // Página temporária se torna a nova raiz
  }
}

// Função auxilar na inserção de alunos
void ins(TAluno a, TPagina ** pag, int * cresceu, TAluno *meio, TPagina ** pagRetorno){
  TPagina * pagTemp;
  int i, j;

  if(*pag == NULL){
    *cresceu = 1;
    *meio = a;
    *pagRetorno = NULL;
    return;
  }
  i = 1; // Contador é declarado e utilizado para identificar ponto de inserção na página
  while ((i< (*pag)->qtd) && a.matricula  > (*pag)->vecAluno[i-1].matricula){
    i++;
  }
  if(a.matricula == (*pag)->vecAluno[i-1].matricula){ // Verificando se a matricula já existe
    printf("Matricula já cadastrada\n");
    *cresceu = 0;
    return;
  }
  if(a.matricula<(*pag)->vecAluno[i-1].matricula){ // Se for menor vai para a esquerda
      ins(a, &(*pag)->filho[i-1], cresceu, meio, pagRetorno);
  }else{ // Caso contrário vai para a direita
      ins(a, &(*pag)->filho[i], cresceu, meio, pagRetorno);
    }
  if(!*cresceu) // Verifica se a árvore não precisa crescer
      return;
  if((*pag)->qtd < 2*m){ // Verifica se há espaÇo no nó para inserir na página
    inserePagina(&(*pag), *meio, pagRetorno);
    *cresceu = 0;
    return;
  } // Caso não haja, aloca-se uma pagina temporãria
  pagTemp = (TPagina*)malloc(sizeof(TPagina));
  pagTemp->qtd = 0;
  pagTemp->filho[0] = NULL;
  if(i <= m+1){ // Verifica se o item está na esquerda ou direita para pegar o item do meio
    inserePagina(&pagTemp, (*pag)->vecAluno[2*m-1], &(*pag)->filho[2*m]);
    (*pag)->qtd--;
    inserePagina(&(*pag), *meio, pagRetorno);
  }else{
    inserePagina(&pagTemp, *meio, pagRetorno);
  }
  for(j = m+2; j <= 2*m; j++){ // Reinsere os itens da divisão de página na página temporária
    inserePagina(&pagTemp, (*pag)->vecAluno[j-1], &(*pag)->filho[j]);
  }
  (*pag)->qtd = m;
  pagTemp->filho[0] = (*pag)->filho[m+1];
  *meio = (*pag)->vecAluno[m];
  *pagRetorno = pagTemp;
}

// Função responsável por inserir registro na página e mantê-la ordenada
void inserePagina(TPagina ** pag, TAluno a, TPagina ** pagDir){
  int pos, boolean;

  pos = (*pag)->qtd;
  boolean = pos > 0;
  // Percorre de trás para frente, quando a chave da posição atual for menor é feita a inserção
  while (boolean) {
    if(a.matricula >= (*pag)->vecAluno[pos-1].matricula){ // Verifica se a posição foi encontrada
      boolean = 0;
      break;
    }
    (*pag)->vecAluno[pos] = (*pag)->vecAluno[pos-1];
    (*pag)->filho[pos+1] = (*pag)->filho[pos];
    pos--;
    if(pos < 1) // Verifica se chegou no início da página
      boolean = 0;
  }
  // Registro é inserido na página
  (*pag)->vecAluno[pos] = a;
  (*pag)->filho[pos+1] = *pagDir;
  (*pag)->qtd++;
}

// Função responsável por realizar a remoção à partir da matrícula do aluno
void removeB(TPagina ** pag, int mat){
  int diminui;
  TPagina ** aux;

  rem(pag, mat, &diminui);
  if(diminui && (*pag)->qtd == 0){ // Verifica se a página ficou vazia e libera memória
    aux = pag;
    *pag = (*aux)->filho[0];
    free(aux);
  }
}

// Função auxiliar que percorre àrvore a procura da página onde se encontra registro à ser removido
void rem(TPagina ** pag, int mat, int * diminui){
  int j, ind = 1;
  TPagina ** aux; // Árvore auxiliar utilizada como cópia para percorrer

  if(*pag == NULL){ // Chegou ao fim sem encontrar ou a árvore está vazia
    printf("Registro não encontrado\n");
    *diminui = 0;
    return;
  }
  aux = pag;
  // Percorre a página incrementando índice utilizado na recursão
  while (ind < (*aux)->qtd && mat > (*aux)->vecAluno[ind - 1].matricula)
    ind++;
  if(mat == (*aux)->vecAluno[ind - 1].matricula){ // Caso o aluno seja encontrado
    if((*aux)->filho[ind-1] == NULL){ // Verifica se é folha
      (*aux)->qtd--; // Decrementa quantidade de registros na página
      *diminui = ((*aux)->qtd < m); // Flag recebe 1 caso a página fique com menos de M registros
      for(j = ind; j <= (*aux)->qtd; j++){ // Laço rearranja o vetor da página após remoção
        (*aux)->vecAluno[j-1] = (*aux)->vecAluno[j];
        (*aux)->filho[j] = (*aux)->filho[j+1];
      }
      return;
    }
    antecessor(pag, ind, &(*aux)->filho[ind -1], diminui); // Se não for folha movimenta o antecessor
    if(*diminui) // Faz a reconstituição caso tenha diminuído
      reconstitui(&(*aux)->filho[ind -1], pag, ind - 1, diminui);
    return;
  }
  if(mat > (*aux)->vecAluno[ind - 1].matricula) // Se a matrícula for maior percorre o filho à direita do pai
    ind++;
  rem(&(*aux)->filho[ind-1], mat, diminui);
  if(*diminui) // Verifica se diminuiu para fazer a reconstituição
    reconstitui(&(*aux)->filho[ind -1], pag, ind - 1, diminui);
}

// Função que faz a troca de registros caso o aluno à ser removido não esteja numa página folha
void antecessor(TPagina ** pag, int ind, TPagina ** pagPai, int * diminui){
  if((*pagPai)->filho[(*pagPai)->qtd] != NULL){
    antecessor(pag, ind, &(*pagPai)->filho[(*pagPai)->qtd], diminui);
    if(*diminui)
      reconstitui(&(*pagPai)->filho[(*pagPai)->qtd], pagPai, (*pagPai)->qtd, diminui);
      return;
  }
  (*pag)->vecAluno[ind-1] = (*pagPai)->vecAluno[(*pagPai)->qtd - 1];
  (*pagPai)->qtd--;
  *diminui = ((*pagPai)->qtd < m);
}

// Auxilia na remoção reorganizando a àrvore de forma que suas propriedades sejam mantidas
void reconstitui(TPagina ** pag, TPagina ** pagPai, int posPai, int * diminui){
  TPagina * aux;
  int dispAux, j;

  if(posPai < (*pagPai)->qtd){
    aux = (*pagPai)->filho[posPai+1];
    dispAux = (aux->qtd - m + 1) / 2;
    (*pag)->vecAluno[(*pag)->qtd] = (*pag)->vecAluno[posPai];
    (*pag)->filho[(*pag)->qtd+1]= aux->filho[0];
    (*pag)->qtd++;
    if(dispAux > 0){
      for(j = 1; j < dispAux; j++)
        inserePagina(pag, aux->vecAluno[j-1], &aux->filho[j]);
      (*pagPai)->vecAluno[posPai] = aux->vecAluno[dispAux-1];
      aux->qtd-=dispAux;
      for(j = 0; j <= aux->qtd; j++)
         aux->vecAluno[j] = aux->vecAluno[j+dispAux];
      for(j = 0; j <= aux->qtd; j++)
         aux->filho[j] = aux->filho[j+dispAux];
      *diminui = 0;
    }else{
      for(j = 1; j <= m; j++)
        inserePagina(pag, aux->vecAluno[j-1], &aux->filho[j]);
      free(aux);
      for(j = posPai; j <= (*pagPai)->qtd; j++){
          (*pagPai)->vecAluno[j-1] = (*pagPai)->vecAluno[j];
          (*pagPai)->filho[j] = (*pagPai)->filho[j+1];
      }
      (*pagPai)->qtd--;
      if((*pagPai)->qtd >= m) *diminui = 0;
    }
  }
}
