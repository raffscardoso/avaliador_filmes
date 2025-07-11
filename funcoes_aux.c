#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char* converter_string_para_lowercase(const char* str){
  if(str == NULL){
    return NULL;
  }

  char* str_minuscula = malloc(strlen(str) + 1);
  if(str_minuscula == NULL){
    perror("Erro na alocacao de memoria na da string em letras minusculas!");
    return NULL;
  }

  for(int i = 0; str[i] != '\0'; i++){
    str_minuscula[i] = tolower((unsigned char)str[i]);
  }
  str_minuscula[strlen(str)] = '\0';

  return str_minuscula;
}

void limpar_buffer_entrada_usuario(){
  int c;
  while((c = getchar()) != '\n' && c != EOF);
}

void remover_nova_linha(char* str){
    size_t len = strlen(str);

    if(len > 0 && str[len - 1] == '\n'){
        str[len - 1] = '\0';
    }
}


