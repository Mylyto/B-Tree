#include "arvoreB.h"
#include <stdio.h>
#include <stdlib.h>

void inicializaB(TPagina ** p){
  *p = NULL;
}
void buscaB(TPagina * pag, int mat){
  int i;
  if(pag==NULL){
    printf("Matricula não cadastrada...");
  }else{
    i = 0;
    while (i < pag->qtd && mat > pag->vecAluno[i].matricula )
      i++;
    if(mat == pag->vecAluno[i].matricula){
      printf("Matricula encontrada\n");
    }else{
      if(mat<pag->vecAluno[i].matricula)
        buscaB(pag->filho[i], mat);
      else
        buscaB(pag->filho[i+1], mat);
    }
  }
}

void alturaB(TPagina * pag, int * altura){
  if(pag==NULL){
    return;
  }else{
    altura++;
    alturaB(pag->filho[0], altura);
  }
}

void insereB(TPagina * pag, TAluno a) {
  int pos = 0, i;
  TAluno meio;
  TPagina * novosFilhos[2*m+1];
  while (i < pag->qtd && a.matricula > pag->vecAluno[i].matricula ) //INSERSÇAO SIMPLES
    i++;
    if(a.matricula == pag->vecAluno[i].matricula){
        printf("Matricula já inserida\n");
    }else{
        pag->vecAluno[pag->qtd++] = a;
          //ORDENAR
    }
  //insereB2(pag, a, &meio, pos, novosFilhos);
}

/*
void insereB2(TPagina * pag, TAluno a, TAluno * meio, int pos, TPagina ** novosFilhos){//Chega ao final da estrutura
  int i = 0, j;
  TAluno vecMeio[2*m+1], vecDir[2*m], vecEsq[2*m];
  TPagina vecPag[2*m+1];
  if(pag==NULL){ //Primeira Inserção
    pag->qtd = 1;
    pag->vecAluno[0] = a;
    for(i=0;i<(2*m+1);i++)
      pag->filho[i] = NULL;
    return;
  }else{
    if(pag->qtd < (2*m+1)){ //A QUANTIDADE DE REGISTROS É MENOR QUE O MÁXIMO PERMITIDO
      if(pag->filho[i] == NULL){ //A PÁGINA NÃO POSSUÍ FILHOS
        while (i < pag->qtd && a.matricula > pag->vecAluno[i].matricula )
          i++;
        if(a.matricula == pag->vecAluno[i].matricula){
          printf("Matricula já inserida\n");
        }else{
          pag->vecAluno[++pag->qtd] = a;
          //ORDENAR
        }
        return;
      }else{ // A PÁGINA TEM FILHOS, apenas percorrer até uma página folha.
        while (i < pag->qtd && a.matricula > pag->vecAluno[i].matricula)
          i++;
        if(a.matricula == pag->vecAluno[i].matricula){
          printf("Matricula já inserida\n");
        }else{
          if(a.matricula < pag->vecAluno[i].matricula)
            insereB2(pag->filho[i], a, meio, i, novosFilhos);
          else
            insereB2(pag->filho[i+1], a, meio, (i+1), novosFilhos);
        }
      }
    }else{ //A PÁGINA ESTÁ CHEIA
      i=0;
      if(pag->filho[i] == NULL){ // E NÃO TEM FILHOS
        for(i=0;i<2*m;i++)
          vecMeio[i] = pag->vecAluno[i];
        vecMeio[i] = a;
        //ORDENAR vecMeio;
        *meio = vecMeio[m+1];
        for(i=0;i<m;i++){
          vecEsq[i] = vecMeio[i];
        }
        j= i + 1;
        for(i=0;i<m;i++){
          vecDir[i] = vecMeio[j];
          j++;
        }
        for(i=0; i<(2*m); i++){
          if(i < pos)
            vecPag[i] = *pag->filho[i];
          else if(i == pos)
            for(j=0;j<m;j++)
              vecPag[i].vecAluno[j] = vecEsq[j];
          else if(i == (pos+1))
            for(j=0;j<m;j++)
              vecPag[i].vecAluno[j] = vecDir[j];
          else
            vecPag[i] = *pag->filho[i-1];
        }
        *novosFilhos = vecPag;
        return;
      }else{// A PAGINA ESTÁ CHEIA E TEM FILHOS, apenas percorrer até encontrar uma pagina folha.
        i=0;
        while (i < pag->qtd && a.matricula > pag->vecAluno[i].matricula)
          i++;
        if(a.matricula == pag->vecAluno[i].matricula){
          printf("Matricula já inserida\n");
        }else{
          if(a.matricula < pag->vecAluno[i].matricula)
            insereB2(pag->filho[i], a, meio, i, novosFilhos);
          else
            insereB2(pag->filho[i+1], a, meio, (i+1), novosFilhos);
        }
      }
    }
  }
  *pag->filho = *novosFilhos;
  if(pag->qtd < (2*m+1)){
    pag->vecAluno[++pag->qtd] = a;
  }else{
    for(i=0;i<2*m;i++)
      vecMeio[i] = pag->vecAluno[i];
    vecMeio[i] = a;
    //ORDENAR vecMeio;
    *meio = vecMeio[m+1];
    for(i=0;i<m;i++){
      vecEsq[i] = vecMeio[i];
    }
    j= i + 1;
    for(i=0;i<m;i++){
      vecDir[i] = vecMeio[j];
      j++;
    }
    for(i=0; i<(2*m); i++){
      if(i < pos)
        vecPag[i] = *pag->filho[i];
      else if(i == pos)
        for(j=0;j<m;j++)
          vecPag[i].vecAluno[j] = vecEsq[j];
      else if(i == (pos+1))
        for(j=0;j<m;j++)
          vecPag[i].vecAluno[j] = vecDir[j];
      else
        vecPag[i] = *pag->filho[i-1];
    }
    *novosFilhos = vecPag;
  }
}
*/

