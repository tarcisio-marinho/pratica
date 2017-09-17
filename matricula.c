#include<stdio.h>
#include "matricula.h"
#include <string.h>
#include "alunos.h"
#include "disciplinas.h"
#include <time.h>

void getData(char data[]){
	struct tm *local;
	int dia, mes, ano;
	time_t t;

	t = time(NULL);
	local = localtime(&t);
	dia = local->tm_mday;
	mes = local->tm_mon+1;
	ano = local->tm_year+1900;

	sprintf(data, "%02d/%02d/%d", dia,mes,ano);
}

void matricula_aluno(FILE *disciplinas, char codigo[], NOdisciplina *disci, FILE *alunos, char matricula[], NOaluno *alun, FILE *matriculas){
  Disciplina dis;
  Aluno al;
  Matricula mat;
  char horario;
  int status, pos;
  char data[11];
  getData(data);


  // se o aluno não existir ?
  pos = busca_arvore_aluno(alun, matricula);
  if(pos == -1){
    printf("[-] Aluno não cadastrado\n");
    return;
  }


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

    if(al.media<5){ // 3 disciplinas
      if(al.qtd_disciplinas_matriculado>= 3){
        printf("Aluno já cadastrado em 3 disciplinas\n");
        return;
      }
    }else if(al.media>5 || al.media<7){ // 5 disciplinas
      if(al.qtd_disciplinas_matriculado>=5){
        printf("Aluno já cadastrado em 5 disciplinas\n");
        return;
      }
    }else if(al.media>=7){ // 6 disciplinas
      if(al.qtd_disciplinas_matriculado>=6){
        printf("Aluno já cadastrado em 6 disciplinas\n");
        return;
      }
    }

    if(al.qtd_disciplinas_matriculado>6){
      printf("O aluno já se matriculou em 6 disciplinas");
      return;
    }
  }



  // FEITA TODAS AS VERIFICAÇÕES, MATRICULA O ALUNO NA DISCIPLINA
  printf("Aluno está pronto para ser matriculado\n");

  strcpy(mat.matricula, matricula);
  strcpy(mat.codigo, codigo);
  strcpy(mat.data, data);
  mat.status = 1;

  fseek(matriculas, 0, 2);
  status = fwrite(&mat, sizeof(Matricula), 1, matriculas);
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

  pos = busca_arvore_aluno(alun, matricula);
  fseek(alunos, pos*sizeof(Aluno), 0);
  status = fread(&al, sizeof(Aluno), 1, alunos);
  al.qtd_disciplinas_matriculado++;

  fseek(alunos, -sizeof(Aluno), 1);
  status = fwrite(&al, sizeof(Aluno), 1, alunos);

  if(status != 1){
    printf("\n[-] Erro ao alterar a qtd de disciplinas matriculadas do aluno\n");
    return;
  }
  else  printf("\n[+] alterada a qtd de disciplinas matriculada do aluno\n");
  printf("\n[+] matriculado com sucesso!!\n");


}


void exclui_matricula(FILE *disciplinas, char codigo[], NOdisciplina *disci, FILE *alunos, char matricula[], NOaluno *alun, FILE *matriculas){
  int status, pos;
  Matricula mat;
  Disciplina dis;
  Aluno al;

  fseek(matriculas, 0, 0);
  while(1){
    status = fread(&mat, sizeof(Matricula), 1, matriculas);
    if(status !=1){
      if(!feof(matriculas))  return;
      else{
        return;
      }
    }
    else{
      if((mat.status == 1) && (strcmp(mat.matricula, matricula) == 0) && (strcmp(mat.codigo, codigo) == 0)){
        printf("\n[+] Matricula encontrada\n");
        mat.status = 0;
        break;
      }
    }
  }

  fseek(matriculas, -sizeof(Matricula), 1);
  status = fwrite(&mat, sizeof(Matricula), 1, matriculas);
  if(status != 1)  printf("[-] Erro ao deletar matricula\n");
  else  printf("[+] Matrícula removida\n");



  pos = busca_arvore_aluno(alun, matricula);
  fseek(alunos, pos*sizeof(Aluno), 0);
  status = fread(&al, sizeof(Aluno), 1, alunos);
  al.qtd_disciplinas_matriculado--;

  fseek(alunos, -sizeof(Aluno), 1);
  status = fwrite(&al, sizeof(Aluno), 1, alunos);
  if(status != 1){
    printf("[-] Erro ao alterar qtd de disciplinas do aluno\n");
    return;
  }else  printf("[+] quantidade de disciplinas do aluno alteradas\n");



  pos = busca_arvore_disciplina(disci, codigo);
  fseek(disciplinas, pos*sizeof(Disciplina), 0);
  status = fread(&dis, sizeof(Disciplina), 1, disciplinas);
  dis.qtd_vagas_ocupadas--;

  fseek(disciplinas, -sizeof(Disciplina), 1);
  status = fwrite(&mat, sizeof(Disciplina), 1, disciplinas);
  if(status != 1){
    printf("[-] Erro ao alterar a quantidade de vagas ocupadas na disciplina\n");
    return;
  }else  printf("[+] Quantidade de vagas ocupadas na disciplina alteradas\n");


  printf("\n[+] Aluno desmatriculado com sucesso\n");

}


