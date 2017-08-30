
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "types.h"


///// operacoes dos alunos

void remove_tudo_aluno(NOaluno ** raiz){
  if (raiz != NULL){
    remove_tudo_aluno(&(*raiz)->esq);
    remove_tudo_aluno(&(*raiz)->dir);
    remover_arvore_aluno(*raiz);
  }
}

int remover_arvore_aluno(NOaluno **raiz, char matricula[]){
  if (*raiz == NULL)  return -1; // não achou
  else if (strcmp(matricula, (*raiz)->matricula) == 0)  remover_no_aluno(&(*raiz));
  else{
    if (strcmp(matricula, (*raiz)->matricula) < 0)  remover_arvore_aluno(&((*raiz)->esq),matricula);
    else  remover_arvore_aluno(&((*raiz)->dir),matricula);
  }
}

NOaluno * maior_aluno(NOaluno ** raiz){
  NOaluno * aux;
  aux = *raiz;
  if (aux->dir == NULL){
    *raiz = (*raiz)->esq;
    return (aux);
  }
  else  return maior_aluno(&((*raiz)->dir));
}

void remover_no_aluno(NOaluno **raiz){
  NOaluno * pos;
  pos = *raiz;
  if ((*raiz)->esq == NULL && (*raiz)->dir == NULL) // Não tem filhos
    *raiz = NULL;
  else if ((*raiz)->esq == NULL) // Não tem filho a esquerda
    *raiz = (*raiz)->dir;
  else if ((*raiz)->dir == NULL) // Não tem filho a direita
    *raiz = (*raiz)->esq;
  else{
    pos = maior_aluno(&((*raiz)->esq));
    strcpy((*raiz)->matricula, pos->matricula);
  }
  free (pos);
}




void inserir_arvore_aluno(NOaluno **raiz, char matricula[], int pos){
  if(*raiz == NULL){
    *raiz = (NOaluno*)malloc(sizeof(NOaluno));
    strcpy((*raiz)->matricula, matricula);
    (*raiz)->pos = 0; // posicao do arquivo
    (*raiz)->dir = NULL;
    (*raiz)->esq = NULL;
  }else{
    if(strcmp((*raiz)->matricula, matricula)<0)  inserir_arvore_aluno(&((*raiz)->dir), matricula, pos);
    else  inserir_arvore_aluno(&((*raiz)->esq), matricula, pos);
  }
}



int busca_arvore_aluno(NOaluno *raiz, char matricula[]){ // retorna a posicao
  if(raiz == NULL)  return -1; // não achou
  else{
    if(strcmp(raiz->matricula, matricula) == 0)  return raiz->pos; // achou a posicao do aluno
    else if(strcmp(raiz->matricula, matricula) > 0) return busca_arvore_aluno(raiz->esq, matricula);
    else if(strcmp(raiz->matricula, matricula) < 0) return busca_arvore_aluno(raiz->dir, matricula);
  }
}


int montar_arvore_aluno(NOaluno **raiz, FILE *alunos){
  int status, contador = -1;
  Aluno *al;
  fseek(alunos, 0, 0);
  while(1){
    status = fread(&al, sizeof(Aluno), 1, alunos);
    if(status != 1){
      if(!feof(alunos)){
          break;
      }else{
          break;
      }
    }else{
      contador++;
      inserir_arvore_aluno(*raiz, al->matricula, contador);
    }
  }
  return contador;
}

/////// operacoes das disciplinas


void remove_tudo_disciplina(NOdisciplina ** raiz){
  if (raiz != NULL){
    remove_tudo_disciplina(&(*raiz)->esq);
    remove_tudo_disciplina(&(*raiz)->dir);
    remover_arvore_disciplina(raiz);
  }
}

int remover_arvore_disciplina(NOdisciplina **raiz, char codigo[]){
  if (*raiz == NULL)  return -1; // não achou
  else if (strcmp((*raiz)->codigo, codigo) == 0)  remover_no_disciplina(&(*raiz));
  else{
    if (strcmp((*raiz)->codigo, codigo) > 0)  remover_arvore_disciplina(&((*raiz)->esq),codigo);
    else  remover_arvore_disciplina(&((*raiz)->dir),codigo);
  }
}

NOdisciplina * maior_disciplina(NOdisciplina **raiz){
  NOdisciplina * aux;
  aux = *raiz;
  if (aux->dir == NULL){
    *raiz = (*raiz)->esq;
    return (aux);
  }
  else  return maior_disciplina(&((*raiz)->dir));
}


void remover_no_disciplina(NOdisciplina **raiz){
  NOdisciplina * pos;
  pos = *raiz;
  if ((*raiz)->esq == NULL && (*raiz)->dir == NULL) // Não tem filhos
    *raiz = NULL;
  else if ((*raiz)->esq == NULL) // Não tem filho a esquerda
    *raiz = (*raiz)->dir;
  else if ((*raiz)->dir == NULL) // Não tem filho a direita
    *raiz = (*raiz)->esq;
  else{
    pos = maior_disciplina(&((*raiz)->esq));
    strcpy((*raiz)->codigo, pos->codigo);
  }
  free (pos);
}


void inserir_arvore_disciplina(NOdisciplina **raiz, char codigo[], int pos){
  if(*raiz == NULL){
    *raiz = (NOdisciplina*)malloc(sizeof(NOdisciplina));
    strcpy((*raiz)->codigo, codigo);
    (*raiz)->pos = 0; // posicao do arquivo
    (*raiz)->dir = NULL;
    (*raiz)->esq = NULL;
  }else{
    if(strcmp((*raiz)->codigo, codigo)<0)  inserir_arvore_disciplina(&((*raiz)->dir), codigo, pos);
    else  inserir_arvore_disciplina(&((*raiz)->esq), codigo, pos);
  }
}



int busca_arvore_disciplina(NOdisciplina *raiz, char codigo[]){ // retorna a posicao


  if(raiz == NULL)  return -1; // não achou
  else{
    if(strcmp(raiz->codigo, codigo) == 0)  return raiz->pos;
    else if(strcmp(raiz->codigo, codigo) > 0) return busca_arvore_disciplina(raiz->esq, codigo);
    else if(strcmp(raiz->codigo, codigo) < 0) return busca_arvore_disciplina(raiz->dir,codigo);
  }
}




int montar_arvore_disciplina(NOdisciplina **raiz, FILE *disciplinas){
    return 0;
}

/// comaadsoas
