
#include<stdio.h>
#include<string.h>
#include<ctype.h>

// validacoes do aluno

int valida_nome(char nome[]){
    return 0;
}

int valida_matricula(char matricula[]){
    int i, soma = 0, resto;
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


int valida_email(char email[]){
    int i, count=0;
    for(i=0;i<strlen(email);i++){
        if(email[i]=='@')    count++;
        if(isalnum(email[i])==0 || email[i]!='-' || email[i] != '_' || email[i]!='.')    return 1;
    }
    if(count > 1)    return 1;
    return 0;
}

int valida_telefone(char telefone[]){
    int i;
    if(strlen(telefone)!=11)    return 1;
    for (i=0;i<strlen(telefone);i++){
        if(telefone[i]<'0' || telefone[i]>'9')    return 1;
    }
    return 0;
}

int valida_media(float media){
    if(media<0||media>10)    return 1;
    else    return 0;
}






// validacoes da disciplina

int valida_codigo(char codigo[]){
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
    if(horario<'A' || horario>'G')    return 1;
    else   return 0;
}

int valida_sala(char sala[]){
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
    if(total<30 || total>60)    return 1;
    else    return 0;
}

int valida_data_matricula(char data[]){
    return 0;
}

