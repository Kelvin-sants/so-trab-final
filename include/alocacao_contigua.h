#ifndef _ALOCACAO_CONTIGUA_H_
#define _ALOCACAO_CONTIGUA_H_

#include "disco.h"
#include "arquivo.h"

/*
    Realiza a alocação contígua de um arquivo no disco.

    Parâmetros:
     - disco: ponteiro para a estrutura do disco
     - arquivo: ponteiro para a estrutura do arquivo

    Retorno:
     - TRUE  (1)  : alocação realizada com sucesso
     - FALSE (-1) : falha na alocação (disco inválido ou ausência de espaço contíguo)
*/
int alocarArquivoContiguo(Disco *disco, Arquivo *arquivo);

#endif
