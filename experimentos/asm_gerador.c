#include <stdio.h>
#include "structs.h"
#include "funcoes.h"


void asm_gerador(typ_ins_t *ins, int n)
{

    FILE *arquivo;

    
    for (int k = 0; k < n; k++)
    {
        
        switch (ins[k].tipo)
        {
            case r: // Tipo R 
                switch(ins[k].funct)
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
                fprintf(arquivo, "$r%i, $r%i, $r%i\n", ins[k].rd, ins[k].rs, ins[k].rt);


            break;

            case i: // Tipo I
                switch (ins[k].opcode)
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
                fprintf(arquivo, "$r%i, $r%i, %i\n", ins[k].rs, ins[k].rt, ins[k].immediato);
            break;

            case j:
                fprintf(arquivo, "jump %i\n",ins[k].addr);
            break;
            default:
            break;
        }
    }
}