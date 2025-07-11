#ifndef FUNCOES_FILME
#define FUNCOES_FILME

// Códigos de reset
#define RESET          "\033[0m"
#define RESET_BG       "\033[49m"
#define RESET_TEXT     "\033[39m"

// Códigos de cores de texto
#define RED            "\033[31m"
#define GREEN          "\033[32m"

// Códigos de cores de fundo
#define BG_BLUE        "\033[44m"

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


typedef void (*PtrFunc)(ArrayDeFilmes* arr);

typedef struct {
  char* descricao;
  PtrFunc executar;
} OpcaoMenu;

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

#endif // !FUNCOES_FILME
