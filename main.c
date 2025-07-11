#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funcoes_filme.h"

#define OPCAO_SAIDA 6

int main(void) {
    srand(time(NULL));

    printf("\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("          MOVIELOG");

    ArrayDeFilmes meu_banco_de_dados;
    inicializar_array(&meu_banco_de_dados);
    carregar_filmes("filmes.txt", &meu_banco_de_dados);

    int opcao_menu = 0;
    char buffer_opcao[10];

    while (opcao_menu != OPCAO_SAIDA) {
        printf("\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
        printf("            MENU\n");
        printf("[1] ADICIONAR FILME\n");
        printf("[2] BUSCAR FILME\n");
        printf("[3] REMOVER FILME\n");
        printf("[4] LISTAR FILMES\n");
        printf("[5] RECOMENDAÇAO DE FILME ALEATORIO\n");
        printf("[6] SALVAR ALTERAÇÕES E SAIR\n");
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
                remover_filme(&meu_banco_de_dados);
                break;  
            case 4:
                listar_filmes(&meu_banco_de_dados);
                break;
            case 5:
                recomenda_aleatorio(&meu_banco_de_dados);
                break;
            case 6:
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

