#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct_filme.h"


//protótipo de funções locais
void imprime_filme(const ArrayDeFilmes* arr);

int main(void) {
    printf("-=-=-=-=-=-=-=-=-=-=-\n");
    printf("LETTERBOXD só que BR\n");
    printf("-=-=-=-=-=-=-=-=-=-=-\n");

    ArrayDeFilmes meu_banco_de_dados;
    inicializar_array(&meu_banco_de_dados);
    carregar_filmes("filmes.txt", &meu_banco_de_dados);

    printf("\n=== FILMES ATUALMENTE NA MEMÓRIA ===\n");
    imprime_filme(&meu_banco_de_dados);

    int opcao_menu = 0;
    char buffer_opcao[10];

    while (opcao_menu != 3) {
        printf("\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
        printf("            MENU\n");
        printf("[1] ADICIONAR FILME\n");
        printf("[2] BUSCAR FILME\n");
        printf("[3] SALVAR ALTERAÇÕES E SAIR\n");
        printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
        printf("Escolha uma opção: ");

        fgets(buffer_opcao, sizeof(buffer_opcao), stdin);
        opcao_menu = atoi(buffer_opcao);

        switch (opcao_menu) {
            case 1:
                adicionar_novo_filme(&meu_banco_de_dados);
                break;
            case 2:
                buscar_filme(&meu_banco_de_dados);
                break;
            case 3:
                printf("\nSalvando dados no arquivo 'filmes.txt'...\n");
                salvar_para_arquivo("filmes.txt", &meu_banco_de_dados);
                printf("Dados salvos! Saindo...\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
                break;
        }
    }

    liberar_array(&meu_banco_de_dados);

    return 0;
}

//imprimir os filmes
void imprime_filme(const ArrayDeFilmes* arr) {
    if (arr->tamanho_atual == 0) {
        printf("Nenhum filme na memória.\n");
        return;
    }
    for (int i = 0; i < arr->tamanho_atual; i++) {
        printf("\n-----------------------------------\n");
        printf("Filme %d:\n", i + 1);
        printf("  == Nome: %s\n", arr->filmes[i].nome);
        printf("  == Ano de Lançamento: %d\n", arr->filmes[i].dataLancamento);
        printf("  == Nota: %.1f\n", arr->filmes[i].nota);
        printf("  == Gênero: %s\n", arr->filmes[i].tipo);
        printf("  == Sinopse: %s\n", arr->filmes[i].sinopse ? arr->filmes[i].sinopse : "(vazia)");
        // Correção no comentário: arr->filmes[i].sinopse
        // print_boxed_text(arr->filmes[i].sinopse, 50); 
    }
}
