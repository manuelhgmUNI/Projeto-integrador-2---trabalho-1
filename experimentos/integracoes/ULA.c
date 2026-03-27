#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

typ_ulaR ula(int A, int B, typ_ulaOp operacao) {
    typ_ulaR res;

    switch (operacao) {
        case ADD:
            res.resultado = A + B;
            break;
            
        case SUB:
            res.resultado = A - B;
            break;

        case AND:
            res.resultado = A & B;
            break;

        case OR:
            res.resultado = A | B;
            break;


        case SLT:
            if (A < B)
                res.resultado = 1;
            else
                res.resultado = 0;
            break;
    }
    if (res.resultado == 0)
        res.zero = 1;
    else
        res.zero = 0;

    if (res.resultado > 127 || res.resultado < -128) //verifica overflow 
        res.overflow = 1;
    else
        res.overflow = 0;

    return res;
}