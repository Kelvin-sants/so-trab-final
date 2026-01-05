#ifndef _ALOCACAO_ENCADEADA_H_
#define _ALOCACAO_ENCADEADA_H_

#include "disco.h"
#include "arquivo.h"

/*
    Realiza a alocação encadeada de um arquivo no disco.
    
    Parâmetros:
    - disco: ponteiro para a estrutura do disco
    - arquivo: ponteiro para a estrutura do arquivo
    
    Retorno:
    - TRUE  (1)  : alocação realizada com sucesso
    - FALSE (-1) : falha na alocação (disco inválido ou espaço insuficiente)
*/
int alocarEncadeada(Disco *disco, Arquivo *arquivo);

#endif
