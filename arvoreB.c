#include "arvoreB.h"
#include "teste.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void inicializaB(TPagina ** p){
  *p = NULL;
}

void buscaB(TPagina * pag, int mat, TTeste * t){
  int i = 1;
  if(pag==NULL){
    printf("A %d matricula não foi cadastrada...", mat);
  }else{
    while (mat > pag->vecAluno[i-1].matricula && i < pag->qtd) {
      comparacaoPesquisa(t);
      i++;
    }
    if(mat == pag->vecAluno[i-1].matricula){
      comparacaoPesquisa(t);
      printf("Matricula Encontrada: %d   Aluno: %s   Nota Final: %d\n",
      pag->vecAluno[i-1].matricula, pag->vecAluno[i-1].nome,pag->vecAluno[i-1].notaF );
      return;
    }else if(mat < pag->vecAluno[i-1].matricula ){
      comparacaoPesquisa(t);
      acessoPesquisa(t);
      buscaB(pag->filho[i-1], mat, t);
    }else{
      comparacaoPesquisa(t);
      acessoPesquisa(t);
      buscaB(pag->filho[i], mat, t);
    }
  }
}

void alturaB(TPagina ** raiz, TTeste * t){
  int altura = 0, i;
  alt(raiz, &altura, t);
  for(i=0;i<altura; i++)
    alturaTeste(t);
  printf("Altura %d\n", altura);
}

void alt(TPagina ** pag, int * altura, TTeste * t){
  if((*pag) == NULL){
    *altura= *altura -1;// CASO O FILHO SEJA NULO, DIMINUI A ALTURA EM 1
    return;
  }else{//ENQUANTO A ÁRVORE NÃO FOR NULA PERCORRE A RAIZ SEMPRE A ESQUERDA
    *altura= *altura + 1; // INCREMENTA A ALTURA
    alt(&(*pag)->filho[0], altura, t);
    return;
  }
}

void insereB(TAluno a, TPagina ** pag){
  int cresceu;
  TAluno meio;
  TPagina * pagRetorno;
  TPagina * pagTemp;
  ins(a, pag, &cresceu, &meio, &pagRetorno);
  if(cresceu){ // VERIFICA SE A ÁRVORE CRESCEU PARA CIMA
    pagTemp = (TPagina*)malloc(sizeof(TPagina)); // ALOCA UMA PAGINA TEMPORARIA
    if(pagTemp == NULL) printf("Erro em Alocar\n");
    pagTemp->qtd = 1;
    pagTemp->vecAluno[0] = meio; // O ELEMENTO DO MEIO VIRA O PRIMEIRO ITEM DA PAG
    pagTemp->filho[1] = pagRetorno; // O FILHO A ESQUERDA É A PAGINA DE RETORNADA NA RECURSÃO
    pagTemp->filho[0] = *pag; // A ANTIGA RAIZ VIRA O FILHO A ESQUERDA
    *pag = pagTemp; // A PAGINA TEMPORARIAVIRA A NOVA RAIZ
  }
}

void ins(TAluno a, TPagina ** pag, int * cresceu, TAluno *meio, TPagina ** pagRetorno){
  TPagina * pagTemp;
  int i, j;
  if(*pag == NULL){
    *cresceu = 1;
    *meio = a;
    *pagRetorno = NULL;
    return;
  }
  i = 1;
  while ((i< (*pag)->qtd) && a.matricula  > (*pag)->vecAluno[i-1].matricula){ // PERCORRENDO O VECTOR DA PAGINA
    i++;
  }
  if(a.matricula == (*pag)->vecAluno[i-1].matricula){ // VERIFICANDO SE A MATRICULA JÁ EXISTE
    printf("Matricula já cadastrada\n");
    *cresceu = 0;
    return;
  }
  if(a.matricula<(*pag)->vecAluno[i-1].matricula){ // SE FOR MENOR VAI PARA A ESQUERDA
      ins(a, &(*pag)->filho[i-1], cresceu, meio, pagRetorno);
  }else{ //CASO CONTRÁRIO VAI PARA A DIREITA
      ins(a, &(*pag)->filho[i], cresceu, meio, pagRetorno);
    }
  if(!*cresceu) // VERIFICA SE A ÁRVORE NÃO PRECISA CRESCER
      return;
  if((*pag)->qtd < 2*m){ //VERIFICA SE HÁ ESPAÇO NO NÓ PARA INSERIR NA PAGINA
    inserePagina(&(*pag), *meio, pagRetorno);
    *cresceu = 0;
    return;
  } // CASO NÃO HAJA, ALOCA-SE UMA PAGINA TEMPORÁRIA
  pagTemp = (TPagina*)malloc(sizeof(TPagina));
  pagTemp->qtd = 0;
  pagTemp->filho[0] = NULL;
  if(i<= m+1){ // VERIFICA SE O ITEM ESTÁ NA ESQUERDA OU DIREITA PARA PEGAR O ITEM DO MEIO
    inserePagina(&pagTemp, (*pag)->vecAluno[2*m-1], &(*pag)->filho[2*m]);
    (*pag)->qtd--;
    inserePagina(&(*pag), *meio, pagRetorno);
  }else{
    inserePagina(&pagTemp, *meio, pagRetorno);
  }
  for(j=m+2;j<=2*m;j++){ // REINSERE OS ITENS DA DIVISÃO DE PAGINA NA PAG TEMP
    inserePagina(&pagTemp, (*pag)->vecAluno[j-1], &(*pag)->filho[j]);
  }
  (*pag)->qtd = m;
  pagTemp->filho[0] = (*pag)->filho[m+1];
  *meio = (*pag)->vecAluno[m];
  *pagRetorno = pagTemp;
}

