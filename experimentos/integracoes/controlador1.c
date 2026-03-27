#include <stdio.h>
#include "structs.h"
#include "funcoes.h"
#include "registradores.h" // para poder usar le_registrador() e escreve_registrador() 

void controlador(typ_stt *state, int n)
{
    typ_ins_t *ins = &state->instrucao_t[n];

    typ_ulaR  saida_ula;
    typ_ulaOp ulaop;

    switch (ins->tipo)
    {
    case r: //Tipo R 
        ulaop     = (typ_ulaOp)ins->funct;
        saida_ula = ula(le_registrador(state->registradores, ins->rs),
                        le_registrador(state->registradores, ins->rt),
                        ulaop);

        if (saida_ula.overflow)
            printf(" overflow na instrucao R (PC=%d)\n", n);

        escreve_registrador(state->registradores, ins->rd, saida_ula.resultado);
        break;

    case i: // Tipo I 
        if (ins->opcode == beq) {
            //beq: subtrai rs - rt  se zero desvia.
            ulaop     = SUB;
            saida_ula = ula(le_registrador(state->registradores, ins->rs),
                            le_registrador(state->registradores, ins->rt),
                            ulaop);

            if (saida_ula.zero)
                state->pc += ins->immediato; 

        } else {
            ulaop     = ADD;
            int val_rs = le_registrador(state->registradores, ins->rs);
            saida_ula  = ula(val_rs, ins->immediato, ulaop);

            if (saida_ula.overflow)
                printf("[AVISO] Overflow na instrucao I (PC=%d)\n", n);

            if (ins->opcode == addi) {
                escreve_registrador(state->registradores, ins->rt, saida_ula.resultado);

            } else if (ins->opcode == lw) {
 
                int endereco = saida_ula.resultado;
                if (state->mem_dados != NULL &&
                    endereco >= 0 && endereco < MEM_DADOS_TAM) {
                    escreve_registrador(state->registradores, ins->rt,
                                        state->mem_dados->dados[endereco]);
                } else {
                    printf("[ERRO] LW: endereco %d invalido\n", endereco);
                }

            } else if (ins->opcode == sw) {

                int endereco = saida_ula.resultado;
                if (state->mem_dados != NULL &&
                    endereco >= 0 && endereco < MEM_DADOS_TAM) {
                    state->mem_dados->dados[endereco] =
                        (int8_t)le_registrador(state->registradores, ins->rt);
                } else {
                    printf("[ERRO] SW: endereco %d invalido\n", endereco);
                }
            }
        }
        break;

    case j: 
        state->pc = (int)(ins->instrucao_bruta & 0xFF) - 1;
        break;

    default:
        break;
    }
}
