

#include <stdio.h>
#include <string.h>
#include "types.h"
#include "arvore.h"
#include "alunos.h"
#include "valida.h"
#include "disciplinas.h"

void cadastrar_disciplina(FILE *arq, NOdisciplina **raiz, int *pos){
  Disciplina disciplina;
  char codigo[11], nome[41], horario, sala[5];
  int status, qtd_vagas;
  system("clear");

  printf("\nInsira o codigo: ");
  fgets(codigo, 10, stdin);
  while (valida_codigo(&codigo) != 0){
    printf("\n[-] codigo inválido, insira novamente: ");
    fgets(codigo, 10, stdin);
  }

  while (verifica_codigo(codigo, *raiz) != 0){
    printf("\n[-] codigo já registrado, insira outra: ");
    fgets(codigo, 10, stdin);
  }

  printf("\nNome da disciplina: ");
  fgets(nome, 40, stdin);
  while(valida_nome(nome) != 0){
    printf("\nNome invalido, insira novamente: ");
    fgets(nome, 40, stdin);
  }

  printf("\nhorario da disciplina: ");
  scanf("%c", &horario);fflush(stdin);getchar();
  while(valida_horario(horario) != 0){
    printf("\nhorario inválido, insira novamente: ");
    scanf("%c", &horario);fflush(stdin);getchar();
  }

  printf("\nsala da disciplina: ");
  fgets(sala, 4, stdin);
  while(valida_sala(sala) != 0){
    printf("\nsala inválido, insira novamente: ");
    fgets(sala, 4, stdin);
  }

  printf("\nQuantidade de vagas: ");
  scanf("%d", &qtd_vagas);fflush(stdin);getchar();
  while(valida_qtd_total_vagas(qtd_vagas) != 0){
    printf("\nQuantidade de vagas inválida, insira novamente: ");
    scanf("%d", &qtd_vagas);fflush(stdin);getchar();
  }

  // terminou as validações, copia para a struct e salva em arquivo
  strcpy(disciplina.codigo, codigo);
  strcpy(disciplina.nome, nome);
  disciplina.horario = horario;
  strcpy(disciplina.sala, sala);
  disciplina.qtd_total_vagas = qtd_vagas;
  disciplina.qtd_vagas_ocupadas = 0;
  disciplina.status = 1;

  fseek(arq, 0, 2);
  status = fwrite(&disciplina, sizeof(Disciplina), 1, arq);
  *pos+=1;
  inserir_arvore_disciplina(raiz, codigo, *pos);

  if(status != 1)  printf("\n[-] Erro ao cadastrar disciplina\n");
  else  printf("\n[+] Cadastrado\n");
}



void alterar_disciplina(char codigo[], FILE *arq, NOdisciplina *raiz){
  int pos, status, qtd_total_vagas;
  char sala[5], nome[40];
  Disciplina dis;
  system("clear");

  pos = busca_arvore_disciplina(raiz, codigo);
  if(pos != -1){
    fseek(arq, pos*sizeof(Disciplina), 0);
    status = fread(&dis, sizeof(Disciplina), 1, arq);

    printf("\nnovo Nome: ");
    fgets(nome, 40, stdin);
    while(valida_nome(nome) != 0){
      printf("\nNome invalido, digite outro nome: ");
      fgets(nome, 40, stdin);
    }

    printf("\nnova Sala: ");
    fgets(sala, 4, stdin);
    while(valida_sala(sala) != 0){
      printf("\nSala invalida, digite outra sala: ");
      fgets(nome, 40, stdin);
    }

    printf("\nnova quantidade total de vagas: ");
    scanf("%d", &qtd_total_vagas);fflush(stdin);getchar();
    while(valida_qtd_total_vagas(qtd_total_vagas) != 0){
      printf("\n[-] Inválido, nova quantidade total de vagas: ");
      scanf("%d", &qtd_total_vagas);fflush(stdin);getchar();
    }

    strcpy(dis.nome, nome);
    strcpy(dis.sala, sala);
    dis.qtd_total_vagas = qtd_total_vagas;

    fseek(arq, -sizeof(Disciplina), 1);
    status = fwrite(&dis, sizeof(Disciplina), 1, arq);
    if(status != 1)  printf("[-] Erro ao alterar\n");
    else  printf("[+] Alterado\n");

  }else  printf("[-] Disciplina inexistente\n");
}




void exibir_disciplina(char codigo[], FILE *arq, NOdisciplina *raiz){
  int pos, status;
  Disciplina dis;
  system("clear");

  pos = busca_arvore_disciplina(raiz, codigo);
  if(pos != -1){
    fseek(arq, pos*sizeof(Disciplina), 0);
    status = fread(&dis, sizeof(Disciplina), 1, arq);
    if(status != 1)  printf("Erro ao ler");
    else{
      printf("\nNome: %s\n", dis.nome);
      printf("horario: %c\n", dis.horario);
      printf("sala: %s\n", dis.sala);
      printf("quantidade de vagas disponiveis: %d\n", dis.qtd_total_vagas - dis.qtd_vagas_ocupadas);
    }
  }else  printf("[-] Disciplina não cadastrada\n");
}






void remover_disciplina(char codigo[], FILE *arq, NOdisciplina **raiz){ // só remover se não tiver alunos matriculados
  int pos, status;
  Disciplina dis;
  pos = busca_arvore_disciplina(*raiz, codigo);
  if(pos != -1){
    fseek(arq, pos*sizeof(Disciplina), 0);
    status = fread(&dis, sizeof(Disciplina), 1, arq);
    dis.status = 0;
    fseek(arq, -sizeof(Disciplina), 1);
    status = fwrite(&dis, sizeof(Disciplina), 1, arq);
    remover_arvore_disciplina(raiz, codigo);
    printf("Removido\n");
  }else  printf("[-] Disciplina não cadastrado");
}




int verifica_codigo(char codigo[], NOdisciplina *raiz){
  int retorno;
  retorno = busca_arvore_disciplina(raiz, codigo);
  if(retorno == -1)  return 0;
  else  return 1;
}




void manutencao_disciplina(FILE *arq){
  Disciplina dis;
  int status;
  FILE *arq2;
  arq2 = fopen("disciplinas2.dat", "w+b");
  fseek(arq, 0, 0);
  while(1){
    status = fread(&dis, sizeof(Disciplina), 1, arq);
    if(status != 1){

      if(!feof(arq))  break;
      else  break;

    }else{
      if(dis.status == 1)  status = fwrite (&dis, sizeof (Disciplina), 1, arq2);;
    }
  }
  fclose(arq);
  fclose(arq2);
  remove("disciplinas.dat");
  rename("disciplinas2.dat", "disciplinas.dat");
}
