#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ler_inteiro();
void limpa_buff();

int main()
{
    int menu = 0;
    
    do
    {
        printf("\n   -=|| mips unipampa ||=-   \n");
        printf("+-----+-----------------------------------------------------+\n| [1] | Carregar memoria de instrucoes (.mem)               |\n| [2] | Carregar memória de Dados (.dat)                    |\n| [3] | Imprimir memórias (instruções e dados)              |\n| [4] | Imprimir banco de registradores                     |\n| [5] | Imprimir todo simulador (registradores de memorias) |\n| [6] | Salvar .asm                                         |\n| [7] | Salvar .dat                                         |\n| [8] | Executa Programa (run)                              |\n| [9] | Executa uma instrução (Step)                        |\n| [0] | Volta uma instrução (Back)                          |\n+-----+-----------------------------------------------------+\nEntrada: ");
        scanf("%i", &menu);
        limpa_buff();

        switch (menu)
        {
        case 1:
            /* Carregar memoria de instrucoes (.mem) */
        break;
        
        case 2:
            /* Carregar memória de Dados (.dat) */
        break;
        
        case 3:
            /* Imprimir memórias (instruções e dados) */
        break;
        
        case 4:
            /* Imprimir banco de registradores */
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
        
        default:
            break;
        }
    }
    while (menu != 123);
     
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
    while ((c = getchar()) != '\n' && c != EOF){/*curioso kkkkkk*/}
}