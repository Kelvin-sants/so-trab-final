#ifndef _ALOCACAO_INDEXADA_H_
#define _ALOCACAO_INDEXADA_H_

#include "disco.h"
#include "arquivo.h"

/*
    Realiza a alocação indexada de um arquivo no disco.
    Parâmetros:
    - disco: ponteiro para a estrutura do disco
    - arquivo: ponteiro para a estrutura do arquivo
    
    Retorno:
    - TRUE  (1)  : alocação realizada com sucesso
    - FALSE (-1) : falha na alocação (disco inválido ou espaço insuficiente)
*/
int alocarIndexada(Disco *disco, Arquivo *arquivo);

#endif
