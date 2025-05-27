#ifndef STRUCT_FILME
#define STRUCT_FILME


typedef struct{
    float nota; //0.0 até 5.0
    char* nome; //nome do filme
    char* sinopse; //sinopse de cada filme
    char* tipo; //tipo de filme
    int dataLancamento; //data de lançamento
} Filme;

#endif // !STRUCT_FILME
