#ifndef leitura_de_comandos_h
#define leitura_de_comandos_h

#include <stdio.h>

typedef enum {
    tipo_R = 1,
    tipo_I = 2,
    tipo_J = 3
} TipoInstrucao;

typedef struct {
    TipoInstrucao tipo;
    char total[17];
    int opcode;    // Bits 15-12
    int rs;        // Bits 11-9
    int rt;        // Bits 8-6
    int rd;        // Bits 5-3
    int funct;     // Bits 2-0
    int immediato; // Bits 5-0 (com sinal)
    int addr;      // Bits 11-0 (endereço jump)
} instrucaoSep;


int carregar_memoria_instrucoes(instrucaoSep **memoria);

int leitura_binario(char *bin, int inicio, int final, int sinal);

#endif