void manutencao_matricula(FILE *arq){
  Matricula mat;
  int status;
  FILE *arq2;
  arq2 = fopen("matriculas2.dat", "w+b");
  fseek(arq, 0, 0);
  while(1){
    status = fread(&mat, sizeof(Matricula), 1, arq);
    if(status != 1){

      if(!feof(arq))  break;
      else  break;

    }else{
      if(mat.status == 1)  status = fwrite (&mat, sizeof (Matricula), 1, arq2);;
    }
  }
  fclose(arq);
  fclose(arq2);
  remove("matriculas.dat");
  rename("matriculas2.dat", "matriculas.dat");
}

void exibi_disciplinas(FILE *disciplinas, char codigo[], NOdisciplina *disci, FILE *alunos, char matricula[], NOaluno *alun, FILE *matriculas){
  int status, pos;
  Matricula mat;
  Disciplina dis;
  Aluno al;

  pos = busca_arvore_aluno(alun, matricula);
  if(pos == -1){
    printf("[-] Aluno não cadastrado\n");
    return;
  }

  fseek(matriculas, 0, 0);
  while(1){
    status = fread(&mat, sizeof(Matricula), 1, matriculas);
    if(status !=1){
      if(!feof(matriculas))  return;
      else{
        return;
      }
    }
    else{
      if(mat.status == 1 && strcmp(mat.matricula, matricula) == 0){
        pos = busca_arvore_disciplina(disci, mat.codigo);
        if(pos != -1){
          fseek(disciplinas, pos*sizeof(Disciplina), 0);
          status = fread(&dis, sizeof(Disciplina), 1, disciplinas);
          printf("\n======\n");
          printf("\nCódigo da disciplina: %s",dis.codigo);
          printf("\nNome da disciplina: %s",dis.nome);
          printf("\nHorario da disciplina: %c",dis.horario);
          printf("\nSala da disciplina: %s\n",dis.sala);
        }
      }
    }
  }
}


void exibi_matricula_aluno(FILE *disciplinas, char codigo[], NOdisciplina *disci, FILE *alunos, char matricula[], NOaluno *alun, FILE *matriculas){
  int status, pos;
  Matricula mat;
  Disciplina dis;
  Aluno al;
  int qtd = 0;

  pos = busca_arvore_disciplina(disci, codigo);
  if(pos == -1){
    printf("[-] Disciplina não cadastrada\n");
    return;
  }

  fseek(matriculas, 0, 0);
  while(1){
    status = fread(&mat, sizeof(Matricula), 1, matriculas);
    if(status !=1){
      if(!feof(matriculas))  return;
      else{
        return;
      }
    }
    else{
      if(mat.status == 1 && strcmp(mat.codigo, codigo) == 0){
        pos = busca_arvore_aluno(alun, mat.matricula);
        if(pos != -1){
          fseek(alunos, pos*sizeof(Aluno), 0);
          status = fread(&al, sizeof(Aluno), 1, alunos);
          printf("\n======\n");
          printf("\Matricula do aluno: %s",al.matricula);
          printf("\nNome do aluno: %s",al.nome);
          qtd++;
        }
      }
    }
  }
  printf("\nTotal de alunos matriculados: %d\n", &qtd);
}
