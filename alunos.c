
#include <stdio.h>
#include <string.h>
#include "types.h"
#include "arvore.h"


void cadastrar_aluno(FILE *arq, NOaluno **raiz, int pos){
  Aluno *aluno;
  char matricula[10], nome[40], email[40], telefone[11];
  int status;
  printf("\nInsira matriula: ");
  fgets(matricula, 10, stdin);
  while (valida_matricula(matricula) != 0){
    printf("\nmatricula inválida, insira outra: ");
    fgets(matricula, 10, stdin);
  }
  while (verifica_matricula(matricula) != 0){
    printf("\nmatricula já registrada, insira outra: ");
    fgets(matricula, 10, stdin);
  }
  printf("\nNome: ");
  fgets(nome, 40, stdin);
  printf("\nemail: ");
  fgets(email, 40, stdin);
  printf("\ntelefone: ");
  fgets(telefone, 11, stdin);

  strcpy(aluno->matricula, matricula);
  strcpy(aluno->nome, nome);
  strcpy(aluno->email, email);
  strcpy(aluno->telefone, telefone);
  aluno->media = 0.0;
  aluno->qtd_disciplinas_matriculado = 0;
  aluno->status = 1;

  fseek(arq, 0, 2); // insere no final do arquivo
  status = fwrite(&aluno, sizeof(Aluno), 1, arq);
  inserir_arvore_aluno(*raiz, matricula, pos+1);

  if(status != 1)  printf("\nErro ao cadastrar aluno\n");
  else  printf("\nCadastrado\n");
}

void alterar_aluno(char matricula[], FILE *arq, NOaluno *raiz){
  int pos, status;
  char email[40], nome[40], telefone[11];
  Aluno al;
  pos = busca_arvore_aluno(raiz, matricula);
  if(pos != -1){
    fseek(arq, pos*sizeof(Aluno), 0);
    printf("\nNome: ");
    fgets(nome, 40, stdin);
    printf("\nemail: ");
    fgets(email, 40, stdin);
    printf("\ntelefone: ");
    fgets(telefone, 11, stdin);
    fseek(arq, -sizeof(Aluno), 1);
    status = fwrite(&al, sizeof(Aluno), 1, arq);
    if(status != 1)  printf("Erro ao alterar\n");
    else  printf("Alterado\n");

  }else  printf("Aluno inexistente\n");
}

void exibir_aluno(char matricula[], FILE *arq, NOaluno *raiz){
  int pos, status;
  Aluno al;
  pos = busca_arvore_aluno(raiz, matricula);
  if(pos != -1){
    fseek(arq, pos*sizeof(Aluno), 0);
    status = fread(&al, sizeof(Aluno), 1, arq);
    if(status != 1)  printf("Erro ao ler");
    else{
      printf("\nNome: %s\n", al->nome);
      printf("Telefone: %s", al->telefone);
      printf("Email: %s\n", al->email);
      printf("Quantidade disciplinas matriculado: %d", al->qtd_disciplinas_matriculado);
      printf("Media: %f", al->media);
    }
  }else  printf("Aluno não cadastrado\n");
}

void remover_aluno(char matricula[], FILE *arq, NOaluno **raiz){
  int pos, status;
  Aluno al;
  pos = busca_arvore_aluno(raiz, matricula);
  if(pos != -1){
    fseek(arq, pos*sizeof(Aluno), 0);
    status = fread(&al, sizeof(Aluno), 1, arq);
    al->info = 0;
    fseek(arq, -sizeof(Aluno), 1);
    status = fwrite(&al, sizeof(Aluno), 1, arq);
    remover_arvore_aluno(*raiz, matricula);
    printf("Removido\n");
  }else  printf("Aluno não cadastrado");
}

int valida_matricula(NOaluno *raiz, char matricula[]){ // implementar quando ana falar as regras
  return 0;
}

int verifica_matricula(char matricula[], NOaluno *raiz){
  int retorno;
  retorno = busca_arvore_aluno(raiz, matricula);
  if(retorno != -1)  return 0;
  else  return 1;
}

void manutencao_aluno(FILE *arq){
  Aluno al;
  int status;
  FILE *arq2;
  arq2 = fopen("alunos2.dat", "w+b");
  while(1){
    status = fread(&al, sizeof(Aluno), 1, arq);
    if(status != 1){

      if(!feof(arq))  break;
      else  break;

    }else{
      if(al->status == 1)  status = fwrite (&al, sizeof (Aluno), 1, arq2);;
    }
  }
  fclose(arq);
  fclose(arq2);
  fremove("alunos.dat");
  frename("alunos2.dat", "alunos.dat");
}
