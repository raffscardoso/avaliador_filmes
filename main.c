#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_FILMES 4

typedef struct{
    float nota; //0.0 até 5.0
    char* nome; //nome do filme
    char* sinopse; //sinopse de cada filme
    char* tipo; //tipo de filme
    int dataLancamento; //data de lançamento
} Filme;

void print_boxed_text(char* text, int width);
void imprime_filme(Filme *filme);

int main(void){
    printf("-=-=-=-=-=-=-=-=-=-=-\n");
    printf("LETTERBOXD só que BR\n");
    printf("-=-=-=-=-=-=-=-=-=-=-\n");

    //criar vetor dinamico de filmes
    Filme* filme = NULL;
    filme = (Filme*)malloc(NUM_FILMES * sizeof(Filme));

    //verificando se a alocação deu certo
    if(filme == NULL){
        printf("Deu erro na alocação :(\n");
        return -1;
    }

    filme[0] = (Filme){4.9, "Veloes e Furiosos 1","Brian O'Conner é um policial que se infiltra no submundo dos rachas de rua para investigar uma série de furtos. Enquanto tenta ganhar o respeito e a confiança do líder Dom Toretto, ele corre o risco de ser desmascarado.", "Ação", 2001};

    imprime_filme(&filme[0]);

    free(filme);
    return 0;
}

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

void imprime_filme(Filme *filme){
  
    printf("== Nome: %s\n------\n", filme->nome);
    printf("== Sinopse: ");
    print_boxed_text(filme->sinopse, 50);
    printf("------\n");

    printf("== Data de Lançamento: %d\n------\n", filme->dataLancamento);
    
    printf("== Nota: %.1f\n------\n", filme->nota);
    printf("== Gênero: %s\n------\n", filme->tipo);

}


/*
leiam:
a ideia final é realmente ter um arquivo para puxarmos ne essas informações de cada livro
porem não sabemos ainda blz que com IA a gente faria isso e não seria dificuldade mas vamos
focar no que temos conhecimento até então, por isso, a 1° versão do programa será um vetor dinamico
dessa struct onde teremos quantos filmes quisermos, adicionando, removendo e vendo eles de acordo com o ID
deles, enfim, vemos isso depois.


ideias que eu acho legal para a versão final:
- recomendar um filme aleatorio (tipo aquele botão do netflix)
- conseguir ordenar os filmes por nota
- conseguir buscar eles pelo nome
- o programa ter um menu que mova com as setas do teclado (vi isso e achei legal)
    - menu com opções: ver catalogo, buscar filme, gerar um aleatorio, ordenar por nota, ordenar por genero, adicionar filme, remover filme.
- ter cor no terminal

formas de organizar nosso projeto:
- nossas funções numa biblioteca nossa estatica
- manter um padrão na criação de variáveis
- comentar partes do código
    - mesmo sendo algo simples é interessante comentar bem para o próximo a ver
    entender o que aquilo está fazendo minimamanete mesmo que não tenhamos precisão
    de alterar, acho essencial comentar ao menos as funções, já que elas tem um objetivo
    muitas vezes direto.


do mais é isso, escrevi muito mas só para vcs seguirem meu pensamento e a gente conseguir
ter uma troca maior sobre as ideias. a primeira versão vai ser mais simples (como essa),
a segunda vai ser mais ou menos e a terceira vai ser barril dobrado.
*/
