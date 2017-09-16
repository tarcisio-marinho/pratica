#include<stdio.h>
#include "types.h"

void matricula_aluno(FILE *disciplinas, char codigo[], NOdisciplina *disci, FILE *alunos, char matricula[], NOaluno *alun, FILE *matriculas);
void getData(char data[]);
void exclui_matricula(FILE *disciplinas, char codigo[], NOdisciplina *disci, FILE *alunos, char matricula[], NOaluno *alun, FILE *matriculas);
void manutencao_matricula(FILE *matriculas);
