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
        /* le o rs e o rt, passa p ula, utiliza o funct armazenado em ulaop 
        p decidir qual operacao fazer e salva o valor resultante em rd
        */
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
            /*beq: subtrai rs - rt  se flag zero retorna vdd,
             pc é somado fazendo o jump incondicional
             addi: ula soma o rs com o imm e armazena no rt
             lw/sw: controlador1.c usa o result da ula como indice p endereco da memoria
             no lw busca o dado/valor no endereco e escreve no rt
             no sw pega o valor e escreve na mem dados . (ele verifica o limite que tinha sido usado no define)
            */
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
                printf("overflow I (PC=%d)\n", n);

            if (ins->opcode == addi) {
                escreve_registrador(state->registradores, ins->rt, saida_ula.resultado);

            } else if (ins->opcode == lw) {
 
                int endereco = saida_ula.resultado;
                if (state->mem_dados != NULL &&
                    endereco >= 0 && endereco < MEM_DADOS_TAM) {
                    escreve_registrador(state->registradores, ins->rt,
                                        state->mem_dados->dados[endereco]);
                } else {
                    printf("erro LW endereco invalido\n");
                }

            } else if (ins->opcode == sw) {

                int endereco = saida_ula.resultado;
                if (state->mem_dados != NULL &&
                    endereco >= 0 && endereco < MEM_DADOS_TAM) {
                    state->mem_dados->dados[endereco] =
                        (int8_t)le_registrador(state->registradores, ins->rt);
                } else {
                    printf("erro SW endereco invalido\n");
                }
            }
        }
        break;

    case j: 
    // altera pc p endereco fazendo um jump incondicional
        state->pc = (int)(ins->instrucao_bruta & 0xFF) - 1;
        break;

    default:
        break;
    }
}
