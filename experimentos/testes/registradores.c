#include <stdio.h>
#include "registradores.h"

void inicia_registradores(BancoRegistradores *banco) {
    int i;
    for(i = 0; i < 8; i++) {
        banco->reg[i] = 0;
    }
}
void escreve_registrador(BancoRegistradores *banco, int indice, int valor) {
    //evitar escrever no 0
    if(indice > 0 && indice < 8) {
        banco->reg[indice] = (signed char)valor;
    }
}

int le_registrador(BancoRegistradores *banco, int indice) {
    if(indice >= 0 && indice < 8) {
        return (int)banco->reg[indice];
    }
    return 0; 
}

void imprime_registradores(BancoRegistradores *banco) {
    int i;
    printf("\nbanco de registradores\n");
    for(i = 0; i < 8; i++) {
        
        printf("$%d: %4d \n", i, banco->reg[i]);
    }

}
