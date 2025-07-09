#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "struct_filme.h"

#define TAMANHO_INICIAL_ARRAY 10
#define TAMANHO_LINHA 2048
#define TAMANHO_SINOPSE 4096

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

void inicializar_array(ArrayDeFilmes* arr){
    arr->filmes = malloc(TAMANHO_INICIAL_ARRAY * sizeof(Filme));

    if(arr->filmes == NULL){
        printf("Erro ao alocar dinamicamente\n");
        exit(1);
    }

    arr->tamanho_atual = 0;
    arr->capacidade = TAMANHO_INICIAL_ARRAY;
}

void adicionar_filme_ao_array(ArrayDeFilmes* arr, Filme filme){
    if(arr->tamanho_atual >= arr->capacidade){
        int nova_capacidade = arr->capacidade * 2;

        Filme* novo_bloco = realloc(arr->filmes, nova_capacidade * sizeof(Filme));

        if(novo_bloco == NULL){
            printf("Erro ao realocar memória!\n");
            exit(1);
        }

        arr->filmes = novo_bloco;
        arr->capacidade = nova_capacidade;
        printf("[INFO] Array redimensionado para capacidade de %d filmes.\n", nova_capacidade);
    }

    arr->filmes[arr->tamanho_atual] = filme;
    arr->tamanho_atual++;
}

void carregar_filmes(const char* nome_arquivo, ArrayDeFilmes* arr){
    FILE* arquivo = fopen(nome_arquivo, "r");

    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }

    char linha[TAMANHO_LINHA];
    Filme filme_temp;

    // Inicializa ponteiros para evitar lixo de memória
    filme_temp.nome = NULL;
    filme_temp.dataLancamento = 0;
    filme_temp.sinopse = NULL;
    filme_temp.nota = 0;
    filme_temp.tipo = NULL;

    //---------------------------------

    while(fgets(linha, sizeof(linha), arquivo) != NULL){
        remover_nova_linha(linha);

        if(strncmp(linha, "NOME: ", 6) == 0){
            filme_temp.nome = strdup(linha + 6);
            if (filme_temp.nome == NULL) {
              perror("ERRO na alocacao do NOME do filme");
              filme_temp.sinopse = NULL;
              filme_temp.tipo = NULL;
              continue;
            }
        }else if(strncmp(linha, "DATA: ", 6) == 0){
            filme_temp.dataLancamento = atoi(linha + 6);
        }else if(strncmp(linha, "NOTA: ", 6) == 0){
            filme_temp.nota = atof(linha + 6);
        }else if(strncmp(linha, "GENERO: ", 8) == 0){
            filme_temp.tipo = strdup(linha + 8);
            if(filme_temp.tipo == NULL){
              perror("ERRO na alocacao do TIPO/GENERO do filme");
              filme_temp.nome = NULL;
              filme_temp.sinopse = NULL;
              continue;
            }
        }else if(strcmp(linha, "SINOPSE_INICIO") == 0){
            char buffer_sinopse[TAMANHO_SINOPSE] = "";

            while(fgets(linha, sizeof(linha), arquivo) != NULL){
                remover_nova_linha(linha);

                if(strcmp(linha, "SINOPSE_FIM") == 0){
                    break;
                }

                strcat(buffer_sinopse, linha);
                strcat(buffer_sinopse, "\n");
            }

            filme_temp.sinopse = strdup(buffer_sinopse);
            if(filme_temp.sinopse == NULL){
              perror("ERRO na alocacao da SINOPSE do filme");
              filme_temp.nome = NULL;
              filme_temp.tipo = NULL;
              continue;
            }

            adicionar_filme_ao_array(arr, filme_temp);

            filme_temp.nome = NULL;
            filme_temp.dataLancamento = 0;
            filme_temp.nota = 0;
            filme_temp.sinopse = NULL;
            filme_temp.tipo = NULL;
        }
    }

    fclose(arquivo);
    printf("Carga finalizada!! %d filmes carregados para a memória.\n", arr->tamanho_atual);
}

void liberar_array(ArrayDeFilmes* arr){
    if(arr->filmes != NULL){
        for(int i = 0; i < arr->tamanho_atual; i++){
            //free(arr->filmes[i].dataLancamento);
            free(arr->filmes[i].nome);
            //free(arr->filmes[i].nota);
            free(arr->filmes[i].sinopse);
            free(arr->filmes[i].tipo);
        }
        free(arr->filmes);
    }
    arr->filmes = NULL;
    arr->capacidade = 0;
    arr->tamanho_atual = 0;
}

void adicionar_novo_filme(ArrayDeFilmes* arr){
    Filme novo_filme;

    char buffer[TAMANHO_LINHA];

    printf("\n----- Adicionar Novo Filme -----\n");

    printf("NOME: ");
    fgets(buffer, sizeof(buffer), stdin);
    remover_nova_linha(buffer);
    novo_filme.nome = strdup(buffer);

    printf("ANO: ");
    fgets(buffer, sizeof(buffer), stdin);
    novo_filme.dataLancamento = atoi(buffer);

    printf("NOTA (0.0 - 10.0): ");
    fgets(buffer, sizeof(buffer), stdin);
    novo_filme.nota = atof(buffer);

    printf("Gênero: ");
    fgets(buffer, sizeof(buffer), stdin);
    remover_nova_linha(buffer);
    novo_filme.tipo = strdup(buffer);

    printf("Sinopse (digite ENTER para novas linhas)\n");
    printf("Para finalizar, digite FIM em uma nova linha e pressione ENTER\n");

    char buffer_sinopse[TAMANHO_SINOPSE] = "";

    while(fgets(buffer, sizeof(buffer), stdin) != NULL){
        if(strncmp(buffer, "FIM\n", 4) == 0){
            break;
        }
        strcat(buffer_sinopse, buffer);
    }
    novo_filme.sinopse = strdup(buffer_sinopse);

    adicionar_filme_ao_array(arr, novo_filme);

    printf("\n [SUCESSO] - Filme %s adicionado ao banco de dados.\n", novo_filme.nome);
    printf("Lembre-se de salvar ao sair do programa para manter as alterações!\n");

}


