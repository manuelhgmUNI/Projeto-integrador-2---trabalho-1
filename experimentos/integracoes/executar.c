// arquivo: executar.c
#include <stdio.h>
#include "structs.h"
#include "funcoes.h"
#include "registradores.h"

void executarCiclo(typ_stt *state, int n)
{
    typ_ins *ins = &state->instrucao_t[n];

    
    controlador(state, n);

    
    int val_rs = le_registrador(state->registradores, ins->rs);
    int val_rt = le_registrador(state->registradores, ins->rt);

    //calcul endereco
    //mux ula, 1 usa imm, 0 usa rt
    int ula_in2 = state->sinal[ula_fon] ? ins->immediato : val_rt;
    typ_ulaR saida_ula = ula(val_rs, ula_in2, state->ulaop);

    
    int dado_memoria = 0;
    int endereco = saida_ula.resultado;

    if (state->sinal[esc_mem]) { //sw
        if (state->mem_dados != NULL && endereco >= 0 && endereco < MEM_DADOS_TAM) {
            state->mem_dados->dados[endereco] = (int8_t)val_rt;
        } else {
            printf("erro\n");
        }
    }

    // lw tem mem_reg = 0 e esc_reg = 1
    if (state->sinal[esc_reg] == 1 && state->sinal[mem_reg] == 0) { 
        if (state->mem_dados != NULL && endereco >= 0 && endereco < MEM_DADOS_TAM) {
            dado_memoria = state->mem_dados->dados[endereco];
        } else {
            printf("erro\n");
        }
    }

    // escrita banc registrador
    if (state->sinal[esc_reg]) {
        // destino, reg destino 1 salva rd, se 0 salva rt
        int reg_destino = state->sinal[reg_des] ? ins->rd : ins->rt;
        
        // mem_reg for 1 vem da ula, se 0, vem da memoria
        int dado_escrita = state->sinal[mem_reg] ? saida_ula.resultado : dado_memoria;
        
        escreve_registrador(state->registradores, reg_destino, dado_escrita);
    }

    // pc att
    if (state->sinal[jump]) {
        state->pc = (int)(ins->instrucao_bruta & 0xFF) - 1; // -1 porque o main sempre faz pc++ depois
    } else if (state->sinal[branch] && saida_ula.zero) {
        state->pc += ins->immediato; //pc= pc+1+imm
    }
}