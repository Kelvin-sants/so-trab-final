#define _ALOCACAO_CONTIGUA_C_
#include "arquivo.h"
#include "disco.h"
#include <stdlib.h>
#define TRUE 1
#define FALSE -1

int alocarArquivoContiguo(Disco *disco, Arquivo *arquivo) {
    int tamanho_arquivo;
    int tamanho_disco;
    int blocos_livres_consecutivos = 0;
    int inicio_bloco = -1;

    if (disco == NULL || arquivo == NULL) {
        return FALSE;
    }

    tamanho_arquivo = consultarTamanhoArquivo(arquivo);
    tamanho_disco = consultarTamanhoDisco(disco);

    for (int i = 0; i < tamanho_disco; i++) {
        if (verificarBlocoLivre(disco, i) == TRUE) {
            //se for o primeiro bloco livre encontrado
            if (blocos_livres_consecutivos == 0) {
                inicio_bloco = i;
            }

            blocos_livres_consecutivos++;

            if (blocos_livres_consecutivos == tamanho_arquivo) {
                for (int j = inicio_bloco; j < inicio_bloco + tamanho_arquivo; j++) {
                    definirBlocoOcupado(disco, j, consultarIdArquivo(arquivo));
                    adiconarBlocoArquivo(arquivo, j);       //talvez tire isso e só use esse vetor na Alocação indexada
                }
                //se conseguiu alocar todos os blocos necessários
                return TRUE;
            }
        } else {
            blocos_livres_consecutivos = 0;
            inicio_bloco = -1;
        }
    }
    
    //se não conseguiu alocar o arquivo
    return FALSE;
}