void remover_filme(ArrayDeFilmes* arr){

    

    for (int i=0; i <arr->tamanho_atual; i++){
        printf("[%d]- %s\n", i+1, arr->filmes[i].nome);
    }
    char buffer[10];
    printf("Digite o numero do film para remover");
    fgets(buffer, sizeof(buffer), stdin);
    
    int filme_numero;
    sscanf(buffer, "%d",&filme_numero);
    int indice_remov= filme_numero-1;
    
    if(indice_remov < 0 || indice_remov >= arr->tamanho_atual){
      printf("\nERRO, Numero de filme invalido!\n");
      return;
    }

    printf("\n Removendo o filme: %s\n", arr->filmes[indice_remov].nome);

    free(arr->filmes[indice_remov].nome);
    free(arr->filmes[indice_remov].tipo);
    free(arr->filmes[indice_remov].sinopse);

    for(int i=indice_remov; i<arr-> tamanho_atual-1;i++){
        arr->filmes[i]= arr->filmes[i+1];
    }

    arr->tamanho_atual--;

    limpar_buffer_entrada_usuario();

}


//salvar as alterações no banco de dados (arquivo)
void salvar_para_arquivo(const char* nome_arquivo, const ArrayDeFilmes* arr) {
    FILE* arquivo = fopen(nome_arquivo, "w");

    if (arquivo == NULL) {
        perror("ERRO CRÍTICO: Não foi possível abrir o arquivo para salvar");
        return;
    }

    // Percorre o array na memória
    for (int i = 0; i < arr->tamanho_atual; i++) {
        Filme filme_atual = arr->filmes[i];
        
        fprintf(arquivo, "===FILME===\n");
        fprintf(arquivo, "NOME: %s\n", filme_atual.nome ? filme_atual.nome : "");
        fprintf(arquivo, "DATA: %d\n", filme_atual.dataLancamento);
        fprintf(arquivo, "NOTA: %.1f\n", filme_atual.nota);
        fprintf(arquivo, "GENERO: %s\n", filme_atual.tipo ? filme_atual.tipo : "");

        //gravar a sinopse da maneira certa
        fprintf(arquivo, "SINOPSE_INICIO\n");
        fprintf(arquivo, "%s", filme_atual.sinopse ? filme_atual.sinopse : "");
        
        // Garante que a sinopse termine com \n antes do marcador de fim
        if (filme_atual.sinopse && strlen(filme_atual.sinopse) > 0 && filme_atual.sinopse[strlen(filme_atual.sinopse)-1] != '\n') {
            fprintf(arquivo, "\n");
        }
        fprintf(arquivo, "SINOPSE_FIM\n");
    }

    fclose(arquivo);

}
void buscar_filme(const ArrayDeFilmes* arr) {
    if (arr->tamanho_atual == 0) {
        printf("Nenhum filme na memória.\n");
        return;
    }

    char termo[256];
    printf("\n----- BUSCAR FILME -----\n");
    printf("Digite parte do nome do filme a ser buscado: ");
    fgets(termo, sizeof(termo), stdin);
    remover_nova_linha(termo);

    int encontrou = 0;

    char* termo_minusculo = converter_string_para_lowercase(termo);
    if(termo_minusculo == NULL){
      perror("Erro ao processar termo minusculo");
      return;
    }

    for (int i = 0; i < arr->tamanho_atual; i++) {

      char* nome_filme_minusculo = converter_string_para_lowercase(arr->filmes[i].nome);
      if(nome_filme_minusculo == NULL){
        printf("Erro ao processar nome do filme na busca.\n");
        continue;
      }


        if (strstr(nome_filme_minusculo, termo_minusculo)) {
            encontrou = 1;

            printf("\n=== Filme %d ===\n", i + 1);
            printf("Nome: %s\n", arr->filmes[i].nome);
            printf("Ano: %d\n", arr->filmes[i].dataLancamento);
            printf("Nota: %.1f\n", arr->filmes[i].nota);
            printf("Gênero: %s\n", arr->filmes[i].tipo ? arr->filmes[i].tipo : "(sem gênero)");
            printf("Sinopse:\n%s\n", arr->filmes[i].sinopse ? arr->filmes[i].sinopse : "(sem sinopse)");
        }
    }


    free(termo_minusculo);

    if (!encontrou) {
        printf("\nNenhum filme encontrado com esse termo.\n");
    }

    printf("\nPressione ENTER para continuar...");

    limpar_buffer_entrada_usuario();
}

void listar_filmes(const ArrayDeFilmes *arr){
 if(arr->tamanho_atual == 0) {
   printf("Nenhum filme na memoria.\n");
   return;
 }

 for(int i = 0; i < arr->tamanho_atual; i++){
   printf("\nFilme %d: %s", (i + 1), arr->filmes[i].nome);
 }
}


