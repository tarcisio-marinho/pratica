#include<stdio.h>
#include "types.h"


void cadastrar_disciplina(FILE *arq, NOdisciplina **raiz, int pos);
void alterar_disciplina(char codigo[], FILE *arq, NOdisciplina *raiz); // busca no indice do arquivo, se existir -> exibe, altera -> não existe  == STATUS == 1
void exibir_disciplina(char codigo[], FILE *arq, NOdisciplina *raiz); // busca no indice do arquivo, se existir -> exibe, senão -> não existe  == STATUS == 1
void remover_disciplina(char codigo[], FILE *arq, NOdisciplina **raiz); // busca no indice do arquivo, se existir -> remove -> status = 0 , senão -> não existe == STATUS == 1
int procura_disciplina_no_arquivo(char codigo[], FILE *arq, int qtd); // busca a posicao do disciplina, se não existir, retorna -1;
int verifica_codigo(char codigo[], NOdisciplina *raiz);
void manutencao_disciplina(FILE *arq);
