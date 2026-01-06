#define _ALOCACAO_INDEXADA_C_
#include "arquivo.h"
#include "disco.h"
#include <stdlib.h>
#define TRUE 1
#define FALSE -1

int alocarIndexada(Disco *disco, Arquivo *arquivo) {
    int tamanho_arquivo;
    int tamanho_disco;
    int blocos_livres_encontrados = 0;

    if (disco == NULL || arquivo == NULL) {
        return FALSE;
    }

    tamanho_arquivo = consultarTamanhoArquivo(arquivo);
    tamanho_disco = consultarTamanhoDisco(disco);

    for (int i = 0; i < tamanho_disco && blocos_livres_encontrados < tamanho_arquivo; i++) {
        if (verificarBlocoLivre(disco, i) == TRUE) {
            definirBlocoOcupado(disco, i, consultarIdArquivo(arquivo));
            adicionarBlocoArquivo(arquivo, i);        //talvez tire isso e só use esse vetor na Alocação indexada
            blocos_livres_encontrados++;
        }
    }

    if (blocos_livres_encontrados == tamanho_arquivo) {
        return TRUE; // sucesso na alocação
    } else {
        // desfaz a alocação parcial em caso de falha
        removerTodosBlocosArquivo(arquivo);
        for (int i = 0; i < tamanho_disco; i++) {
            if (consultarValorBloco(disco, i) == consultarIdArquivo(arquivo)) {
                definirBlocoLivre(disco, i);
            }
        }
        return FALSE; // falha na alocação
    }
}