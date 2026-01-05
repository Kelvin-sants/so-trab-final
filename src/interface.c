#define _INTERFACE_C_

#include <stdio.h>
#include <stdlib.h>

#include "include/interface.h"
#include "include/disco.h"
#include "include/arquivo.h"
#include "include/alocacao_contigua.h"
#include "include/alocacao_encadeada.h"
#include "include/alocacao_indexada.h"

#define TRUE 1
#define FALSE -1

// protótipo das funções internas do arquivo, auxiliares das funções principais

static Arquivo *buscarArquivoPorId(Arquivo **arquivos, int quantidade, int id);
static void listarArquivos(Arquivo **arquivos, int quantidade);
static void imprimirDisco(const Disco *disco);

// interface

void exibirMenu(void) {
    printf("\n ----------[ SIMULADOR DE ALOCACAO DE ARQUIVOS ]---------- \n");

    printf("[ 1 ] - Criar disco\n");
    printf("[ 2 ] - Reiniciar disco\n");
    printf("[ 3 ] - Visualizar disco\n\n");

    printf("[ 4 ] - Criar arquivo\n");
    printf("[ 5 ] - Listar arquivos\n\n");

    printf("[ 6 ] - Realizar alocação contigua \n");
    printf("[ 7 ] - Realizar alocação encadeada \n");
    printf("[ 8 ] - Realizar alocação indexada \n\n");
    printf("[ 9 ] - Remover um arquivo \n\n");

    printf("[ 0 ] - Sair\n");

    printf("Escolha uma opcao para proseguir: ");
}

void iniciarInterface(void) {

    Disco *disco = NULL;        // dico
    Arquivo **arquivos = NULL;  // vetor de ponteiros para arquivos
    int qtd_arquivos = 0;
    int capacidade = 0;
    int opcao = -1;          

    while (opcao != 0) {

        exibirMenu();
        scanf("%d", &opcao);

        // processar opção

        if (opcao == 1) {               // criar disco
            int tamanho;

            if (disco != NULL) {
                destruirDisco(disco);
                disco = NULL;
            }

            printf("Informe o tamanho do disco: ");
            scanf("%d", &tamanho);

            disco = criarDisco(tamanho);
            
            if (disco != NULL) {
                printf("Disco criado! \n");
            } else {
                printf("Erro ao criar disco.\n");
            }

        } else if (opcao == 2) {        // reiniciar disco

            if (disco != NULL) {
                reinicializarDisco(disco);
                printf("Disco reiniciado.\n");
            } else {
                printf("Disco inexistente.\n");
            }

        } else if (opcao == 3) {        // visualizar disco
            if (disco != NULL) {
                imprimirDisco(disco);
            } else {
                printf("Disco inexistente.\n");
            }

        } else if (opcao == 4) {        // criar arquivo
            int id, tamanho;
            Arquivo *novo_arquivo;

            printf("Insira o ID do arquivo: ");
            scanf("%d", &id);

            if (buscarArquivoPorId(arquivos, qtd_arquivos, id) != NULL) {
                printf("Arquivo com esse ID ja existe.\n");
            } else {
                printf("Informe o tamanho do arquivo: ");
                scanf("%d", &tamanho);

                novo_arquivo = criarArquivo(id, tamanho);
                if (novo_arquivo != NULL) {
                    if (qtd_arquivos == capacidade) {
                        // se for primeiro arquivo cria capacidade = 4, senão a capacidade dobra
                        if (capacidade == 0) {
                            capacidade = 4;                 
                        } else {
                            capacidade = capacidade * 2;    // dobra a capacidade
                        }
                        
                        arquivos = realloc(arquivos, capacidade * sizeof(Arquivo *));
                    }
                    
                    arquivos[qtd_arquivos] = novo_arquivo;
                    qtd_arquivos++;
                    printf("Arquivo criado!\n");

                } else {
                    printf("Erro ao criar arquivo.\n");
                }
            }

        } else if (opcao == 5) {                        // listar arquivos
            listarArquivos(arquivos, qtd_arquivos);

        } else if (opcao >= 6 && opcao <= 8) {          // alocações
            int id;
            Arquivo *arquivo;

            if (disco == NULL) {
                printf("Disco inexistente.\n");

            } else {

                printf("Informe o ID do arquivo: ");
                scanf("%d", &id);
                arquivo = buscarArquivoPorId(arquivos, qtd_arquivos, id);

                if (arquivo == NULL) {
                    printf("Arquivo nao encontrado.\n");

                } else {

                    int resultado = FALSE;

                    if (opcao == 6) {
                        resultado = alocarArquivoContiguo(disco, arquivo);
                    } else if (opcao == 7) {
                        resultado = alocarEncadeada(disco, arquivo);
                    } else if (opcao == 8) {
                        resultado = alocarIndexada(disco, arquivo);
                    }

                    if (resultado == TRUE) {
                        printf("Arquivo alocado com sucesso.\n");
                    } else {
                        printf("Falha na alocacao do arquivo.\n");
                    }
                }
            }
        } else if (opcao == 9) {            // remover um arquivo
            
            int id;
            int i, j;
            Arquivo *arquivo;

            if (disco == NULL) {
                printf("O disco não existe.\n");
            } else {
                printf("Informe o ID do arquivo que deseja remover: ");
                scanf("%d", &id);

                arquivo = buscarArquivoPorId(arquivos, qtd_arquivos, id);

                if (arquivo == NULL) {
                    printf("Arquivo nao encontrado.\n");
                } else {
                    // Libera os blocos ocupados pelo arquivo no disco
                    for (i = 0; i < consultarTamanhoDisco(disco); i++) {
                        if (consultarBloco(disco, i) == id) {
                            definirBlocoLivre(disco, i);
                        }
                    }

                    // remove o arquivo do vetor 
                    for (i = 0; i < qtd_arquivos; i++) {
                        if (arquivos[i] != NULL) {
                            if (consultarIdArquivo(arquivos[i]) == id) {
                                destruirArquivo(arquivos[i]);

                                /* Desloca os elementos para manter o vetor compacto */
                                for (j = i; j < qtd_arquivos - 1; j++) {
                                    arquivos[j] = arquivos[j + 1];
                                }
                                arquivos[qtd_arquivos - 1] = NULL;
                                qtd_arquivos--;
                                break;
                            }
                        }
                    }

                    printf("O arquivo foi removido com sucesso.\n");
                }
            }


        } else if (opcao == 0) {            // encerramento
            printf("Encerrando o sistema...\n");

        } else {                              // opção errada
            printf("Opcao invalida.\n");
        }
        
    }

    // liberar memória
    if (arquivos != NULL) {
        for (int i = 0; i < qtd_arquivos; i++) {
            if (arquivos[i] != NULL) {
                destruirArquivo(arquivos[i]);
            }
        }
        free(arquivos);
    }

    if (disco != NULL) {
        destruirDisco(disco);
    }
}

