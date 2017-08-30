
#ifndef ESTRUTURAS
#define ESTRUTURAS

typedef struct al{ // não podem ter 2 alunos com a mesma matricula
  char matricula[10];
  char nome[40];
  char email[40];
  char telefone[11];
  float media; // media do semestre anterior -> 0
  int qtd_disciplinas_matriculado; // ao cadastrar novo -> 0
  int status; // -> 1 = ativo // 0 = deletado
}Aluno;

typedef struct dis{
  char codigo[7]; // não pode ter disciplina com o mesmo codigo || DEVE PASSAR POR VALIDAÇÃO  || 3 primeiros = letras, 4 ultimos = numeros
  char nome[20]; // apenas conter letras e espaços
  char horario[5];
  char sala[4];
  int qtd_total_vagas; //
  int qtd_vagas_ocupadas; // começa com 0
  int status; // 1-> ativo || 0->deletado
}Disciplina;

typedef struct mat{
  char codigo[7];
  char matricula[10];
  char data[10];
  int status;
}Matricula;

typedef struct arv{
  char matricula;
  int pos;
  struct arv *dir, *esq;
}NOaluno;

typedef struct ar{
  char codigo[7];
  int pos;
  struct ar *dir, *esq;
}NOdisciplina;

#endif
