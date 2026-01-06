// OBJETIVO: Representar o disco; Inicializar os blocos; Liberar blocos; Funções utilitárias relacionadas ao estado do disco
#define _DISCO_C_
#include "disco.h"
#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

Disco *criarDisco(int numBlocos){
    Disco *disco;
    int i;

    if(numBlocos > 0){
        // alocação da estrutura do disco
        disco = (Disco *)malloc(sizeof(Disco));     

        if(disco != NULL){

            // alocação do vetor de blocos
            disco->blocos = (Bloco*)malloc(sizeof(Bloco)*numBlocos);

            if(disco->blocos != NULL){
                disco->tamanho = numBlocos;
                for (i = 0; i < numBlocos; i++){
                    disco->blocos[i].dado = BLOCO_LIVRE;
                    disco->blocos[i].proximo = -1;
                }
                
                return disco;
            }
            free(disco); // Libera estrutura em caso de erro
        }
        return NULL;
    }
    return NULL;
}

void destruirDisco(Disco *disco){
    if(disco != NULL){
        if(disco->blocos != NULL){
            free(disco->blocos);
        }
        free(disco);
    }
    return;
}

void reinicializarDisco(Disco *disco) {
    int i;

    if (disco != NULL) {
        if (disco->blocos != NULL) {
            for (i = 0; i < (disco->tamanho); i++) {
                disco->blocos[i].dado = BLOCO_LIVRE;
                disco->blocos[i].proximo = -1;
            }
        }
        return;
    }
    return;
}

int consultarTamanhoDisco(const Disco *disco) {
    if (disco != NULL) {
        return disco->tamanho;
    }
    return ERRO_DISCO;
}

int consultarValorBloco(const Disco *disco, int index) {
    if (disco != NULL) {
        if (disco->blocos != NULL) {
            if (index >= 0 && index < disco->tamanho) {
                return disco->blocos[index].dado;
            }
        }
        return ERRO_DISCO;
    }
    return ERRO_DISCO;
}

int verificarBlocoLivre(const Disco *disco, int index) {
    if (disco != NULL) {
        if (disco->blocos != NULL) {
            if (index >= 0 && index < disco->tamanho) {
                if (disco->blocos[index].dado == BLOCO_LIVRE) {
                    return TRUE;
                } else {
                    return FALSE;
                }
            }
        }
        return ERRO_DISCO;
    }
    return ERRO_DISCO;
}

int definirBlocoOcupado(const Disco *disco, int index, int id_arquivo) {
    if (disco != NULL) {
        if (disco->blocos != NULL) {
            if (index >= 0 && index < disco->tamanho) {
                disco->blocos[index].dado = id_arquivo;
                return TRUE;
            }
            return FALSE;
        }
        return ERRO_DISCO;
    }
    return ERRO_DISCO;
}

int definirBlocoLivre(const Disco *disco, int index) {
    if (disco != NULL) {
        if (disco->blocos != NULL) {
            if (index >= 0 && index < disco->tamanho) {
                disco->blocos[index].dado = BLOCO_LIVRE;
                disco->blocos[index].proximo = -1;
                return TRUE;
            }
            return FALSE;
        }
        return ERRO_DISCO;
    }
    return ERRO_DISCO;
}

int contarBlocosLivres(const Disco *disco) {
    int i;
    int contador = 0;

    if (disco != NULL) {
        if (disco->blocos != NULL) {
            for (i = 0; i < disco->tamanho; i++) {
                if (disco->blocos[i].dado == BLOCO_LIVRE) {
                    contador++;
                }
            }
            return contador;
        }
        return ERRO_DISCO;
    }
    return ERRO_DISCO;
}

int verificarEspacoLivre(const Disco *disco, int n) {
    int livres;

    if (disco != NULL) {
        if (n >= 0) {
            livres = contarBlocosLivres(disco);
            if (livres != ERRO_DISCO) {
                if (livres >= n) {
                    return TRUE;
                } else {
                    return FALSE;
                }
            }
        }
    }
    return ERRO_DISCO;
}

const Bloco *visualizarBlocosDisco(const Disco *disco) { // Retorna apenas uma visão do disco
    if (disco != NULL) {
        if (disco->blocos != NULL) {
            return disco->blocos;
        }
    }
    return NULL;
}

int definirProximoBloco(const Disco *disco, int index_atual, int index_proximo){
    if (disco != NULL) {
        if (disco->blocos != NULL) {
            if (index_atual >= 0 && index_atual < disco->tamanho &&
                index_proximo >= 0 && index_proximo < disco->tamanho) {
                disco->blocos[index_atual].proximo = index_proximo;
                return TRUE;
            }
            return FALSE;
        }
        return ERRO_DISCO;
    }
    return ERRO_DISCO;
}

int removerProximoBloco(const Disco *disco, int index_atual){
    if (disco != NULL) {
        if (disco->blocos != NULL) {
            if (index_atual >= 0 && index_atual < disco->tamanho) {
                disco->blocos[index_atual].proximo = -1;
                return TRUE;
            }
            return FALSE;
        }
        return ERRO_DISCO;
    }
    return ERRO_DISCO;
}