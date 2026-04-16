#ifndef REGISTRADORES_H
#define REGISTRADORES_H

#include "structs.h"


typedef typ_reg BancoRegistradores;

void inicia_registradores(BancoRegistradores *banco);
void escreve_registrador(BancoRegistradores *banco, int indice, int valor);
int le_registrador(BancoRegistradores *banco, int indice);
void imprime_registradores(BancoRegistradores *banco);

#endif
