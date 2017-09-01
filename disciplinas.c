

#include <stdio.h>
#include <string.h>
#include "types.h"
#include "arvore.h"
#include "alunos.h"
#include "valida.h"
#include "disciplinas.h"

void cadastrar_disciplina(FILE *arq, NOdisciplina **raiz, int pos){
  Disciplina disciplina;
  char codigo[11], nome[41], email[41], telefone[12];
  int status;

  // recebe as informações e as valida
  printf("\nInsira matriula: ");
  fgets(codigo, 10, stdin);
  while (valida_codigo(codigo) != 0){
    printf("\ncodigo inválida, insira novamente: ");
    fgets(codigo, 10, stdin);getchar();
  }

  while (verifica_codigo(codigo, *raiz) != 0){
    printf("\ncodigo já registrada, insira outra: ");
    fgets(codigo, 10, stdin);getchar();
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
  strcpy(disciplina.codigo, codigo);
  strcpy(disciplina.nome, nome);
  strcpy(disciplina.email, email);
  strcpy(disciplina.telefone, telefone);
  disciplina.media = 0.0;
  disciplina.qtd_disciplinas_codigodo = 0;
  disciplina.status = 1;

  fseek(arq, 0, 2);
  status = fwrite(&disciplina, sizeof(Disciplina), 1, arq);
  inserir_arvore_disciplina(raiz, codigo, pos+1);

  if(status != 1)  printf("\nErro ao cadastrar disciplina\n");
  else  printf("\nCadastrado\n");
}



void alterar_disciplina(char codigo[], FILE *arq, NOdisciplina *raiz){
  int pos, status;
  char email[40], nome[40], telefone[11];
  Disciplina al;
  pos = busca_arvore_disciplina(raiz, codigo);
  if(pos != -1){
    fseek(arq, pos*sizeof(Disciplina), 0);
    printf("\nNome: ");
    fgets(nome, 40, stdin);
    printf("\nemail: ");
    fgets(email, 40, stdin);
    printf("\ntelefone: ");
    fgets(telefone, 11, stdin); // VALIDACOES

    strcpy(al.nome, nome);
    strcpy(al.email, email);
    strcpy(al.telefone, telefone);

    fseek(arq, -sizeof(Disciplina), 1);
    status = fwrite(&al, sizeof(Disciplina), 1, arq);
    if(status != 1)  printf("Erro ao alterar\n");
    else  printf("Alterado\n");

  }else  printf("Disciplina inexistente\n");
}




void exibir_disciplina(char codigo[], FILE *arq, NOdisciplina *raiz){
  int pos, status;
  Disciplina al;
  pos = busca_arvore_disciplina(raiz, codigo);
  if(pos != -1){
    fseek(arq, pos*sizeof(Disciplina), 0);
    status = fread(&al, sizeof(Disciplina), 1, arq);
    if(status != 1)  printf("Erro ao ler");
    else{
      printf("\nNome: %s\n", al.nome);
      printf("Telefone: %s", al.telefone);
      printf("Email: %s\n", al.email);
      printf("Quantidade disciplinas codigodo: %d", al.qtd_disciplinas_codigodo);
      printf("Media: %f", al.media);
    }
  }else  printf("Disciplina não cadastrado\n");
}






void remover_disciplina(char codigo[], FILE *arq, NOdisciplina **raiz){
  int pos, status;
  Disciplina al;
  pos = busca_arvore_disciplina(*raiz, codigo);
  if(pos != -1){
    fseek(arq, pos*sizeof(Disciplina), 0);
    status = fread(&al, sizeof(Disciplina), 1, arq);
    al.status = 0;
    fseek(arq, -sizeof(Disciplina), 1);
    status = fwrite(&al, sizeof(Disciplina), 1, arq);
    remover_arvore_disciplina(raiz, codigo);
    printf("Removido\n");
  }else  printf("Disciplina não cadastrado");
}




int verifica_codigo(char codigo[], NOdisciplina *raiz){
  int retorno;
  retorno = busca_arvore_disciplina(raiz, codigo);
  if(retorno == -1)  return 0;
  else  return 1;
}




void manutencao_disciplina(FILE *arq){
  Disciplina al;
  int status;
  FILE *arq2;
  arq2 = fopen("disciplinas2.dat", "w+b");
  fseek(arq, 0, 0);
  while(1){
    status = fread(&al, sizeof(Disciplina), 1, arq);
    if(status != 1){

      if(!feof(arq))  break;
      else  break;

    }else{
      if(al.status == 1)  status = fwrite (&al, sizeof (Disciplina), 1, arq2);;
    }
  }
  fclose(arq);
  fclose(arq2);
  remove("disciplinas.dat");
  rename("disciplinas2.dat", "disciplinas.dat");
}
