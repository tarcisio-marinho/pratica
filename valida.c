
#include<stdio.h>
#include<string.h>
#include<ctype.h>

// validacoes do aluno

int valida_nome(char nome[]){

}

int valida_matricula(char matricula[]){

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
    if(strlen(codigo)!=7)    return 1;
    else{
        if(codigo[0]<'a' || codigo[0]>'z')    return 2;
        else if(codigo[1]<'a' || codigo[1]>'z')    return 3;
        else if(codigo[2]<'a' || codigo[2]>'z')    return 4;
        else if(codigo[3]<'1' || codigo[3]>'9')    return 5;
        else if(codigo[4]<'1' || codigo[4]>'9')    return 6;
        else if(codigo[5]<'1' || codigo[5]>'9')    return 7;
        else if(codigo[6]<'1' || codigo[6]>'9')    return 8;
        else    return 0;
    }
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

}
