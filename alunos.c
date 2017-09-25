
#include <stdio.h>
#include <string.h>
#include "types.h"
#include "arvore.h"
#include "alunos.h"
#include "valida.h"


void cadastrar_aluno(FILE *arq, NOaluno **raiz, int *pos){
  Aluno aluno;
  char matricula[11], nome[41], email[41], telefone[12];
  int status;
  system("clear");

  // recebe as informações e as valida
  printf("\nInsira matriula: ");
  fgets(matricula, 11, stdin);
  while (validar_matricula(matricula) != 0){
    printf("\nmatricula inválida, insira novamente: ");
    fgets(matricula, 11, stdin);
  }

  while (verifica_matricula(matricula, *raiz) != 0){
    printf("\nmatricula já registrada\n");
    return;
  }

  printf("\nNome: ");
  fgets(nome, 41, stdin);
  while(validar_nome_aluno_disciplina(nome) != 0){
    printf("\nNome invalido, insira novamente: ");
    fgets(nome, 41, stdin);
  }

  printf("\nemail: ");
  fgets(email, 41, stdin);
  while(validar_email(email) != 0){
    printf("\nemail inválido, insira novamente: ");
    fgets(email, 41, stdin);
  }

  printf("\ntelefone: ");
  fgets(telefone, 12, stdin);
  while(validar_telefone(telefone) != 0){
    printf("\ntelefone inválido, insira novamente: ");
    fgets(telefone, 12, stdin);
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
  *pos+=1;
  inserir_arvore_aluno(raiz, matricula, *pos);

  if(status != 1)  printf("\n[-] Erro ao cadastrar aluno\n");
  else  printf("\n[+] Cadastrado\n");
}


void alterar_aluno(char matricula[], FILE *arq, NOaluno *raiz){ // ALTERAR A MEDIA
  int pos, status;
  float media;
  char email[40], nome[40], telefone[11];
  Aluno al;
  system("clear");

  pos = busca_arvore_aluno(raiz, matricula);
  if(pos != -1){

    fseek(arq, pos*sizeof(Aluno), 0);
    status = fread(&al, sizeof(Aluno), 1, arq);

    printf("\nNome: ");
    fgets(nome, 41, stdin);
    while(validar_nome_aluno_disciplina(nome) != 0){
      printf("\nNome inválido, insira novamente: ");
      fgets(nome, 41, stdin);
    }
    printf("\nemail: ");
    fgets(email, 41, stdin);
    while(validar_email(email) != 0){
      printf("\nEmail inválido, insira novamente: ");
      fgets(email, 41, stdin);
    }
    printf("\ntelefone: ");
    fgets(telefone, 12, stdin);
    while(validar_telefone(telefone) != 0){
      printf("\nTelefone inválido, insira novamente: ");
      fgets(telefone, 12, stdin);
    }

    printf("\nDigite a nova média: ");
    scanf("%f",&media);fflush(stdin);getchar();
    while(validar_media(media)!=0){
      printf("\nDigite a nova média: ");
      scanf("%f",&media);fflush(stdin);getchar();
    }

    al.media = media;
    strcpy(al.nome, nome);
    strcpy(al.email, email);
    strcpy(al.telefone, telefone);

    fseek(arq, -sizeof(Aluno), 1);
    status = fwrite(&al, sizeof(Aluno), 1, arq);
    if(status != 1)  printf("[-] Erro ao alterar\n");
    else  printf("[+] Alterado\n");

  }else  printf("[-] Aluno inexistente\n");

}




void exibir_aluno(char matricula[], FILE *arq, NOaluno *raiz){
  int pos, status;
  Aluno al;
  system("clear");

  pos = busca_arvore_aluno(raiz, matricula);
  if(pos != -1){
    fseek(arq, pos*sizeof(Aluno), 0);
    status = fread(&al, sizeof(Aluno), 1, arq);
    if(status != 1)  printf("Erro ao ler");
    else{
      printf("\nNome: %s\n", al.nome);
      printf("Telefone: %s\n", al.telefone);
      printf("Email: %s\n", al.email);
      printf("Quantidade disciplinas matriculado: %d\n", al.qtd_disciplinas_matriculado);
      printf("Media: %.2f\n", al.media);
    }
  }else  printf("[-] Aluno não cadastrado\n");
}






void remover_aluno(char matricula[], FILE *arq, NOaluno **raiz){// não pode excluir se tiver matriculado em disciplinas
  int pos, status;
  Aluno al;

  pos = busca_arvore_aluno(*raiz, matricula);
  if(pos != -1){
    fseek(arq, pos*sizeof(Aluno), 0);
    status = fread(&al, sizeof(Aluno), 1, arq);
    if(al.qtd_disciplinas_matriculado > 0){
      printf("[-] Aluno está matriculado em alguma matéria, não é possivel excluir\n");
      return;
    }
    al.status = 0;
    fseek(arq, -sizeof(Aluno), 1);
    status = fwrite(&al, sizeof(Aluno), 1, arq);
    remover_arvore_aluno(raiz, matricula);
    printf("[+] Removido\n");
  }else  printf("[-] Aluno não cadastrado");
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
