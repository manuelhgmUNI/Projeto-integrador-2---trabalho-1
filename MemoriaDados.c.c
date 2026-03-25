#include <stdio.h>
#define TAM_MEM 1024

void iniciaeMemoria(int *mem);
int lerMemoria(int *mem, int endereco, int MemRead);
void escreveMemoria(int *mem, int endereco, int valor, int MemWrite);

int main()
{   int mem[TAM_MEM];
    inicializaMemoria(mem);
    // escreve valor 50 no endereço 10
    escreveMemoria(mem, 10, 50, 1);
    // lê do endereço 10
    int valor = lerMemoria(mem, 10, 1);
    printf("Valor lido: %d\n", valor);
    return 0;
}

void iniciaeMemoria(int *mem) {
    for (int i=0; i<TAM_MEM; i++) {
        mem[i]=0;
    }
}

int lerMemoria(int *mem, int endereco, int MemRead) {
    if (MemRead) {
        return mem[endereco];
    }
    return 0;
}

void escreveMemoria(int *mem, int endereco, int valor, int MemWrite) {
    if (MemWrite) {
        mem[endereco] = valor;
    }
}