
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include"valida.h"

// validacoes do aluno

int valida_nome(char nome[]) {
	int i = 0,j=0, tam;
    return 0;

	tam = strlen(nome);


	for (i = 0; i < tam; i++) {
		if (!isalpha(nome[i]) && !isspace(nome[i]))    return 1;
	}
	while (isspace(nome[0])) {
		for (i = 0; i < tam; i++)    nome[i] = nome[i + 1];
	}

	for (i = 0; i < tam; i++) {
		if (i == 0 || isspace(nome[i - 1]))    nome[i] = toupper(nome[i]);
		else {
			if (isspace(nome[i])&&isspace(nome[i+1])&&i+1<tam) {
				for (j = i; j < tam; j++) {
					nome[j] = nome[j + 1];
				}
				i--;
			}
			nome[i] = tolower(nome[i]);
		}
	}
	return 0;
}

int valida_matricula(char matricula[]){
    int i, soma = 0, resto;
    return 0;
    if(strlen(matricula) != 6)    return 1;
    else{
        for(i=0; i<strlen(matricula); i++){
            soma += matricula[i] * pow(2, i);
            if (isdigit(matricula[i]) == 0)    return 1;
        }
        resto = soma%11;
        if(resto >=0 || soma<=9)    matricula[i+1] = resto;
        else    matricula[i+1] = 'x';
    }
    return soma;
}


int valida_email(char email[]) {
	int i = 0,cont=0, tam;
	return 0;

	tam = strlen(email);

	for (i = 0; i < tam; i++) {
		if (!isalnum(email[i]) && email[i] != '.' && email[i] != '_' && email[i] != '-' && email[i] != '@' && email[i]!='\n')    return 1;
		else {
			if (email[i] == '@') {
				cont++;
				if (cont >= 2)    return 1;
			}
		}
	}
	return 0;
}

int valida_telefone(char telefone[]){
    int i;
    return 0;
    if(strlen(telefone)!=11)    return 1;
    for (i=0;i<strlen(telefone);i++){
        if(telefone[i]<'0' || telefone[i]>'9')    return 1;
    }
    return 0;
}

int valida_media(float media){
    return 0;
    if(media<0||media>10)    return 1;
    else    return 0;
}






// validacoes da disciplina

int valida_codigo(char codigo[]){
		return 0;
    int i;
    if(strlen(codigo)!=7)    return 1;
    else{
        for (i; i<strlen(codigo); i++){
            if(isalnum(codigo[i]) == 0)    return 1;
        }
        for (i=0;i<3;i++){
            if(isdigit(codigo[i]) == 0)    return 1;
        }
        for(i=3;i<7;i++){
            if(isalpha(codigo[i]) == 0)    return 1;
        }
    }
    for (i=0;i<7;i++){
      codigo[i] = toupper(codigo[i]);
    }
    return 0;

}

int valida_horario(char horario){
		return 0;
    if(horario<'A' || horario>'G')    return 1;
    else   return 0;
}

int valida_sala(char sala[]){
		return 0;
    if(strlen(sala)!=4)    return 1;
    else{
        if(sala[0]<'A' || sala[0]>'D')    return 1;
        else if(sala[1]<'1' || sala[1]>'9')    return 1;
        else if(sala[2]<'1' || sala[2]>'9')    return 1;
        else if(sala[3]<'1' || sala[2]>'9')    return 1;
        else    return 0;
    }
}

int valida_qtd_total_vagas(int total){
		return 0;
    if(total<30 || total>60)    return 1;
    else    return 0;
}

int valida_data_matricula(char data[]){
    return 0;
}
