#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leitura_de_comandos.h"

int carregar_memoria_instrucoes(instrucaoSep **memoria)
{
    FILE *Mem_ins = fopen("memoria1.mem", "r");
    if (Mem_ins == NULL) {
        printf("erro na leitura\n");
        return 0;
    }

    int linhas = 0;
    char buffer[100];
    
    
    while (fgets(buffer, sizeof(buffer), Mem_ins)) {
        if(strlen(buffer) > 5) { 
            linhas++;
        }
    }
    
    *memoria = (instrucaoSep *) malloc(linhas * sizeof(instrucaoSep));
    fseek(Mem_ins, 0, SEEK_SET);

    for (int i = 0 ; i < linhas; i++)
    {
       
        if (fgets((*memoria)[i].total, 17, Mem_ins) == NULL) break;
        
        char c;
        while ((c = fgetc(Mem_ins)) != '\n' && c != EOF);
        
        
        (*memoria)[i].opcode    = leitura_binario((*memoria)[i].total, 0, 3, 0);   // 15-12
        (*memoria)[i].rs        = leitura_binario((*memoria)[i].total, 4, 6, 0);   // 11-9
        (*memoria)[i].rt        = leitura_binario((*memoria)[i].total, 7, 9, 0);   // 8-6
        (*memoria)[i].rd        = leitura_binario((*memoria)[i].total, 10, 12, 0); // 5-3
        (*memoria)[i].funct     = leitura_binario((*memoria)[i].total, 13, 15, 0); // 2-0
        (*memoria)[i].immediato = leitura_binario((*memoria)[i].total, 10, 15, 1); // 5-0 (com sinal)
        (*memoria)[i].addr      = leitura_binario((*memoria)[i].total, 4, 15, 0);  // 11-0 (Endereço Jump)
        
       
        if ((*memoria)[i].opcode == 0)
            (*memoria)[i].tipo = tipo_R;
        else if ((*memoria)[i].opcode == 2)
            (*memoria)[i].tipo = tipo_J;
        else
            (*memoria)[i].tipo = tipo_I;
    }
    
    fclose(Mem_ins);
    printf("instrucoes carregadas na medmoria.\n", linhas);
    return linhas;
}

int leitura_binario(char *bin, int inicio, int final, int sinal)
{
    int resultado = 0;
    int tamanho = (final - inicio);

    for (int i = inicio, j = tamanho; i <= final; i++, j--) {
        if (bin[i] == '1') {
            resultado += (1 << j);
        }
    }

    
    if (sinal == 1 && bin[inicio] == '1') {
        resultado = resultado - (1 << (tamanho + 1));
    }

    return resultado;
}
