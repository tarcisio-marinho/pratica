#include<stdio.h>
#include<stdlib.h>
#include "alunos.h"
#include "arvore.h"
#include "types.h"
#include "valida.h"
#include "disciplinas.h"

//#include "matricula.h"

void alunoss(FILE *arq, NOaluno **alunos, int *pos);
void disciplinass(FILE *arq, NOdisciplina * *disciplinas, int *pos);
//void matriculas(FILE *al, NOaluno * *alunos, FILE *dis, NOdisciplina * &disciplinas);

int main(){
  int op;
  int posicoes, posicoes2;
  NOaluno *alunos = NULL;
  NOdisciplina *disciplinas = NULL;
  FILE *al, *dis;

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


  while(1){
    system("clear");
    printf("1) Alunos \n");
    printf("2) Disciplinas \n");
    printf("3) Matrícula \n4) sair\nEscolha: ");
    scanf("%d", &op);fflush(stdin);getchar();

    if(op == 1){
      alunoss(al, &alunos, &posicoes);
    }else if(op == 2){
      disciplinass(dis, &disciplinas, &posicoes2);
    }else if(op == 3){
      //matriculas(al, &alunos, dis, &disciplina);
    }else if(op == 4){
      manutencao_aluno(al);
      manutencao_disciplina(dis);
      //remove_tudo_aluno(&alunos);
      //remove_tudo_disciplina(&disciplinas);
      return 0;
    }else{
        printf("\nOpção inválida\n");
    }
  }

  return 0;
}


void alunoss(FILE *arq, NOaluno **alunos, int *pos){
  int op;
  char matricula[11];
  system("clear");
  while (1){
    printf("1) cadastrar aluno\n");
    printf("2) alterar aluno\n");
    printf("3) exibir aluno\n");
    printf("4) remover aluno \n5) voltar\nEscolha: ");
    scanf("%d", &op);fflush(stdin);getchar();

    if(op == 1){
      cadastrar_aluno(arq, alunos, pos);
    }

    else if(op == 2){
      printf("Insira a matricula do aluno: ");
      fgets(matricula, 10, stdin);
      alterar_aluno(matricula, arq, *alunos);
    }

    else if(op == 3){
      printf("Insira a matricula do aluno: ");
      fgets(matricula, 10, stdin);
      exibir_aluno(matricula, arq, *alunos);
    }

    else if(op == 4){
      printf("Insira a matricula do aluno: ");
      fgets(matricula, 10, stdin);
      remover_aluno(matricula, arq, alunos);
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
  system("clear");
  while (1){
    printf("1) cadastrar disciplina\n");
    printf("2) alterar disciplina\n");
    printf("3) exibir disciplina\n");
    printf("4) remover disciplina \n5) retornar\nEscolha: ");
    scanf("%d", &op);getchar();

    if(op == 1){
      cadastrar_disciplina(arq, disciplinas, pos);
    }

    else if(op == 2){
      printf("Insira o codigo da disciplina: ");
      fgets(codigo, 7, stdin);
      alterar_disciplina(codigo, arq, *disciplinas);
    }

    else if(op == 3){
      printf("Insira o codigo da disciplina: ");
      fgets(codigo, 7, stdin);
      exibir_disciplina(codigo, arq, *disciplinas);
    }

    else if(op == 4){
      printf("Insira o codigo da disciplina: ");
      fgets(codigo, 7, stdin);
      remover_disciplina(codigo, arq, disciplinas);
    }

    else if(op == 5){
      return;
    }

    else{
      printf("Opção inválida\n");
    }
  }
}

/*
void matriculas(FILE *al, NOaluno * &alunos, FILE *dis, NOdisciplina * &disciplinas){
  int op;
  char codigo[7], matricula[10];
  system("clear");
  while (1){
    printf("1) matricular aluno\n");
    printf("2) exclui matricula do aluno\n");
    printf("3) exibir disciplina que aluno está matriculado\n");
    printf("4) exibir alunos matriculados numa disciplina \nEscolha: ");
    scanf("%d", &op);

    if(op == 1){
      printf("\nInsira a matricula do aluno: ");
      fgets(matricula, 10, stdin);
      printf("\nInsira o codigo da disciplina: ");
      fgets(codigo, 7, stdin);
      matricula_aluno(codigo, matricula);
    }
    else if(op == 2){
      printf("\nInsira a matricula do aluno: ");
      fgets(matricula, 10, stdin);
      printf("\nInsira o codigo da disciplina: ");
      fgets(codigo, 7, stdin);
      exclui_matricula(codigo, matricula);
    }
    else if(op == 3){
      printf("\nInsira a matricula do aluno: ");
      fgets(matricula, 10, stdin);
      exibir_disciplinas_aluno_matriculado(matricula);
    }
    else if(op == 4){
      printf("\nInsira o codigo da disciplina: ");
      fgets(codigo, 10, stdin);
      exibi_dados_alunos_matriculados_disciplina(codigo);
    }
    else{
      printf("\nOpção inválida\n");
    }
  }

}
*/
