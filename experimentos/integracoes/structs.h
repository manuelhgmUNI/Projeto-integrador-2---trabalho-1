#ifndef STRUCTS_H
#define STRUCTS_H
#include <stdint.h>
#include <stdbool.h>

// tipo instrucao
enum tipos_de_instrucao {
    r = 1,
    i = 2,
    j = 3,
};


typedef struct str_instrucaoV2 {
    enum tipos_de_instrucao tipo;
    uint16_t instrucao_bruta;
    char total[18]; 

    uint16_t opcode;    // 15-12
    uint16_t rs;        // 11-9
    uint16_t rt;        // 8-6
    uint16_t rd;        // 5-3
    uint16_t funct;     // 2-0
    int16_t  immediato; // 5-0
    uint16_t addr;      // 6-0
} typ_ins;

//typedef p ser compativel com o nosso main
typedef typ_ins typ_instrucaoSep;

//registrador agora com int8_t e alterei para $ tbm
typedef struct str_regis {
    int8_t $[8];
} typ_reg;

/* ================ ULA ================ */
typedef enum {
    ADD = 0,
    SUB = 2,
    AND = 4,
    OR  = 5,
    SLT
} typ_ulaOp;

typedef struct {
    int resultado;
    int zero;
    int overflow; //sai 1 se a flag ativar
} typ_ulaR;

//coloquei aqui a mem dados do renan
#define MEM_DADOS_TAM 256
typedef struct {
    int8_t dados[MEM_DADOS_TAM];
} typ_mem_dados;

// estado
typedef struct str_state {
    typ_ins     *instrucao_t;
    typ_reg       *registradores;
    typ_mem_dados *mem_dados;   //ponteiro mem dados
    int pc;
    int pc_hist[256];           // pc_hist vai ser nossa pilha p pc
    int hist_topo;              //sinal da pilha
    bool sinal[8];
    typ_ulaOp ulaop;
} typ_stt;

//sinais 
enum {
    esc_mem = 0,
    esc_reg = 1,
    mem_reg = 2,
    ula_fon = 3,
    reg_des = 4,
    inc_pc  = 5,
    jump    = 6,
    branch  = 7,
};

//tipo i
enum tipo_i {
    addi = 4,
    beq  = 8,
    lw   = 11,
    sw   = 15,
};

#endif
