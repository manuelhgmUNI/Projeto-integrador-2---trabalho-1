#include <stdio.h>
#include "funcoes.h"
#include "structs.h"


int executar(typ_stt *status, typ_reg reg, bool clear_data)
{
    int val_write;

    if (status == NULL || status->instrucao_t == NULL || status->registradores == NULL || status->mem_dados == NULL) {
        fprintf(stderr, "errro\n");
        return -1;
    }//tratamento de erro  pq tava dando segmentation fault

    if (status->pc < 0 || status->pc >= 256) {
        fprintf(stderr, "erro!\n");
        return -1;
    }//ver se o pc tem um valor valido

    //stats mas n testei ainda, pra deixar mais didatico como o julio pediu
    status->total_instrucoes++;
    switch (status->instrucao_t[status->pc].tipo) {
        case r: status->r_instrucoes++; break;
        case i: status->i_instrucoes++; break;
        case j: status->j_instrucoes++; break;
        default: break;
    }

    controlador(status, status->pc);

    int valor_a = status->registradores->$[status->instrucao_t[status->pc].rs];
    int valor_b = status->sinal[ula_fon] == 0
                        ? status->registradores->$[status->instrucao_t[status->pc].rt]
                        : status->instrucao_t[status->pc].immediato; //mux rt ou imm

    status->ular = ula(valor_a, valor_b, status->ulaop);

    unsigned int endereco_mem = (uint8_t)status->ular.resultado; 
    int8_t saida_mem = mem_data(status->mem_dados,
                               endereco_mem,
                               status->registradores->$[status->instrucao_t[status->pc].rt],
                               status->sinal[esc_mem],
                               status->sinal[mem_reg],
                               clear_data);

    if (status->sinal[esc_reg]) {
        val_write = status->sinal[mem_reg] ? saida_mem : status->ular.resultado;
        if (status->sinal[reg_des])
            status->registradores->$[status->instrucao_t[status->pc].rd] = (int8_t)val_write;
        else
            status->registradores->$[status->instrucao_t[status->pc].rt] = (int8_t)val_write;
    }

    //incremento do pc so no final e usando como o base o pc atual
    int pc_antigo = status->pc;
    if (status->sinal[inc_pc]) {
        status->pc = pc_antigo + 1;
        if (status->sinal[jump]) {
            status->pc = status->instrucao_t[pc_antigo].addr;
        } else if (status->sinal[branch] && status->ular.zero) //a gente precisa do sub no beq pra verificar se é zero
        {
            status->pc = pc_antigo + 1 + status->instrucao_t[pc_antigo].immediato;
        }
    }

    return 0;
}