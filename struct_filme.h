#ifndef STRUCT_FILME
#define STRUCT_FILME


typedef struct{
    char* nome; 
    int dataLancamento; 
    float nota; 
    char* tipo; 
    char* sinopse; 
} Filme;

typedef struct{
    Filme* filmes;
    int tamanho_atual;
    int capacidade;
} ArrayDeFilmes;

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
void imprime_filmes(const ArrayDeFilmes* arr);

#endif // !STRUCT_FILME
