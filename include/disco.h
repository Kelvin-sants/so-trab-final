#ifndef _DISCO_H_
#define _DISCO_H_

#ifdef _DISCO_C_
// Constantes globais
#define BLOCO_LIVRE -1
#define ERRO_DISCO -2

// Estrutura do disco
typedef struct _disco_ {
    int tamanho;       // número total de blocos
    int *blocos;       // vetor de blocos
} Disco;

#else
typedef struct _disco_ Disco;
#endif

// Funções
Disco *disk_create(int size); 
void disk_destroy(Disco *disk);
void disk_reset(Disco *disk);                                    // reinicializa o disco, marcando todos os blocos como livres
int disk_get_size(const Disco *disk);
int disk_get_block(const Disco *disk, int index);
int disk_is_block_free(const Disco *disk, int index);
int disk_set_block(const Disco *disk, int index, int file_id);   // marca bloco como ocupado por um arquivo
int disk_free_block(const Disco *disk, int index);               // marca bloco como livre
int disk_count_free_blocks(const Disco *disk);                   // conta blocos livres
int disk_has_free_space(const Disco *disk, int n);               // descobrir se disco possui n blocos livres
const int *disk_get_blocks(const Disco *disk);                   // função para visualizar os blocos do disco

#endif
