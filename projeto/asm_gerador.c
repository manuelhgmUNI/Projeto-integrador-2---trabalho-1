#include <stdio.h>
#include "structs.h"
#include "funcoes.h"


int asm_gerador(typ_ins *instrucao, int n)
{

    FILE *arquivo = NULL;
    arquivo = fopen("saida.asm", "w");
    if (arquivo == NULL)
    {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    
    for (int k = 0; k < n; k++)
    {
        
        switch (instrucao[k].tipo)
        {
            case r: // Tipo R 
                switch(instrucao[k].funct)
                {
                    case ADD:
                        fprintf(arquivo, "add ");
                    break;

                    case SUB:
                        fprintf(arquivo, "sub ");
                    break;

                    case AND:
                        fprintf(arquivo, "and ");
                    break;

                    case OR:
                        fprintf(arquivo, "or ");
                    break;
                }
                fprintf(arquivo, "$r%i, $r%i, $r%i\n", instrucao[k].rd, instrucao[k].rs, instrucao[k].rt);


            break;

            case i: // Tipo I
                switch (instrucao[k].opcode)
                {
                case beq:
                    fprintf(arquivo, "beq ");
                break;
                    

                case addi:    
                    fprintf(arquivo, "addi ");
                break;    


                case lw:
                    fprintf(arquivo, "lw ");
                break;


                case sw:
                    fprintf(arquivo, "sw ");
                break;
                
                default:
                    break;
                }
                fprintf(arquivo, "$r%i, $r%i, %i\n", instrucao[k].rs, instrucao[k].rt, instrucao[k].immediato);
            break;

            case j:
                fprintf(arquivo, "jump %i\n",instrucao[k].addr);
            break;
            default:
            break;
        }
    }
    fclose(arquivo);
    arquivo = NULL;
    return 0;
}