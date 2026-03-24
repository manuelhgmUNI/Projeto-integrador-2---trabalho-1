#include "structs.h"
#include "funcoes.h"


typ_stt *executar_instrução(typ_stt *state, int n)
{
    switch (state[n].instrucao_t.tipo)
    {
    case 1: // Tipo R 
        typ_ulaOp ulaop = state[n].instrucao_t.funct;
        typ_ulaR saida_ula = ula(state[n].registradores.$[state[n].instrucao_t.rs], state[n].registradores.$[state[n].instrucao_t.rt], ulaop);
        state[n].registradores.$[state[n].instrucao_t.rd] = saida_ula.resultado;
    break;

    case 2: // Tipo I

    break;

    case 3:
    
    default:
        break;
    }

}