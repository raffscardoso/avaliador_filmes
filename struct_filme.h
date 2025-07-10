#ifndef STRUCT_FILME
#define STRUCT_FILME


typedef struct{
    char* nome; //nome do filme
    int dataLancamento; //data de lançamento
    float nota; //0.0 até 5.0
    char* tipo; //tipo de filme
    char* sinopse; //sinopse de cada filme
} Filme;

typedef struct{
    Filme* filmes;
    int tamanho_atual;
    int capacidade;
} ArrayDeFilmes;

//declarando as funções da nossa biblioteca
void inicializar_array(ArrayDeFilmes* arr);
void adicionar_filme_ao_array(ArrayDeFilmes* arr, Filme filme);
void carregar_filmes(const char* nome_arquivo, ArrayDeFilmes* arr);
void liberar_array(ArrayDeFilmes* arr);
void adicionar_novo_filme(ArrayDeFilmes* arr);
void remover_filme(ArrayDeFilmes* arr);
void recomenda_aleatorio(const ArrayDeFilmes* arr);
void salvar_para_arquivo(const char* nome_arquivo, const ArrayDeFilmes* arr);
void buscar_filme(const ArrayDeFilmes* arr);
void listar_filmes(const ArrayDeFilmes* arr);
char* converter_string_para_lowercase(const char* str);

#endif // !STRUCT_FILME
