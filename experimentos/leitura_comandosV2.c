#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "structs.h"

typ_stt *decodificado_bit_bit(typ_stt *state)
{
    /*
    0000/000 => ADD => 0/0
    0000/010 => SUB => 0/2
    0000/100 => AND => 0/4
    0000/101 => OR => 0/5
    0100 => AADi => 4
    1011 => LW => 11
    1111 => SW => 15
    1000 => BEQ => 8
    0010 => J => 2
    */

    FILE *Mem_ins = fopen("memoria1.mem", "r"); //so adicionei um tratamento de erro pra caso o arquivo nao abra
    if (Mem_ins == NULL) {
        printf("erro ao abrir o arquivo memoria1.mem\n");
        return NULL;
    }

    state->registradores = (typ_reg *) malloc(255 * sizeof(typ_reg));
    state->instrucao_t = (typ_ins_t *) malloc(255 * sizeof(typ_ins_t));
    fseek(Mem_ins, 0, SEEK_SET);


    char buffer_linha[32]; //  buffer p ler a linha toda  ja com o \n

    for (int i = 0 ; i < 255; i++)
    {

        if (fgets(buffer_linha, sizeof(buffer_linha), Mem_ins) == NULL) break;

        uint16_t inst_bin = (uint16_t) strtol(buffer_linha, NULL, 2);
        state->instrucao_t[i].instrucao_bruta = inst_bin;


        state->instrucao_t[i].opcode = (inst_bin >> 12) & 0x0F;
        state->instrucao_t[i].rs     = (inst_bin >> 9)  & 0x07;
        state->instrucao_t[i].rt     = (inst_bin >> 6)  & 0x07;
        state->instrucao_t[i].rd     = (inst_bin >> 3)  & 0x07;
        state->instrucao_t[i].funct  =  inst_bin        & 0x07;
        state->instrucao_t[i].addr   =  inst_bin        & 0x7F;



        if (state->instrucao_t[i].opcode == 0) {
            state->instrucao_t[i].tipo = 1;
        } else if (state->instrucao_t[i].opcode == 4 || state->instrucao_t[i].opcode == 8 || state->instrucao_t[i].opcode == 11 || state->instrucao_t[i].opcode == 15) {
            state->instrucao_t[i].tipo = 2;
        } else if (state->instrucao_t[i].opcode == 2) {
            state->instrucao_t[i].tipo = 3;
        }

        printf("\n instrucao lida : %u / 0x%04X\n", inst_bin, inst_bin);
        printf("opcode: %i\nrs: %i | rt: %i | rd: %i\nfunct: %i | imediato: %i | addr: %i | tipo: %i\n",
               state->instrucao_t[i].opcode, state->instrucao_t[i].rs, state->instrucao_t[i].rt, state->instrucao_t[i].rd,
               state->instrucao_t[i].funct, state->instrucao_t[i].immediato, state->instrucao_t[i].addr, state->instrucao_t[i].tipo);
    }

    fclose(Mem_ins);
    return state;
}
