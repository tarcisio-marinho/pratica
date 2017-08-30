
#include<stdio.h>
#include "types.h"


void cadastrar_aluno(FILE *arq, NOaluno **raiz, int pos);
void alterar_aluno(char matricula[], FILE *arq, NOaluno *raiz); // busca no indice do arquivo, se existir -> exibe, altera -> não existe  == STATUS == 1
void exibir_aluno(char matricula[], FILE *arq, NOaluno *raiz); // busca no indice do arquivo, se existir -> exibe, senão -> não existe  == STATUS == 1
void remover_aluno(char matricula[], FILE *arq, NOaluno **raiz); // busca no indice do arquivo, se existir -> remove -> status = 0 , senão -> não existe == STATUS == 1
int procura_aluno_no_arquivo(char matricula[], FILE *arq, int qtd); // busca a posicao do aluno, se não existir, retorna -1;
int valida_matricula(NOaluno *raiz,char matricula[]);
int verifica_matricula(char matricula[], NOaluno *raiz);
void manutencao_aluno(FILE *arq);
