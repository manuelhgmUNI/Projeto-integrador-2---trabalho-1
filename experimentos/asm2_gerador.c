#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "funcoes.h"


int asm_gerador_char(char *asembly, typ_ins *instrucao)
{

        switch ((*instrucao).tipo)
        {
            case r: // Tipo R 
                switch((*instrucao).funct)
                {
                    case ADD:
                        sprintf(asembly, "add ");
                    break;

                    case SUB:
                        sprintf(asembly, "sub ");
                    break;

                    case AND:
                        sprintf(asembly, "and ");
                    break;

                    case OR:
                        sprintf(asembly, "or ");
                    break;
                }
                sprintf(asembly + strlen(asembly), "$r%i, $r%i, $r%i\n", (*instrucao).rd, (*instrucao).rs, (*instrucao).rt);


            break;

            case i: // Tipo I
                switch ((*instrucao).opcode)
                {
                case beq:
                    sprintf(asembly, "beq ");
                break;
                    

                case addi:    
                    sprintf(asembly, "addi ");
                break;    


                case lw:
                    sprintf(asembly, "lw ");
                break;


                case sw:
                    sprintf(asembly, "sw ");
                break;
                
                default:
                    break;
                }
                sprintf(asembly + strlen(asembly), "$r%i, $r%i, %i\n", (*instrucao).rs, (*instrucao).rt, (*instrucao).immediato);
            break;

            case j:
                sprintf(asembly, "jump %i\n",(*instrucao).addr);
            break;
            default:
            break;
        }
}