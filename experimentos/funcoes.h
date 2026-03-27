#include"structs.h"

#ifndef funcoes_H
#define funcoes_H  

    // leitura de comandos v2 bit a bit
    typ_stt *decodificado_bit_bit(typ_stt *state);

    // teste .c
    void limpa_buff();

    // ULA
    typ_ulaR ula(int A, int B, typ_ulaOp operacao);

    // controlador
    typ_stt *controlador(typ_stt *state, int n);


#endif