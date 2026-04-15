#include "funcoes.h"
#include "structs.h"

int executar(typ_stt *status, typ_reg reg, bool clear_data)
{
    
    // pc
    if (status->sinal[inc_pc])
    {
        status->pc += 1;
        if (status->sinal[branch] == status->ular.zero)
            status->pc += status->instrucao_t[status[status->cont_inst].pc].immediato;
        else if (status->sinal[jump])
            status->pc = status->instrucao_t[status[status->cont_inst].pc].addr;
    }

    //instruction decode / banco de registradores
    status = controlador(status, status->cont_inst);
    status->sbreg = Banco_de_registradores(status->registradores->$[status->instrucao_t[status[status->cont_inst].pc].rs], status->registradores->$[status->instrucao_t[status[status->cont_inst].pc].rt], status->registradores->$[status->instrucao_t[status[status->cont_inst].pc].rd], status->sinal[esc_reg], &reg);
    
    // ula / calculo de endereço

    if (status->sinal[ula_fon] = 0)
        status->ular = ula(status->sbreg.s1, status->sbreg.s2, status->ulaop);
    else
        status->ular = ula(status->sbreg.s1, status->registradores->$[status->instrucao_t[status[status->cont_inst].pc].immediato], status->ulaop);

    // acesso de memoria

    int8_t saida_mem = mem_data(status->ular.resultado, reg.$[status->instrucao_t[status[status->cont_inst].pc].rt], !status->sinal[esc_mem], status->sinal[esc_mem], clear_data);
    
    // escrita no banco
    if (status->sinal[mem_reg]) // saida da memoria ( ula ou memoria ==> registrador)
        if (status->sinal[reg_des]) // mux do registrador (1 = rd e 0 = rt)
            reg.$[status->instrucao_t[status[status->cont_inst].pc].rd] = status->ular.resultado;
        else
            reg.$[status->instrucao_t[status[status->cont_inst].pc].rt] = status->ular.resultado;
    else
        if (status->sinal[reg_des])
            reg.$[status->instrucao_t[status[status->cont_inst].pc].rd] = saida_mem;
        else
            reg.$[status->instrucao_t[status[status->cont_inst].pc].rt] = saida_mem;


        
    


}