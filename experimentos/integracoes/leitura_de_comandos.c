#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "structs.h"
#include "leitura_de_comandos.h"


int carregar_memoria_instrucoes(instrucaoSep **mem_out)
{
    char nome_arquivo[64];
    printf("Nome do arquivo .mem: ");
    if (scanf("%63s", nome_arquivo) != 1) return 0;

    FILE *Mem_ins = fopen(nome_arquivo, "r");
    if (Mem_ins == NULL) {
        printf("Erro ao abrir o arquivo '%s'.\n", nome_arquivo);
        return 0;
    }

    //malloc ate 255
    instrucaoSep *mem = (instrucaoSep *) malloc(255 * sizeof(instrucaoSep));
    if (mem == NULL) {
        fclose(Mem_ins);
        return 0;
    }

    char buffer_linha[34]; 
    int count = 0;

    for (int i = 0; i < 255; i++) {
        if (fgets(buffer_linha, sizeof(buffer_linha), Mem_ins) == NULL) break;

        buffer_linha[strcspn(buffer_linha, "\r\n")] = '\0';
        if (strlen(buffer_linha) == 0) continue; //pular linha em branco

        uint16_t inst_bin = (uint16_t) strtol(buffer_linha, NULL, 2);
        mem[i].instrucao_bruta = inst_bin;

        strncpy(mem[i].total, buffer_linha, 17);
        mem[i].total[17] = '\0';

        //decodificacao bit a bit de acordo com v2
        mem[i].opcode = (inst_bin >> 12) & 0x0F;
        mem[i].rs     = (inst_bin >> 9)  & 0x07;
        mem[i].rt     = (inst_bin >> 6)  & 0x07;
        mem[i].rd     = (inst_bin >> 3)  & 0x07;
        mem[i].funct  =  inst_bin        & 0x07;
        mem[i].addr   =  inst_bin        & 0xFF; //tava pegando so 7 ao inves de 8

    
        int16_t imm6 = (int16_t)(inst_bin & 0x3F);
        if (imm6 & 0x20) imm6 |= (int16_t)0xFFC0; /* estende sinal */
        mem[i].immediato = imm6;

        //classicar tipo
        if (mem[i].opcode == 0) {
            mem[i].tipo = r;
        } else if (mem[i].opcode == addi || mem[i].opcode == beq ||
                   mem[i].opcode == lw   || mem[i].opcode == sw) {
            mem[i].tipo = (enum tipos_de_instrucao)2; //tava dando conflito por causa do i e agr deixei explicito que é o tipo
        } else if (mem[i].opcode == 2) {
            mem[i].tipo = j;
        }

        printf("instrucao [%d]: %s | Op:%d rs:%d rt:%d rd:%d funct:%d imm:%d addr:%d tipo:%d\n",
               i, mem[i].total, mem[i].opcode, mem[i].rs, mem[i].rt,
               mem[i].rd, mem[i].funct, mem[i].immediato, mem[i].addr, mem[i].tipo);

        count++;
    }

    fclose(Mem_ins);
    *mem_out = mem;
    return count;
}
