#include<stdio.h>
#include "matricula.h"
#include <string.h>

void matricula(FILE *disciplinas, char codigo[], FILE *alunos, char matricula[], FILE *matriculas){
  Disciplina dis;
  Aluno al;
  Matricula mat;
  char horario;
  int status, continua = 0;

  fseek(disciplinas, 0, 0);
  while(1){
    status = fread(&dis, sizeof(Disciplina), 1, disciplinas);
    if(status != 1){
      if(!feof(disciplinas)){
        printf("Erro de leitura\n");
        return;
      }else{
        printf("Disciplina não esta no arquivo\n");
        return;
      }
    }else{
      if(dis.status == 1 && strcmp(dis.codigo, codigo) == 0){
        if((dis.qtd_total_vagas - dis.qtd_vagas_ocupadas) > 0){
          continua = 1;
          horario = dis.horario;
          break;
        }else{
          printf("Disciplina está cheia\n");
        }
      }
    }
  }

  if(continua == 1){
    fseek(matriculas, 0, 0);
    while(1){
      status = fread(&mat, sizeof(Matricula), 1, matriculas);
      if(status != 1){
        if(!feof(matriculas)){
          printf("Erro de leitura\n");
          return;
        }else{
          printf("Aluno não matriculado em nenhuma disciplina\n");
          return;
        }
      }else{
        if(mat.status == 1 && strcmp(mat.matricula, matricula) == 0){ // achou o aluno no arquivo matricula
          if(strcmp(codigo, mat.codigo) == 0){
            printf("Aluno já matriculado nesta disciplina\n");
            return;
          }else  continua = 1;
        }

      }
    }
  }
  if(continua == 1){
    fseek(matriculas, 0, 0);
    while(1){
      status = fread(&mat, sizeof(Matricula), 1, matriculas);
      if(status != 1){
        if(!feof(matriculas)){
          printf("Erro de leitura\n");
          return;
        }else{
          printf("Aluno não matriculado em nenhuma disciplina\n");
          return;
        }
      }else{
        if(mat.status == 1 && strcmp(mat.matricula, matricula) == 0){ // achou o aluno no arquivo matricula


        }
      }
    }
  }
}


