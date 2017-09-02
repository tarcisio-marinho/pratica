
#ifndef ESTRUTURAS
#define ESTRUTURAS

typedef struct al{ // não podem ter 2 alunos com a mesma matricula
  char matricula[11];
  char nome[41];
  char email[41];
  char telefone[12];
  float media; // media do semestre anterior -> 0
  int qtd_disciplinas_matriculado; // ao cadastrar novo -> 0
  int status; // -> 1 = ativo // 0 = deletado
}Aluno;

typedef struct dis{
  char codigo[8]; // não pode ter disciplina com o mesmo codigo || DEVE PASSAR POR VALIDAÇÃO  || 3 primeiros = letras, 4 ultimos = numeros
  char nome[21]; // apenas conter letras e espaços
  char horario;
  char sala[5];
  int qtd_total_vagas; //
  int qtd_vagas_ocupadas; // começa com 0
  int status; // 1-> ativo || 0->deletado
}Disciplina;

typedef struct mat{
  char codigo[8];
  char matricula[11];
  char data[11];
  int status;
}Matricula;

typedef struct arv{
  char matricula[11];
  int pos;
  struct arv *dir, *esq;
}NOaluno;

typedef struct ar{
  char codigo[7];
  int pos;
  struct ar *dir, *esq;
}NOdisciplina;

#endif
