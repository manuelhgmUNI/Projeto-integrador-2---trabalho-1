#include"structs.h"

#ifndef funcoes_H
#define funcoes_H  

    // leitura de comandos v1 string
    int leitura_binario(char *bin, int inicio, int final, int sinal);
    int decoder(typ_ins_m *instrução);

    // leitura de comandos v2 bit a bit
    typ_stt *decodificado_bit_bit(typ_stt *state);

    // teste .c
    void limpa_buff();

    // ULA
    ResultadoULA ula(int A, int B, ULAOp operacao);


#endif