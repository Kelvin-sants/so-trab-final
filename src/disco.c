// OBJETIVO: Representar o disco; Inicializar os blocos; Liberar blocos; Funções utilitárias relacionadas ao estado do disco
#define _DISCO_C_
#include "disco.h"
#include "stdio.h"
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
            disco->blocos = (int*)malloc(sizeof(int)*numBlocos);

            if(disco->blocos != NULL){
                disco->tamanho = numBlocos;
                for (i = 0; i < numBlocos; i++){
                    disco -> blocos[i] = BLOCO_LIVRE;
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
    return NULL;
}

void reiniciarDisco(Disco *disco) {
    int i;

    if (disco != NULL) {
        if (disco->blocos != NULL) {
            for (i = 0; i < (disco->tamanho); i++) {
                disco->blocos[i] = BLOCO_LIVRE;
            }
        }
        return NULL;
    }
    return NULL;
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
                return disco->blocos[index];
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
                if (disco->blocos[index] == BLOCO_LIVRE) {
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
                disco->blocos[index] = id_arquivo;
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
                disco->blocos[index] = BLOCO_LIVRE;
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
                if (disco->blocos[i] == BLOCO_LIVRE) {
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

const int *visualizarBlocosDisco(const Disco *disco) { // Retorna apenas uma visão do disco
    if (disco != NULL) {
        if (disco->blocos != NULL) {
            return disco->blocos;
        }
    }
    return NULL;
}