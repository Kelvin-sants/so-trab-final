#ifndef _DISCO_H_
#define _DISCO_H_

// Constantes globais
#define BLOCO_LIVRE -1
#define ERRO_DISCO -2

#ifdef _DISCO_C_

// Estrutura do disco
typedef struct _disco_ {
    int tamanho;       // número total de blocos
    int *blocos;       // vetor de blocos
} Disco;

#else
typedef struct _disco_ Disco;
#endif

// Funções
Disco *criarDisco(int size); 
void destruirDisco(Disco *disco);
void reinicializarDisco(Disco *disco);                                  // reinicializa o disco, marcando todos os blocos como livres
int consultarTamanhoDisco(const Disco *disco);
int consultarValorBloco(const Disco *disco, int index);
int verificarBlocoLivre(const Disco *disco, int index);
int definirOcupado(const Disco *disco, int index, int id_arquivo);  // marca bloco como ocupado por um arquivo
int definirBlocoLivre(const Disco *disco, int index);               // marca bloco como livre
int contarBlocosLivres(const Disco *disco);                         // conta blocos livres
int verificarEspacoLivre(const Disco *disco, int n);                 // descobrir se disco possui n blocos livres
const int *visualizarBlocosDisco(const Disco *disco);                // função para visualizar os blocos do disco

#endif
