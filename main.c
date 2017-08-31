#include<stdio.h>
#include<stdlib.h>
#include "alunos.h"
#include "arvore.h"
#include "types.h"
#include "valida.h"

//#include "disciplinas.h"
//#include "matricula.h"

void alunoss(FILE *arq, NOaluno **alunos, int pos);
//void disciplinas(FILE *arq, NOdisciplina * &disciplinas);
//void matriculas(FILE *al, NOaluno * &alunos, FILE *dis, NOdisciplina * &disciplinas);

int main(){
  int op;
  int posicoes;
  NOaluno *alunos;
  NOdisciplina *disciplinas;
  FILE *al, *dis;

  al = fopen("alunos.dat","r+b");
  if(al == NULL){
    al = fopen("alunos.dat", "w+b");
    posicoes = -1;
  }else{
    posicoes = montar_arvore_aluno(&alunos, al);
  }

/*
  dis = fopen("disciplinas.dat","r+b");
  if(al == NULL){
    dis = fopen("disciplinas.dat", "w+b");
  }
*/

  while(1){
    printf("1) Alunos \n");
    printf("2) Disciplinas \n");
    printf("3) Matrícula \nEscolha: ");
    scanf("%d", &op);fflush(stdin);

    if(op == 1){
      alunoss(al, &alunos, posicoes);
    }else if(op == 2){
      //disciplinas(dis, &disciplina);
    }else if(op == 3){
      //matriculas(al, &alunos, dis, &disciplina);
    }else{
      return 0; // aq deve ficar o codigo de manutenção
    }
  }

  return 0;
}


void alunoss(FILE *arq, NOaluno **alunos, int pos){
  int op;
  char matricula[10];
  system("clear");
  while (1){
    printf("1) cadastrar aluno\n");
    printf("2) alterar aluno\n");
    printf("3) exibir aluno\n");
    printf("4) remover aluno \n5) voltar\nEscolha: ");
    scanf("%d", &op);fflush(stdin);

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
      manutencao_aluno(arq);
      return;
    }

    else{
      printf("Opção inválida\n");
    }

  }
}
/*
void disciplinas(FILE *arq, NOdisciplina * &disciplinas){
  int op;
  char codigo[7];
  system("clear");
  while (1){
    printf("1) cadastrar disciplina\n");
    printf("2) alterar disciplina\n");
    printf("3) exibir disciplina\n");
    printf("4) remover disciplina \nEscolha: ");
    scanf("%d", &op);

    if(op == 1){
      printf("Insira a matricula da disciplina para ser cadastrada: ");
      fgets(codigo, 10, stdin);
      cadastrar_disciplina(codigo);
    }
    else if(op == 2){
      printf("Insira a matricula da disciplina: ");
      fgets(codigo, 10, stdin);
      alterar_disciplina(codigo);
    }
    else if(op == 3){
      printf("Insira a codigo da disciplina: ");
      fgets(codigo, 10, stdin);
      exibir_disciplina(codigo);
    }
    else if(op == 4){
      printf("Insira a codigo da disciplina: ");
      fgets(codigo, 10, stdin);
      remover_disciplina(codigo);
    }
    else{
      printf("Opção inválida\n");
    }
  }
}

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
