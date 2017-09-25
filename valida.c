#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "valida.h"

int potencia(int expo){
	int total = 1, c;
	for(c = 1; c <= expo; c++){
		total *= 2;
	}
	return total;
}

void retirarEspaco(char string[]){
	int pos = 0, c;
	char aux;
	do{

		if(string[pos] == ' ' && string[pos + 1] == '\0'){
			string[pos] = '\0';

		}else{
			if( (string[0] == ' ' && string[1] != ' ')  ||  (string[pos] == ' ' && string[pos + 1] == ' ') ){
				for(c = pos; c<strlen(string); c++){
					string[c] = string[c + 1];
				}

			}else{
				pos++;
			}
		}
	}while(string[pos] != '\0');
}

void organizarCaracteres(char string[]){
	int c, n = 0;

	string[n] = toupper(string[n]);
	n++;
	for(c = n; c<strlen(string); c++){
		string[c] = tolower(string[c]);
	}

}

int validar_nome_aluno_disciplina(char nome[]) {
	int c;

	if(nome[0] == '\0')
		return 1;

	else{
		for(c = 0; c < strlen(nome); c++){
			if( !isalpha(nome[c]) && !isspace(nome[c]) ){
				return 1;
			}
		}
	}
	return 0;
}

int validar_qtd_vagas(int qtd_vagas) {
	if (qtd_vagas < 30 || qtd_vagas > 60) {
		return -1;
	}
	else {
		return 0;
	}
}

int validar_email(char email[]) {
	int i;
	int ctt = 0;
	if (email[0] == '\0') {
		return -2;
	}
	for (i = 0; i < strlen(email); i++) {
		if (email[i] == '\0') {
			break;
		}
		if (email[i] == '@') {
			ctt++;
		}
		else if (!(isdigit(email[i]) || isalpha(email[i]) || '.' || '-' || '_' || '@')) {
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
	int i;
	for (i = 0; i < 12; i++) {
		if (tel[i] == '\0') {
			if (i < 11) {
				return -2;
			}
			return 0;
		}
		if (isdigit(tel[i]) == 0) {
			return -1;
		}
	}
}


int validar_horario_disciplina(char *letra) {
	int i;
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
	tamanho = strlen(matricula);
	if (tamanho != 10) {
		return -1;
	}
	for (i = 0; i < 9; i++) {
		soma = soma + (matricula[i] - 48)*potencia(i);
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

int validar_sala_disciplina(char sala[]) {
	int i;

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
