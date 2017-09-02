
#include <stdio.h>
#include <string.h>
#include "types.h"
#include "arvore.h"
#include "alunos.h"
#include "valida.h"


void cadastrar_aluno(FILE *arq, NOaluno **raiz, int pos){
  Aluno aluno;
  char matricula[11], nome[41], email[41], telefone[12];
  int status;

  // recebe as informações e as valida
  printf("\nInsira matriula: ");
  fgets(matricula, 10, stdin);
  while (valida_matricula(matricula) != 0){
    printf("\nmatricula inválida, insira novamente: ");
    fgets(matricula, 10, stdin);getchar();
  }

  while (verifica_matricula(matricula, *raiz) != 0){
    printf("\nmatricula já registrada, insira outra: ");
    fgets(matricula, 10, stdin);getchar();
  }

  printf("\nNome: ");
  fgets(nome, 40, stdin);
  while(valida_nome(nome) != 0){
    printf("\nNome invalido, insira novamente: ");
    fgets(nome, 40, stdin);getchar();
  }

  printf("\nemail: ");
  fgets(email, 40, stdin);
  while(valida_email(email) != 0){
    printf("\nemail inválido, insira novamente: ");
    fgets(email, 40, stdin);getchar();
  }

  printf("\ntelefone: ");
  fgets(telefone, 11, stdin);
  while(valida_telefone(telefone) != 0){
    printf("\ntelefone inválido, insira novamente: ");
    fgets(telefone, 11, stdin);getchar();
  }

  // terminou as validações, copia para a struct e salva em arquivo
  strcpy(aluno.matricula, matricula);
  strcpy(aluno.nome, nome);
  strcpy(aluno.email, email);
  strcpy(aluno.telefone, telefone);
  aluno.media = 0.0;
  aluno.qtd_disciplinas_matriculado = 0;
  aluno.status = 1;

  fseek(arq, 0, 2);
  status = fwrite(&aluno, sizeof(Aluno), 1, arq);
  inserir_arvore_aluno(raiz, matricula, pos+1);

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
    while(valida_nome(nome) != 0){
      printf("\nNome inválido, insira novamente: ");
      fgets(nome, 40, stdin);
    }
    printf("\nemail: ");
    fgets(email, 40, stdin);
    while(valida_email(email) != 0){
      printf("\nEmail inválido, insira novamente: ");
      fgets(email, 40, stdin);
    }
    printf("\ntelefone: ");
    fgets(telefone, 11, stdin); // VALIDACOES
    while(valida_telefone(telefone) != 0){
      printf("\nTelefone inválido, insira novamente: ");
      fgets(telefone, 11, stdin);
    }

    strcpy(al.nome, nome);
    strcpy(al.email, email);
    strcpy(al.telefone, telefone);

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
      printf("\nNome: %s\n", al.nome);
      printf("Telefone: %s", al.telefone);
      printf("Email: %s\n", al.email);
      printf("Quantidade disciplinas matriculado: %d\n", al.qtd_disciplinas_matriculado);
      printf("Media: %f\n", al.media);
    }
  }else  printf("Aluno não cadastrado\n");
}






void remover_aluno(char matricula[], FILE *arq, NOaluno **raiz){
  int pos, status;
  Aluno al;
  pos = busca_arvore_aluno(*raiz, matricula);
  if(pos != -1){
    fseek(arq, pos*sizeof(Aluno), 0);
    status = fread(&al, sizeof(Aluno), 1, arq);
    al.status = 0;
    fseek(arq, -sizeof(Aluno), 1);
    status = fwrite(&al, sizeof(Aluno), 1, arq);
    remover_arvore_aluno(raiz, matricula);
    printf("Removido\n");
  }else  printf("Aluno não cadastrado");
}




int verifica_matricula(char matricula[], NOaluno *raiz){
  int retorno;
  retorno = busca_arvore_aluno(raiz, matricula);
  if(retorno == -1)  return 0;
  else  return 1;
}




void manutencao_aluno(FILE *arq){
  Aluno al;
  int status;
  FILE *arq2;
  arq2 = fopen("alunos2.dat", "w+b");
  fseek(arq, 0, 0);
  while(1){
    status = fread(&al, sizeof(Aluno), 1, arq);
    if(status != 1){

      if(!feof(arq))  break;
      else  break;

    }else{
      if(al.status == 1)  status = fwrite (&al, sizeof (Aluno), 1, arq2);;
    }
  }
  fclose(arq);
  fclose(arq2);
  remove("alunos.dat");
  rename("alunos2.dat", "alunos.dat");
}



