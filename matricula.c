#include<stdio.h>
#include "matricula.h"
#include <string.h>
#include "alunos.h"
#include "disciplinas.h"

// EXISTEM VAGAS NA DISCIPLINA     ***
// SE O ALUNO NÃO JA ESTÁ MATRICULADO NESTA DISCIPLINA ***
// SE O ALUNO NÃO ESTA MATRICULADO EM OUTRA DISCIPLINA NO MESMO HORARIO ***
// SE O ALUNO NÃO ATINGIU O LIMITE DE DISCIPLINAS ***

// MEDIA < 5 -> 3 DISCIPLINAS
// MEDIA == 5 E < 7 -> 5 DISCIPLINAS
// MEDIA >=7 -> 6 DISCIPLINAS

// ATUALIZAR O REGISTRO DA DISCIPLINA -> VAGAS--;

void matricula_aluno(FILE *disciplinas, char codigo[], NOdisciplina *disci, FILE *alunos, char matricula[], NOaluno *alun, FILE *matriculas){
  Disciplina dis;
  Aluno al;
  Matricula mat;
  char horario;
  int status, pos;



  // EXISTEM VAGAS LIVRES NA DISCIPLINA
  pos = busca_arvore_disciplina(disci, codigo);
  if(pos != -1){
    fseek(disciplinas, pos*sizeof(Disciplina), 0);
    status = fread(&dis, sizeof(Disciplina), 1, disciplinas);

    if((dis.qtd_total_vagas - dis.qtd_vagas_ocupadas) <= 0){
      printf("[-] Disciplina cheia! vagas livres: %d\n", dis.qtd_total_vagas - dis.qtd_vagas_ocupadas);
      return;
    }

    horario = dis.horario;

  }else{
    printf("[-] Disciplina inexistente\n");
    return;
  }



  // ALUNO JA ESTA MATRICULADO + MATRICULADO EM OUTRA NO MESMO HORARIO
  fseek(matriculas, 0, 0);
  while(1){
    status = fread(&mat, sizeof(Matricula), 1, matriculas);
    if(status !=1){
      if(!feof(matriculas))  break;
      else  break;
    }
    else{
      if(mat.status == 1 && strcmp(mat.matricula, matricula) == 0){
        if(strcmp(mat.codigo, codigo) == 0){
          printf("Aluno já matriculado nesta disciplina\n");
          return;
        }

        pos = busca_arvore_disciplina(disci, mat.codigo);
        if(pos != -1){
          fseek(disciplinas, pos*sizeof(Disciplina), 0);
          status = fread(&dis, sizeof(Disciplina), 1, disciplinas);
          if(horario == dis.horario){
            printf("Aluno já matriculado em outra disciplina no mesmo horario\n");
            return;
          }
        }
      }
    }
  }


  // ALUNO ATINGIU SEU LIMITE DE DISCIPLINAS
  pos = busca_arvore_disciplina(alun, matricula);
  if(pos != -1){
    fseek(alunos, pos*sizeof(Aluno), 0);
    status = fread(&al, sizeof(Aluno), 1, alunos);

    if(al.qtd_disciplinas_matriculado>6){
      printf("O aluno já se matriculou em 6 disciplinas");
      return;
    }
  }

  // FEITA TODAS AS VERIFICAÇÕES, MATRICULA O ALUNO NA DISCIPLINA
  printf("Aluno está pronto para ser matriculado\n");

  strcpy(mat.matricula, matricula);
  strcpy(mat.codigo, codigo);
  strcpy(mat.data ,"asdadsasd"); // ARRUMAR A DATA DA MATRICULA
  mat.status = 1;

  fseek(matriculas, 0, 2);
  status = fwrite(&mat, sizeof(Aluno), 1, matriculas);
  if(status != 1)  printf("\n[-] Erro ao matricular aluno\n");
  else  printf("\n[+] Matriculado\n");


  pos = busca_arvore_disciplina(disci, codigo);
  fseek(disciplinas, pos*sizeof(Disciplina), 0);
  status = fread(&dis, sizeof(Disciplina), 1, disciplinas);
  dis.qtd_vagas_ocupadas++;

  fseek(disciplinas, -sizeof(Disciplina), 1);
  status = fwrite(&dis, sizeof(Disciplina), 1, disciplinas);

  if(status != 1)  printf("\n[-] Erro ao alterar a qtd de matriculados na disciplina\n");
  else  printf("\n[+] alterada a qtd de alunos na disciplina\n");



}


