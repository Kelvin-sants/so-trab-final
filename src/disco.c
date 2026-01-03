// OBJETIVO: Representar o disco; Inicializar os blocos; Liberar blocos; Funções utilitárias relacionadas ao estado do disco
#define _DISCO_C_
#include "disco.h"
#include "stdio.h"

// protótipos
Disco *criarDisco(int numBlocos); 
void destruirDisco(Disco *disco);
void reiniciarDisco(Disco *disco);                                  // reinicializa o disco, marcando todos os blocos como livres
int consultarTamanhoDisco(const Disco *disco);
int consultarBloco(const Disco *disco, int index);
int verificarBlocoLivre(const Disco *disco, int index);
int definirOcupado(const Disco *disco, int index, int id_arquivo);  // marca bloco como ocupado por um arquivo
int definirBlocoLivre(const Disco *disco, int index);               // marca bloco como livre
int contarBlocosLivres(const Disco *disco);                         // conta blocos livres
int verificarEspacoLivre(const Disco *disco, int n);                 // descobrir se disco possui n blocos livres
const int *visualizarBlocosDisco(const Disco *disco);                // função para visualizar os blocos do disc

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