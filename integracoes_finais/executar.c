#include "funcoes.h"
#include "structs.h"


int executar(typ_stt *status, typ_reg reg, bool clear_data)
{

    int val_write;
    //instruction decode / banco de registradores
    status = controlador(status, status->pc);
    status->registradores[status->cont_inst] = reg;
    
    // ula / calculo de endereço

    if (status->sinal[ula_fon] == 0)
        status->ular = ula(status->registradores->$[status->instrucao_t[status->pc].rs], status->registradores->$[status->instrucao_t[status->pc].rt], status->ulaop);
    else
        status->ular = ula(status->registradores->$[status->instrucao_t[status->pc].rs], status->instrucao_t[status->pc].immediato, status->ulaop);

    // acesso de memoria
    int8_t saida_mem = mem_data(status->ular.resultado, status->registradores->$[status->instrucao_t[status->pc].rt], !status->sinal[esc_mem], status->sinal[esc_mem], clear_data);
    
    // escrita no banco
    if (status->sinal[esc_reg]) { 
        if (status->sinal[mem_reg] == 1) {
             val_write = saida_mem;
     } else {
            val_write = status->ular.resultado;}
    
        
        if (status->sinal[reg_des]) // rd
            status->registradores->$[status->instrucao_t[status->pc].rd] = val_write;
        else // rt
            status->registradores->$[status->instrucao_t[status->pc].rt] = val_write;
    }


    if (status->sinal[inc_pc]) 
    {
        status->pc += 1;
        if (status->sinal[branch] == status->ular.zero)
            status->pc += status->instrucao_t[status->pc - 1].immediato; // pc-1 porque já somamos 1 acima
        else if (status->sinal[jump])
            status->pc = status->instrucao_t[status->pc - 1].addr;
    }
    
    return 0;
}