void inserePagina(TPagina ** pag, TAluno a, TPagina ** pagDir){
  int pos, boolean;
  pos = (*pag)->qtd;
  boolean = pos > 0;
  while (boolean) { // OREDENA O VETOR E FAZ A TROCA DOS FILHOS
    if(a.matricula >= (*pag)->vecAluno[pos -1].matricula){
      boolean = 0;
      break;
    }
    (*pag)->vecAluno[pos] = (*pag)->vecAluno[pos-1];
    (*pag)->filho[pos+1] = (*pag)->filho[pos];
    pos--;
    if(pos < 1)
      boolean = 0;
  }
  //INSERE O REGISTRO NA PAGINA
  (*pag)->vecAluno[pos] = a;
  (*pag)->filho[pos+1] = *pagDir;
  (*pag)->qtd++;
}


void removeB(TPagina ** pag, int mat){
  int diminui;
  TPagina ** aux;
  rem(pag, mat, &diminui);
  if(diminui && (*pag)->qtd == 0){
    aux = pag;
    *pag = (*aux)->filho[0];
    free(aux);
  }
}

void rem(TPagina ** pag, int mat, int * diminui){
  int j, ind = 1;
  TPagina ** aux;
  if(*pag == NULL){
    printf("Registro não encontrado\n");
    *diminui = 0;
    return;
  }
  aux = pag;
  while (ind < (*aux)->qtd && mat > (*aux)->vecAluno[ind - 1].matricula)
    ind++;
  if(mat == (*aux)->vecAluno[ind - 1].matricula){
    if((*aux)->filho[ind-1] == NULL){
      (*aux)->qtd--;
      *diminui = ((*aux)->qtd < m);
      for(j = ind; j <= (*aux)->qtd; j++){
        (*aux)->vecAluno[j-1] = (*aux)->vecAluno[j];
        (*aux)->filho[j] = (*aux)->filho[j+1];
      }
      return;
    }
    antecessor(pag, ind, &(*aux)->filho[ind -1], diminui);
    if(*diminui)
      recostitui(&(*aux)->filho[ind -1], pag, ind - 1, diminui);
    return;
  }
  if(mat > (*aux)->vecAluno[ind - 1].matricula)
    ind++;
  rem(&(*aux)->filho[ind-1], mat, diminui);
  if(*diminui)
    recostitui(&(*aux)->filho[ind -1], pag, ind - 1, diminui);
}

void antecessor(TPagina ** pag, int ind, TPagina ** pagPai, int * diminui){
  if((*pagPai)->filho[(*pagPai)->qtd] != NULL){
    antecessor(pag, ind, &(*pagPai)->filho[(*pagPai)->qtd], diminui);
    if(*diminui)
      recostitui(&(*pagPai)->filho[(*pagPai)->qtd], pagPai, (*pagPai)->qtd, diminui);
      return;
  }
  (*pag)->vecAluno[ind-1] = (*pagPai)->vecAluno[(*pagPai)->qtd - 1];
  (*pagPai)->qtd--;
  *diminui = ((*pagPai)->qtd < m);
}

void recostitui(TPagina ** pag, TPagina ** pagPai, int posPai, int * diminui){
  TPagina * aux;
  int dispAux, j;
  if(posPai < (*pagPai)->qtd){
    aux = (*pagPai)->filho[posPai+1];
    dispAux = (aux->qtd - m + 1) / 2;
    (*pag)->vecAluno[(*pag)->qtd] = (*pag)->vecAluno[posPai];
    (*pag)->filho[(*pag)->qtd+1]= aux->filho[0];
    (*pag)->qtd++;
    if(dispAux > 0){
      for(j=1;j<dispAux;j++)
        inserePagina(pag, aux->vecAluno[j-1], &aux->filho[j]);
      (*pagPai)->vecAluno[posPai] = aux->vecAluno[dispAux-1];
      aux->qtd-=dispAux;
      for(j=0;j<=aux->qtd;j++)
         aux->vecAluno[j] = aux->vecAluno[j+dispAux];
      for(j=0; j<=aux->qtd;j++)
         aux->filho[j] = aux->filho[j+dispAux];
      *diminui = 0;
    }else{
      for(j=1;j<= m; j++)
        inserePagina(pag, aux->vecAluno[j-1], &aux->filho[j]);
      free(aux);
      for(j=posPai;j<=(*pagPai)->qtd;j++){
          (*pagPai)->vecAluno[j-1] = (*pagPai)->vecAluno[j];
          (*pagPai)->filho[j] = (*pagPai)->filho[j+1];
      }
      (*pagPai)->qtd--;
      if((*pagPai)->qtd >= m) *diminui = 0;
    }
  }
}
