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

    /*
    int linhas = 1;
    do
    {
        char aventureiro = '\0', ultimo = '\0';
        while ((aventureiro = fgetc(Mem_ins))!= EOF)
        {
            if (aventureiro == '\n')
                linhas += 1;
            }
            if (aventureiro != EOF)
            ultimo = aventureiro;
            if(ultimo !=  '\n' && ultimo != '\0')
            linhas += 1;
        } while (0);
    */


    state = (typ_stt *) malloc(255 * sizeof(state));
    fseek(Mem_ins, 0, SEEK_SET);


    char buffer_linha[32]; //  buffer p ler a linha toda  ja com o \n

    for (int i = 0 ; i < 255; i++)
    {

        if (fgets(buffer_linha, sizeof(buffer_linha), Mem_ins) == NULL) break;

        uint16_t inst_bin = (uint16_t) strtol(buffer_linha, NULL, 2);
        state[i].instrucao_t.instrucao_bruta = inst_bin;


        state[i].instrucao_t.opcode = (inst_bin >> 12) & 0x0F;
        state[i].instrucao_t.rs     = (inst_bin >> 9)  & 0x07;
        state[i].instrucao_t.rt     = (inst_bin >> 6)  & 0x07;
        state[i].instrucao_t.rd     = (inst_bin >> 3)  & 0x07;
        state[i].instrucao_t.funct  =  inst_bin        & 0x07;
        state[i].instrucao_t.addr   =  inst_bin        & 0x7F;



        if (state[i].instrucao_t.opcode == 0) {
            state[i].instrucao_t.tipo = 1;
        } else if (state[i].instrucao_t.opcode == 4 || state[i].instrucao_t.opcode == 8 || state[i].instrucao_t.opcode == 11 || state[i].instrucao_t.opcode == 15) {
            state[i].instrucao_t.tipo = 2;
        } else if (state[i].instrucao_t.opcode == 2) {
            state[i].instrucao_t.tipo = 3;
        }

        printf("\n instrucao lida : %u / 0x%04X\n", inst_bin, inst_bin);
        printf("opcode: %i\nrs: %i | rt: %i | rd: %i\nfunct: %i | imediato: %i | addr: %i | tipo: %i\n",
               state[i].instrucao_t.opcode, state[i].instrucao_t.rs, state[i].instrucao_t.rt, state[i].instrucao_t.rd,
               state[i].instrucao_t.funct, state[i].instrucao_t.immediato, state[i].instrucao_t.addr, state[i].instrucao_t.tipo);
    }

    fclose(Mem_ins);
    return state;
}
