#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include "disco.h"
#include "arquivo.h"


void iniciarInterface(void);            // inicia fluxo do usuário
void exibirMenu(void);                  
void processarOpcao(int opcao, Disco **disco);
void encerrarInterface(Disco *disco);   // finaliza sistema

#endif