// implementação das funções auxiliares
static Arquivo *buscarArquivoPorId(Arquivo **arquivos, int quantidade, int id) {
    int i;
    if (arquivos != NULL) {
        for (i = 0; i < quantidade; i++) {
            if (arquivos[i] != NULL) {
                if (consultarIdArquivo(arquivos[i]) == id) {
                    return arquivos[i];
                }
            }
            return NULL;
        }
    }
    return NULL;
}
static void listarArquivos(Arquivo **arquivos, int quantidade) {
    int i;
    if (arquivos != NULL) {
        if (quantidade == 0) {
            printf("Não há arquivo cadastrado.\n");
        } else {
            printf("Lista de arquivos cadastrados:\n");
            for (i = 0; i < quantidade; i++) {
                if (arquivos[i] != NULL) {
                    printf("ID: %d - Tamanho: %d blocos\n", consultarIdArquivo(arquivos[i]), consultarTamanhoArquivo(arquivos[i]));
                }
            }
        }
    }
    return NULL;
}
static void imprimirDisco(const Disco *disco) {
    int i;
    const int *blocos;      // vetor de blocos

    if (disco != NULL) {
        blocos = visualizarBlocosDisco(disco);
        if (blocos != NULL) {
            printf("Disco:\n");
            for (i = 0; i < consultarTamanhoDisco(disco); i++) {
                if (blocos[i] == -1) {
                    printf("[ _ ] ");
                } else {
                    printf("[ %d ] ", blocos[i]);
                }
            }
            printf("\n");
        }
        return NULL;
    }
    return NULL;
}

