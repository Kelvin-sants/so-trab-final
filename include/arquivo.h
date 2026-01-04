#ifndef _ARQUIVO_H_
#define _ARQUIVO_H_

#ifdef _ARQUIVO_C_

/* Estrutura interna do arquivo */
typedef struct _arquivo_ {
    int id;             // identificador do arquivo
    int tamanho;        // tamanho solicitado (em blocos)
    int qtd_blocos;     // quantidade de blocos alocados
    int *blocos;        // vetor com os índices dos blocos ocupados
} Arquivo;

#else
typedef struct _arquivo_ Arquivo;
#endif

// criação e destruição
Arquivo *criarArquivo(int id, int tamanho);
void destruirArquivo(Arquivo *arquivo);

// funções de manipulação
int adicionarBlocoArquivo(Arquivo *arquivo, int indice_bloco);
int removerTodosBlocosArquivo(Arquivo *arquivo);

// funções de consulta
int consultarIdArquivo(const Arquivo *arquivo);
int consultarTamanhoArquivo(const Arquivo *arquivo);
int consultarQtdBlocosArquivo(const Arquivo *arquivo);
const int *consultarBlocosArquivo(const Arquivo *arquivo);

#endif
