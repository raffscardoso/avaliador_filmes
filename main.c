#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funcoes_filme.h"

#define OPCAO_SAIDA 6

int main(void) {
    srand(time(NULL));

    printf("\n" BG_BLUE "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" RESET "\n");
    printf(RED "          MOVIELOG" RESET);


    ArrayDeFilmes meu_banco_de_dados;
    inicializar_array(&meu_banco_de_dados);
    carregar_filmes("filmes.txt", &meu_banco_de_dados);

    OpcaoMenu menu[] = {
      {"ADICIONAR FILME", adicionar_novo_filme},
      {"BUSCAR FILME", (PtrFunc)buscar_filme},
      {"REMOVER FILME", remover_filme},
      {"LISTAR FILMES", (PtrFunc)listar_filmes},
      {"RECOMENDACAO FILME ALEATORIO", (PtrFunc)recomenda_aleatorio},
    };


    int num_opcoes = sizeof(menu) / sizeof(menu[0]);
    int opcao_user = 0;

    while (opcao_user != num_opcoes + 1) {
      printf("\n" BG_BLUE "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" RESET "\n");
      printf(RED "            MENU" RESET "\n");

      for (int i = 0; i < num_opcoes; i++) {
            printf("[%d] %s\n", i + 1, menu[i].descricao);
      }

      printf("[%d] SALVAR ALTERAÇÕES E SAIR\n", num_opcoes + 1);
      printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
      printf("Escolha uma opção: ");
      char buffer_opcao[10];
      fgets(buffer_opcao, sizeof(buffer_opcao), stdin);
      opcao_user = atoi(buffer_opcao);

      if (opcao_user> 0 && opcao_user <= num_opcoes) {
        int indice_escolhido = opcao_user - 1;
        menu[indice_escolhido].executar(&meu_banco_de_dados);
      } else if (opcao_user == num_opcoes + 1) {
        printf("\nSalvando dados no arquivo 'filmes.txt'...\n");
        salvar_para_arquivo("filmes.txt", &meu_banco_de_dados);
        printf("Dados salvos! Saindo...\n");
      } else {
        printf("\nOpção inválida! Tente novamente.\n");
      }
    }

    liberar_array(&meu_banco_de_dados);

    return 0;
}

