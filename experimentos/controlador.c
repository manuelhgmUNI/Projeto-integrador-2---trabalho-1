#include "structs.h"
#include "funcoes.h"


typ_stt *controlador(typ_stt *state, int n)
{

    
    switch (state->instrucao_t[n].tipo)
    {
    case r: // Tipo R 
    state->sinal[reg_des] = 1;
    state->sinal[ula_fon] = 0;
    typ_ulaOp ulaop = state->instrucao_t[n].funct;
    state->sinal[mem_reg] = 1;
    state->sinal[esc_reg] = 1;
    state->sinal[jump]    = 0;
    state->sinal[esc_mem] = 0;
    state->sinal[inc_pc]  = 0;
    break;

    case i: // Tipo I
        if (state->instrucao_t[n].opcode != beq)
        {
            typ_ulaOp ulaop = ADD;
            typ_ulaR saida_ula = ula(state->instrucao_t[n].rs, state->instrucao_t[n].immediato, ulaop);
        }    
        switch (state->instrucao_t[n].opcode)
        {
        case beq:
            typ_ulaOp ulaop = AND;
            typ_ulaR saida_ula = ula(state->instrucao_t[n].rs, state->instrucao_t[n].rt, ulaop);
        break;
            

        case addi:    
            state->instrucao_t[n].rt = saida_ula.resultado;
        break;    


        case lw:
            // carregar do endereço de memoria(saida_ula.resultado) para o rt(state->instrucao_t[n].rt)
        break;


        case sw:
            // salvar o rt(state->instrucao_t[n].rt) no endereço de memoria (saida_ula.resultado)
        break;
        
        default:
            break;
        }
    break;

    case j:
    
    default:
        break;
    }

}