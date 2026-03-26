#include <stdio.h>

#define TAM 256

int buscaInstrucao(int *memoria, int pc);

int main() {
    int memoria[TAM];
    int pc = 0;
    int instrucao;

    // Exemplo: carregando instruções fictícias
    memoria[0] = 10;
    memoria[1] = 20;
    memoria[2] = 30;

    // Ciclo de busca
    instrucao = buscaInstrucao(memoria, pc);
    printf("Instrucao: %d\n", instrucao);

    pc = pc + 4;

    instrucao = buscaInstrucao(memoria, pc);
    printf("Instrucao: %d\n", instrucao);

    return 0;
}

int buscaInstrucao(int *memoria, int pc) {
    return memoria[pc / 4];
}