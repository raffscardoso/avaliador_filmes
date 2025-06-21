#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct_filme.h"

#define NUM_FILMES 4

void print_boxed_text(char* text, int width);
void imprime_filme(const ArrayDeFilmes*);

int main(void){
    printf("-=-=-=-=-=-=-=-=-=-=-\n");
    printf("LETTERBOXD só que BR\n");
    printf("-=-=-=-=-=-=-=-=-=-=-\n");

    ArrayDeFilmes meu_banco_de_dados;

    inicializar_array(&meu_banco_de_dados);

    carregar_filmes("filmes.txt", &meu_banco_de_dados);

    printf("\n=== FILMES ATUALMENTE NA MEMÓRIA ===\n");
    imprime_filme(&meu_banco_de_dados);

    //------------ MENU DAS OPÇÕES
    int resposta;
    printf("\n=-=- MENU -=-=\n");
    printf("[1] ADICIONAR FILME\n[2] BUSCAR FILME\n[3] SALVAR ALTERAÇÕES || Resposta: ");
    scanf("%d", &resposta);

    //ajeitar depois as paradas
    if(resposta == 1){

    }else if(resposta == 2){

    }else if(resposta == 3){

    }

    liberar_array(&meu_banco_de_dados);

    return 0;
}

//ajeitar essa função depois depois
void print_boxed_text(char* text, int width){
    int i = 0, col = 0;

    while(text[i] != '\0'){
        putchar(text[i]);
        col++;

        if(col == width){
            putchar('\n');
            col = 0;
        }
        i++;
    }

    if(col != 0){
        putchar('\n');
    }
}

void imprime_filme(const ArrayDeFilmes* arr){
    for(int i = 0; i < arr->tamanho_atual; i++){
        printf("Filme: %d\n", i + 1);
        printf("== Nome: %s\n", arr->filmes[i].nome);
        printf("== Data de Lanaçamento: %d\n", arr->filmes[i].dataLancamento);
        printf("== Nota: %.2f\n", arr->filmes[i].nota);
        //print_boxed_text(arr->filmes->sinopse, 50);
        printf("== Sinopse: %s\n", arr->filmes[i].sinopse);
        printf("== Gênero: %s\n", arr->filmes[i].tipo);
    }
}
