#include<stdio.h>
#include<stdlib.h>
#include "alunos.h"
#include "arvore.h"
#include "types.h"
#include "valida.h"
#include "disciplinas.h"
#include "matricula.h"

void alunoss(FILE *arq, NOaluno **alunos, int *pos);
void disciplinass(FILE *arq, NOdisciplina * *disciplinas, int *pos);
void matriculas(FILE *dis, NOdisciplina *disci, FILE *al, NOaluno *alun, FILE *mat);
void espera();
int main(){
  int op;
  int posicoes, posicoes2;
  NOaluno *alunos = NULL;
  NOdisciplina *disciplinas = NULL;
  FILE *al, *dis, *mat;

  al = fopen("alunos.dat","r+b");
  if(al == NULL){
    al = fopen("alunos.dat", "w+b");
    posicoes = -1;
  }else{
    posicoes = montar_arvore_aluno(&alunos, al);
  }

  dis = fopen("disciplinas.dat","r+b");
  if(dis == NULL){
    dis = fopen("disciplinas.dat", "w+b");
    posicoes2 = -1;
  }else{
    posicoes2 = montar_arvore_disciplina(&disciplinas, dis);
  }

  mat = fopen("matriculas.dat", "r+b");
  if(mat == NULL){
    mat = fopen("matriculas.dat", "w+b");
  }


  while(1){
    system("clear");
    printf("==== Menu ====\n");
    printf("Total alunos: %d\n", posicoes + 1);
    printf("Total disciplinas: %d\n", posicoes2 + 1);
    printf("1) Alunos \n");
    printf("2) Disciplinas \n");
    printf("3) Matrícula \n4) sair\nEscolha: ");
    scanf("%d", &op);fflush(stdin);getchar();

    if(op == 1){
      alunoss(al, &alunos, &posicoes);
    }else if(op == 2){
      disciplinass(dis, &disciplinas, &posicoes2);
    }else if(op == 3){
      matriculas(dis, disciplinas, al, alunos, mat);
    }else if(op == 4){
      manutencao_aluno(al);
      manutencao_disciplina(dis);
      manutencao_matricula(mat);
      remove_tudo_aluno(&alunos);
      remove_tudo_disciplina(&disciplinas);
      return 0;
    }else{
        printf("\nOpção inválida\n");
    }
    espera();
  }

  return 0;
}

void espera(){
  printf("\n[*] Digite qualquer tecla para voltar\n");
  getchar();
}

void alunoss(FILE *arq, NOaluno **alunos, int *pos){
  int op;
  char matricula[11];
  while (1){
    system("clear");
    printf("==== Alunos ====\n");
    printf("1) cadastrar aluno\n");
    printf("2) alterar aluno\n");
    printf("3) exibir aluno\n");
    printf("4) remover aluno \n5) voltar\nEscolha: ");
    scanf("%d", &op);fflush(stdin);getchar();

    if(op == 1){
      cadastrar_aluno(arq, alunos, pos);
      espera();
    }

    else if(op == 2){
      printf("Insira a matricula do aluno: ");
      fgets(matricula, 10, stdin);
      alterar_aluno(matricula, arq, *alunos);
      espera();
    }

    else if(op == 3){
      printf("Insira a matricula do aluno: ");
      fgets(matricula, 10, stdin);
      exibir_aluno(matricula, arq, *alunos);
      espera();
    }

    else if(op == 4){
      printf("Insira a matricula do aluno: ");
      fgets(matricula, 10, stdin);
      remover_aluno(matricula, arq, alunos);
      espera();
    }

    else if(op == 5){
      return;
    }

    else{
      printf("Opção inválida\n");
    }

  }
}

void disciplinass(FILE *arq, NOdisciplina * *disciplinas, int *pos){
  int op;
  char codigo[8];
  while (1){
    system("clear");
    printf("==== Disciplinas ====\n");
    printf("1) cadastrar disciplina\n");
    printf("2) alterar disciplina\n");
    printf("3) exibir disciplina\n");
    printf("4) remover disciplina \n5) retornar\nEscolha: ");
    scanf("%d", &op);getchar();

    if(op == 1){
      cadastrar_disciplina(arq, disciplinas, pos);
      espera();
    }

    else if(op == 2){
      printf("Insira o codigo da disciplina: ");
      fgets(codigo, 7, stdin);
      alterar_disciplina(codigo, arq, *disciplinas);
      espera();
    }

    else if(op == 3){
      printf("Insira o codigo da disciplina: ");
      fgets(codigo, 7, stdin);
      exibir_disciplina(codigo, arq, *disciplinas);
      espera();
    }

    else if(op == 4){
      printf("Insira o codigo da disciplina: ");
      fgets(codigo, 7, stdin);
      remover_disciplina(codigo, arq, disciplinas);
      espera();
    }
    else if(op == 5){
      return;
    }
    else{
      printf("Opção inválida\n");
    }
  }
}


void matriculas(FILE *dis, NOdisciplina *disci, FILE *al, NOaluno *alun, FILE *mat){
  int op;
  char codigo[7], matricula[10];
  while (1){
    system("clear");
    printf("==== Matriculas ====\n");
    printf("1) matricular aluno\n");
    printf("2) exclui matricula do aluno\n");
    printf("3) exibir disciplina que aluno está matriculado\n");
    printf("4) exibir alunos matriculados numa disciplina\n");
    printf("5) retornar\nEscolha: ");
    scanf("%d", &op);getchar();fflush(stdin);

    if(op == 1){
      printf("\nInsira a matricula do aluno: ");
      fgets(matricula, 10, stdin);
      printf("\nInsira o codigo da disciplina: ");
      fgets(codigo, 7, stdin);
      matricula_aluno(dis, codigo, disci, al, matricula, alun, mat);
      espera();
    }
    else if(op == 2){
      printf("\nInsira a matricula do aluno: ");
      fgets(matricula, 10, stdin);
      printf("\nInsira o codigo da disciplina: ");
      fgets(codigo, 7, stdin);
      exclui_matricula(dis, codigo, disci, al, matricula, alun, mat);
      espera();
    }
    else if(op == 3){
      printf("\nInsira a matricula do aluno: ");
      fgets(matricula, 10, stdin);
      exibi_disciplinas(dis, codigo, disci, al, matricula, alun, mat);
      espera();
    }
    else if(op == 4){
      printf("\nInsira o codigo da disciplina: ");
      fgets(codigo, 10, stdin);
      exibi_matricula_aluno(dis, codigo, disci, al, matricula, alun, mat);
      espera();
    }else if(op == 5){
      return;
    }
    else{
      printf("\nOpção inválida\n");
    }
  }

}
