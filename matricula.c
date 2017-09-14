#include<stdio.h>
#include "matricula.h"
#include <string.h>
#include "alunos.h"
#include "disciplinas.h"

// EXISTEM VAGAS NA DISCIPLINA     *****
// SE O ALUNO NÃO JA ESTÁ MATRICULADO NESTA DISCIPLINA
// SE O ALUNO NÃO ESTA MATRICULADO EM OUTRA DISCIPLINA NO MESMO HORARIO
// SE O ALUNO NÃO ATINGIU O LIMITE DE DISCIPLINAS

// MEDIA < 5 -> 3 DISCIPLINAS
// MEDIA == 5 E < 7 -> 5 DISCIPLINAS
// MEDIA >=7 -> 6 DISCIPLINAS

// ATUALIZAR O REGISTRO DA DISCIPLINA -> VAGAS--;

void matricula(FILE *disciplinas, char codigo[], NOdisciplina *disci, FILE *alunos, char matricula[], NOaluno *alun, FILE *matriculas){
  Disciplina dis;
  Aluno al;
  Matricula mat;
  char horario;
  int status, continua = 0, pos;

  pos = busca_arvore_disciplina(disci, codigo);
  if(pos != -1){
    fseek(disciplinas, pos*sizeof(Disciplina), 0);
    status = fread(&dis, sizeof(Disciplina), 1, disciplinas);

    if((dis.qtd_total_vagas - dis.qtd_vagas_ocupadas) <= 0){
      printf("[-] Disciplina cheia! vagas livres: %d", dis.qtd_total_vagas - dis.qtd_vagas_ocupadas);
      return;
    }

  }else{
    printf("[-] Disciplina inexistente\n");
    return;
  }

  pos = busca_arvore_aluno(alun, matricula);
  if(pos != -1){

    fseek(alunos, pos*sizeof(Aluno), 0);
    status = fread(&al, sizeof(Aluno), 1, alunos);

  }else{
    printf("[-] Aluno inexistente\n");
    return;
  }






}


