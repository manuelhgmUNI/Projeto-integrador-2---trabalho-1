#include "structs.h"

#ifndef funcoes_H
#define funcoes_H


    // ULA
    typ_ulaR ula(int A, int B, typ_ulaOp operacao);

    // Controlador 
    void controlador(typ_stt *state, int n);

    void executarCiclo(typ_stt *state, int n);

#endif
