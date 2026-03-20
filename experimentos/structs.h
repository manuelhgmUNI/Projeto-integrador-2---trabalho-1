#include<stdio.h>

#ifndef structs_H
#define structs_H

    enum tipos_de_instrução
    {
        r = 1,
        i = 2,
        j = 3,

    };

    typedef struct str_instrucao
    {
        enum tipos_de_instrução tipo;
        char total[17];
        int opcode; // 0-3
        int rs; // 4-6
        int rt; // 7-9
        int rd; // 10-12
        int funct; // 13-15
        int immediato; // 10-15
        int addr; //endereço do jump
    }typ_ins;

    typedef struct str_regis
    {
        /* registradores */
    }typ_reg;
    

    struct state
    {
        typ_ins instrucao;
        typ_reg registradores;
        int pc;

    };
    


#endif