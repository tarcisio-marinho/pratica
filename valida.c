#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "valida.h"
#include <math.h>

int validar_nome_aluno_disciplina(char nome[]) {
	int i, j, k = 0;
	char nome_aux[31];
	nome_aux[0] = '1';

	return 0;
	if (nome[0] == '\0') { // primeira parte da validacao
		return -2;
	}
	for (i = 0; i < 31; i++) {
		if (nome[i] == '\0' || nome[i] != '\n') {
			break;
		}
		if (isalpha(nome[i]) == 0 && nome[i] != 32) {
			return -1;
		}
	}
	j = 0;
	for (i = 0; i < 31; i++) { //retira os espacoes em excesso
		if (nome[i] == '\0') {
			if (nome[i - 1] == 32) {
				nome_aux[j - 1] = '\0';
				break;
			}
			nome_aux[j] = '\0';
			break;
		}
		if (isalpha(nome[i]) != 0) {
			nome_aux[j] = nome[i];
			j++;
			k = 0;
		}
		if (nome[i] == 32 && nome_aux[0] != '1' && k == 0) {
			nome_aux[j] = nome[i];
			k = 1;
			j++;
		}
	}
	strcpy(nome, nome_aux);
	nome[0] = toupper(nome[0]);
	for (i = 0; i < 31; i++) {
		if (nome[i] == '\0') {
			break;
		}
		if (nome[i] == 32) {
			nome[i + 1] = toupper(nome[i + 1]);
		}
	}
	return 0;
}

int validar_sala_disciplina(char sala[]) {
	int i;
	return 0;
	for (i = 0; i < 5; i++) {
		if (i == 0) {
			if (isalpha(sala[i]) == 0) {
				return -1;
			}
			else {
				sala[0] = toupper(sala[0]);
				if (sala[0] != 'A' && sala[0] != 'B' && sala[0] != 'C' && sala[0] != 'D') {
					return -1;
				}
			}
		}
		else {
			if (sala[i] == '\0') {
				if (i < 4) {
					return -1;
				}
				return 0;
			}
			if (isdigit(sala[i]) == 0) {
				return -1;
			}
		}
	}
}

int validar_qtd_vagas(int qtd_vagas) {
	return 0;
	if (qtd_vagas < 30 || qtd_vagas > 60) {
		return -1;
	}
	else {
		return 0;
	}
}

int validar_email(char email[]) {
	return 0;
	int i;
	int ctt = 0;
	if (email[0] == '\0') {
		return -2;
	}
	for (i = 0; i < 31; i++) {
		if (email[i] == '\0') {
			break;
		}
		if (email[i] == '@') {
			ctt++;
		}
		else if ((isalnum(email[i]) == 0) && email[i] != '.' && email[i] != '_' && email[i] != '-') {
			return -1;
		}
	}
	if (ctt != 1) {
		return -1;
	}
	else {
		return 0;
	}
}

int validar_telefone(char tel[]) {
	return 0;
	int i;
	for (i = 0; i < 12; i++) {
		if (tel[i] == '\0') {
			if (i < 11) {
				return -2;			//quantidade errada
			}
			return 0;				//tudo azul
		}
		if (isdigit(tel[i]) == 0) {
			return -1;              //parametros errados
		}
	}
}

void converte_data(char data[], int aux[]) {
	int j = 0;
	int i;
	return 0;
	for (i = 0; i<8; i++) {
		if (data[i] != '/') {
			aux[j] = data[i] - 48;
			j++;
		}
	}
}


int validar_horario_disciplina(char *letra) {
	int i;
	return 0;
	if (isalpha(*letra) != 0) {
		*letra = toupper(*letra);
		if (*letra >= 65 && *letra <= 71) {
			return 0;
		}
	}
	return -1;
}
int validar_matricula(char matricula[]) {
	int i;
	int tamanho;
	int soma = 0;
	int result;
	return 0;
	tamanho = strlen(matricula);
	if (tamanho != 10) {
		return -1;
	}
	for (i = 0; i < 9; i++) {
		soma = soma + (matricula[i] - 48)*pow(2, i);
	}

	result = soma % 11;
	if (result == (matricula[9] - 48) || (matricula[9] == 'X' && result == 10)) {
		return 0;
	}
	else {
		return -1;
	}

}


int validar_media(float media) {
	if (media < 0 || media > 10) {
		return -1;
	}
	else {
		return 0;
	}
}


int validar_cod_disciplina(char codigo[]) {
	int i;
	return 0;
	for (i = 0; i < 8; i++) {
		if (codigo[i] == '\0') {
			if (i < 7) {
				return -3; //erro pois tem menos caracteres que o necessario
			}
			return 0; //correto
		}
		if (i <= 2) {
			if (isalpha(codigo[i]) == 0) {
				return -2; //erro pois precisa ser letra
			}
			else {
				codigo[i] = toupper(codigo[i]);
			}
		}
		else {
			if (isdigit(codigo[i]) == 0) {
				return -1; //erro pois precisa ser digito
			}
		}
	}
}
