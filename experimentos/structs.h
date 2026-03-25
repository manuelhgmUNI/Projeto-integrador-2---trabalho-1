#include <stdint.h>
#include <stdbool.h>
#ifndef structs_H
#define structs_H

    enum tipos_de_instrucao
    {
        r = 1,
        i = 2,
        j = 3,

    };

    typedef struct str_instrucao
    {
        enum tipos_de_instrucao tipo;
        char total[17];
        int opcode; // 0-3
        int rs; // 4-6
        int rt; // 7-9
        int rd; // 10-12
        int funct; // 13-15
        int immediato; // 10-15
        int addr; //endereço do jump
    }typ_ins_m;

    typedef struct str_instrucaoV2
    {
        enum tipos_de_instrucao tipo;
        uint16_t instrucao_bruta; //unsigned int 16 bits para instrução
        char total_string[18];

        uint16_t opcode;    // 15-12  (4 bits)
        uint16_t rs;        // 11-9  (3 bits)
        uint16_t rt;        // 8-6  (3 bits)
        uint16_t rd;        // 5-3 (3 bits)
        uint16_t funct;     // 2-0 (3 bits)
        int16_t  immediato; // 5-0 (6 bits) - int com sinal p aceita negativos
        uint16_t addr;      // 6-0 (7 bits)
    }typ_ins_t;

    typedef struct str_regis
    {
        int8_t $[8];
    }typ_reg;

    typedef struct str_state
    {
        //typ_ins_m instrucao_m;
        typ_ins_t *instrucao_t;
        typ_reg *registradores;
        int pc;
        bool sinal[8];
    }typ_stt;
    enum
    {
        esc_mem = 0, // escrita na memoria
        esc_reg = 1, // escrita no registrador
        mem_reg = 2, // memoria para registrador
        ula_fon = 3, // fonte da ula (registrador ou imediato)
        reg_des = 4, // registrador de destino
        inc_pc  = 5, // sinal de incremento do pc
        jump    = 6, // sinal do jump

    };
    enum tipo_i
    {
        addi = 3,
        beq  = 8,
        lw   = 11,
        sw   = 15,
    };

    /* ================ ULA ================ */
    typedef enum {
        ADD = 0,    // 0
        SUB = 2,    // 2
        AND = 4,    // 4
        OR  = 5,    // 5
        SLT     // 4
    }typ_ulaOp;

    typedef struct {
        int resultado;  // Resultado da operação
        int zero;       // flag de 0 ou 1
    }typ_ulaR;


#endif