#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct_filme.h"

#define TAMANHO_INICIAL_ARRAY 10
#define TAMANHO_LINHA 2048
#define TAMANHO_SINOPSE 4096

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
        }else if(strncmp(linha, "DATA: ", 6) == 0){
            filme_temp.dataLancamento = atoi(linha + 6);
        }else if(strncmp(linha, "NOTA: ", 6) == 0){
            filme_temp.nota = atof(linha + 6);
        }else if(strncmp(linha, "GENERO: ", 6) == 0){
            filme_temp.tipo = strdup(linha + 6);
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