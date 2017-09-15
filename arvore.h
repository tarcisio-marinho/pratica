
#include<stdio.h>
#include "types.h"


void remove_tudo_aluno(NOaluno ** raiz);
int remover_arvore_aluno(NOaluno **raiz, char matricula[]);
void remover_no_aluno(NOaluno **raiz);
NOaluno * maior_aluno(NOaluno **raiz);
void inserir_arvore_aluno(NOaluno **raiz, char matricula[], int pos);
int busca_arvore_aluno(NOaluno *raiz, char matricula[]);

int montar_arvore_aluno(NOaluno **raiz, FILE *alunos);


void remove_tudo_disciplina(NOdisciplina ** raiz);
int remover_arvore_disciplina(NOdisciplina **raiz, char codigo[]);
void remover_no_disciplina(NOdisciplina **raiz);
NOdisciplina * maior_disciplina(NOdisciplina **raiz);
void inserir_arvore_disciplina(NOdisciplina **raiz, char matricula[], int pos);
int busca_arvore_disciplina(NOdisciplina *raiz, char matricula[]);

int montar_arvore_disciplina(NOdisciplina **raiz, FILE *disciplinas);
