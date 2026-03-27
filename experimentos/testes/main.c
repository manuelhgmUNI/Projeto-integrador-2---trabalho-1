#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "registradores.h"
#include "leitura_de_comandos.h"

int ler_inteiro();
void limpa_buff();

int main()
{
    int menu = 0;
    BancoRegistradores meu_banco;
    instrucaoSep *memoria_instrucoes = NULL;
    int num_instrucoes = 0;

    inicia_registradores(&meu_banco);
    
    do
    {
        printf("\n   -=|| mips unipampa ||=-   \n");
        printf("+-----+-----------------------------------------------------+\n| [1] | Carregar memoria de instrucoes (.mem)               |\n| [2] | Carregar memória de Dados (.dat)                    |\n| [3] | Imprimir memórias (instruções e dados)              |\n| [4] | Imprimir banco de registradores                     |\n| [5] | Imprimir todo simulador (registradores de memorias) |\n| [6] | Salvar .asm                                         |\n| [7] | Salvar .dat                                         |\n| [8] | Executa Programa (run)                              |\n| [9] | Executa uma instrução (Step)                        |\n| [0] | Volta uma instrução (Back)                          |\n+-----+-----------------------------------------------------+\nEntrada: ");
        scanf("%i", &menu);
        limpa_buff();

        switch (menu)
        {
        case 1:
            //verifica se a memoria ja está alocada
            /* Carregar memoria de instrucoes (.mem) */
            if (memoria_instrucoes != NULL) {
                free(memoria_instrucoes);
            }
            num_instrucoes = carregar_memoria_instrucoes(&memoria_instrucoes);
            break;
        
        case 2:
            /* Carregar memória de Dados (.dat) */
            break;
        
        case 3:
            /* Imprimir memórias (instruções e dados) */
            if (memoria_instrucoes == NULL) {
                printf("carregue o arquivo primeiro \n");
            } else {
                printf("\nConteudo da Memoria de Instrucoes\n");
                for (int i = 0; i < num_instrucoes; i++) {
                    printf("[%03d] %s (Opcode: %d, Tipo: %d)\n", i, 
                           memoria_instrucoes[i].total, 
                           memoria_instrucoes[i].opcode,
                           memoria_instrucoes[i].tipo);
                }
            }
            break;
        
        case 4:
            /* Imprimir banco de registradores */
            imprime_registradores(&meu_banco);
            break;
        
        case 5:
            /* Imprimir todo simulador (registradores de memorias) */
            break;
        
        case 6:
            /* Salvar .asm */
            break;
        
        case 7:
            /* Salvar .dat */
            break;

        case 8:
            /* Executa Programa (run) */
            break;
        
        case 9:
            /* Executa uma instrução (Step) */
            break;

        case 0:
            /* Volta uma instrução (Back) */
            break;
        
        case 123:
            printf("simulador finalizado\n");
            break;

        default:
            printf("opcao invalida.\n");
            break;
        }
    }
    while (menu != 123);

    if (memoria_instrucoes != NULL) {
        free(memoria_instrucoes);
        printf("memoria de instrucoes liberada.\n");
    }
     
    return 0;
}

int ler_inteiro()
{
    char snum[32] = "";
    int num = 0;

    if (fgets(snum, sizeof(snum), stdin) != NULL) 
    {
        snum[strcspn(snum, "\n")] = '\0';
        num = atoi(snum);
    }

    return num;
}

void limpa_buff()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
