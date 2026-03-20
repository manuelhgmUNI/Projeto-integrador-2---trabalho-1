#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    AND,
    OR,
    ADD,
    SUB,
    SLT
} ULAOp;

typedef struct {
    int resultado;
    int zero;
} ResultadoULA;

ResultadoULA ula(int A, int B, ULAOp operacao);

int main() {
    
    return 0;
}

ResultadoULA ula(int A, int B, ULAOp operacao) {
    ResultadoULA res;

    switch (operacao) {
        case AND:
            res.resultado = A & B;
            break;

        case OR:
            res.resultado = A | B;
            break;

        case ADD:
            res.resultado = A + B;
            break;

        case SUB:
            res.resultado = A - B;
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

    return res;
}
