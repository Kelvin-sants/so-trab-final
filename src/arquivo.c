#define _ARQUIVO_C_
#include "arquivo.h"
#include "disco.h"
#include <stdlib.h>
#define TRUE 1
#define FALSE -1

Arquivo *criarArquivo(int id, int tamanho) {
    Arquivo *arquivo;
    
    if(tamanho > 0 && id > 0){
        // aloca memória para a estrutura Arquivo
        arquivo = (Arquivo *)malloc(sizeof(Arquivo));
        
        if(arquivo != NULL){
            arquivo->id = id;
            arquivo->tamanho = tamanho;
            arquivo->qtd_blocos = 0; 
            
            arquivo->blocos = (int *)malloc(sizeof(int) * tamanho);
            
            if(arquivo->blocos != NULL){
                // inicializa o vetor de blocos
                for(int i = 0; i < tamanho; i++){
                    arquivo->blocos[i] = BLOCO_LIVRE;
                }
                return arquivo;
            }
            free(arquivo);
        }
        return NULL;
    }
    return NULL;
}

void destruirArquivo(Arquivo *arquivo){
    if(arquivo != NULL){
        if(arquivo->blocos != NULL){
            free(arquivo->blocos);
            arquivo->blocos = NULL; 
        }
        free(arquivo);
    }
    return NULL;
}

int adiconarBlocoArquivo(Arquivo *arquivo, int indice_bloco){
    if (arquivo != NULL){
        if (arquivo->blocos != NULL && indice_bloco >= 0){
            // verifica se há espaço no vetor
            if (arquivo->qtd_blocos < arquivo->tamanho){
                arquivo->blocos[arquivo->qtd_blocos] = indice_bloco;
                arquivo->qtd_blocos++;

                return TRUE;
            }
            return FALSE;
        }
        return FALSE;
    }
    return FALSE;
}

int removerTodosBlocosArquivo(Arquivo *arquivo){
    if (arquivo != NULL){
        if(arquivo->blocos != NULL){
            // marcar blocos como não alocados e zera qtd
            for (int i = 0; i < arquivo->qtd_blocos; i++){
                arquivo->blocos[i] = BLOCO_LIVRE;
            }
            arquivo->qtd_blocos = 0;

            return TRUE;
        }
    }
    return FALSE;
}

int consultarIdArquivo(const Arquivo *arquivo) {
    if (arquivo != NULL) {
        return arquivo->id;
    }
    return FALSE;  // arquivo inválido (nota para localizar onde define validez do arquivo)
}

int consultarTamanhoArquivo(const Arquivo *arquivo) {
    if (arquivo != NULL) {
        return arquivo->tamanho;
    }
    return FALSE;
}

int consultarQtdBlocosArquivo(const Arquivo *arquivo) {
    if (arquivo != NULL) {
        return arquivo->qtd_blocos;
    }
    return FALSE; 
}

const int *consultarBlocosArquivo(const Arquivo *arquivo) {
    if (arquivo != NULL) {
        return arquivo->blocos;
    }
    return NULL;  
}

