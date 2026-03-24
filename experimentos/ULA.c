#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//removi main pra nao dar conflito, estava dando conflito na hora de compilar
typedef enum {
    AND,
    OR,
    ADD,
    SUB,
    SLT
} ULAOp;

typedef struct {
    signed char resultado; // com sinal ao inves de int
    int zero;
    int overflow;          // overflow caso ultrapassa -128 a 127
} ResultadoULA;

ResultadoULA ula(signed char A, signed char B, ULAOp operacao) {
    ResultadoULA res;
    res.overflow = 0;
    int temp_res = 0; 

    switch (operacao) {
        case AND:
            temp_res = A & B;
            break;

        case OR:
            temp_res = A | B;
            break;

        case ADD:
            temp_res = A + B;
            break;

        case SUB:
            temp_res = A - B;
            break;

        case SLT:
            if (A < B)
                temp_res = 1;
            else
                temp_res = 0;
            break;
    }

    if (operacao == ADD || operacao == SUB) {
        if (temp_res > 127 || temp_res < -128) {
            res.overflow = 1;
        }
    }

    res.resultado = (signed char)temp_res; 
    
    if (res.resultado == 0)
        res.zero = 1;
    else
        res.zero = 0;

    return res;
}
