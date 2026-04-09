#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

typ_ulaR ula(int A, int B, typ_ulaOp operacao) {
    typ_ulaR res= {0, false, false};
    int inter_Resul = 0;


    switch (operacao) {
        case ADD:
            inter_Resul = A + B;
            res.overflow = (inter_Resul > 127 || inter_Resul < -128);//overflow
            break;
            
        case SUB:
            inter_Resul = A - B;
            res.overflow = (inter_Resul > 127 || inter_Resul < -128);//overflow
            break;

        case AND:
            inter_Resul = A & B;
            break;

        case OR:
            inter_Resul = A | B;
            break;


        case SLT:
            if (A < B)
                inter_Resul = 1;
            else
                inter_Resul = 0;
            break;
    }

    res.resultado = (int8_t) inter_Resul; //agora sim fazendo um casting para 8 bits apos obter o result intermediario
    res.zero = (res.resultado == 0);

    return res;
}