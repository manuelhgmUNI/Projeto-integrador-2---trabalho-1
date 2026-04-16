#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "funcoes.h"

int main()
{
    typ_stt *teste = NULL;
    typ_ins_m *insteste = NULL;
    teste = (typ_stt *) malloc(sizeof(typ_stt));


    int menu;
    int flag = 0;
    do
    {
        printf("1 - leitura de comandos V1\n2 - leitura de comandos V2\n3 - ula\n0 - sair\n");
        scanf("%i", &menu);
        limpa_buff();
        switch (menu)
        {
            case 1:
                decoder(insteste); // veio
            break;
            case 2:
                teste = decodificado_bit_bit(teste);
                flag = 1;   
            break;

            case 3:
                if (flag == 1)
                {
                    int temp_ula;
                    printf("ula: \n instrução:");
                    scanf("%i", &temp_ula);
                    limpa_buff();
                    if (teste->instrucao_t[temp_ula].tipo != 3)
                    {
                        typ_ulaOp operacao = teste->instrucao_t[temp_ula].opcode;
                        typ_ulaR resul = ula(teste->instrucao_t[temp_ula].rs, teste->instrucao_t[temp_ula].rt, operacao);
                        printf("resultado: %i\nflag: %i\n", resul.resultado, resul.zero);
                    }
                    else
                        printf("selecione uma opção valida!\n");
                }
                else
                    printf("execute a 2 primeiro\n");
            break;
            
            case 0:
            return 0;
            break;
            
            default:
            break;
        }
    } while(menu != 0);

    free(teste);
    free(insteste);
    return 0;
    
}

void limpa_buff()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF){/*curioso kkkkkk*/}
}