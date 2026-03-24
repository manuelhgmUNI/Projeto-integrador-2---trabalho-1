#include "structs.h"
#include "funcoes.h"


typ_stt *controlador(typ_stt *state, int n)
{
    enum tipo_i
    {
        addi = 3,
        beq  = 8,
        lw   = 11,
        sw   = 15,
    };
    
    switch (state->instrucao_t[n].tipo)
    {
    case 1: // Tipo R 
        typ_ulaOp ulaop = state->instrucao_t[n].funct;
        typ_ulaR saida_ula = ula(state->registradores[n].$[state->instrucao_t[n].rs], state->registradores[n].$[state->instrucao_t[n].rt], ulaop);
        state->registradores[n].$[state->instrucao_t[n].rd] = saida_ula.resultado;
    break;

    case 2: // Tipo I
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

    case 3:
    
    default:
        break;
    }

}