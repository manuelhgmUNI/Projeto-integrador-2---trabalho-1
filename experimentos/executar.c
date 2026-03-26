#include "funcoes.h"
#include "structs.h"
#include "registradores.h"

int executar()
{
    // inicializaçao
    typ_stt x;
    typ_stt *status;
    status = &x;
    
    typ_reg reg;
    for (int i = 0; i < 8; i++)
        reg.$[i] = 0; 

    x.pc = 0;

    status = decodificado_bit_bit(status);
    
    // fetch

    //instruction decode / banco de registradores
    status = controlador(status, status->pc);
    status->registradores[status->pc] = reg;
    
    // ula / calculo de endereço

    if (status->sinal[ula_fon] = 0)
        status->ular = ula(status->registradores->$[status->instrucao_t->rs], status->registradores->$[status->instrucao_t->rt], status->ulaop);
    else
        status->ular = ula(status->registradores->$[status->instrucao_t->rs], status->registradores->$[status->instrucao_t->immediato], status->ulaop);

    // acesso de memoria
    


    // escrita no banco



}