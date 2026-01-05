#define _ALOCACAO_ENCADEADA_C_
#include "include/arquivo.h"
#include "include/disco.h"
#include <stdlib.h>
#define TRUE 1
#define FALSE -1

int alocarEncadeada(Disco *disco, Arquivo *arquivo) {
    int tamanho_arquivo;
    int tamanho_disco;
    int blocos_livres_encontrados = 0;
    int bloco_anterior = -1;

    if (disco == NULL || arquivo == NULL) {
        return FALSE;
    }

    tamanho_arquivo = consultarTamanhoArquivo(arquivo);
    tamanho_disco = consultarTamanhoDisco(disco);

    for (int i = 0; i < tamanho_disco && blocos_livres_encontrados < tamanho_arquivo; i++) {
        if (verificarBlocoLivre(disco, i) == TRUE) {
            definirBlocoOcupado(disco, i, consultarIdArquivo(arquivo));
            if (bloco_anterior != -1) {
                definirProximoBloco(disco, bloco_anterior, i);
            }
            bloco_anterior = i;
            blocos_livres_encontrados++;
        }
    }

    if (blocos_livres_encontrados == tamanho_arquivo) {
        return TRUE; // sucesso na alocação
    } else {
        // desfaz a alocação parcial em caso de falha
        for (int i = 0; i < tamanho_disco; i++) {
            if (consultarValorBloco(disco, i) == consultarIdArquivo(arquivo)) {
                definirBlocoLivre(disco, i);
            }
        }
        return FALSE; // falha na alocação
    }
}