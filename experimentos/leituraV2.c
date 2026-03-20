#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

int main()
{
    enum tipos_de_instrucao
    {
        r = 1,
        i = 2,
        j = 3,
    };

    struct str_instrucao
    {
        enum tipos_de_instrucao tipo;
        uint16_t instrucao_bruta; //unsigned int 16 bits para instrução
        char total_string[18];

        uint16_t opcode;    // 0-3  (4 bits)
        uint16_t rs;        // 4-6  (3 bits)
        uint16_t rt;        // 7-9  (3 bits)
        uint16_t rd;        // 10-12 (3 bits)
        uint16_t funct;     // 13-15 (3 bits)
        int16_t  immediato; // 10-15 (6 bits) - int com sinal p aceita negativos
        uint16_t addr;      // 9-15 (7 bits)
    } *instrucao;

    /*
    0000/000 => ADD => 0/0
    0000/010 => SUB => 0/2
    0000/100 => AND => 0/4
    0000/101 => OR => 0/5
    0100 => AADi => 4
    1011 => LW => 11
    1111 => SW => 15
    1000 => BEQ => 8
    0010 => J => 2
    */


    FILE *Mem_ins = fopen("memoria1.mem", "r"); //so adicionei um tratamento de erro pra caso o arquivo nao abra
    if (Mem_ins == NULL) {
        printf("erro ao abrir o arquivo memoria1.mem\n");
        return 1;
    }



    int linhas = 1;
    do
    {
        char aventureiro = '\0', ultimo = '\0';
        while ((aventureiro = fgetc(Mem_ins))!= EOF)
        {
            if (aventureiro == '\n')
                linhas += 1;
        }
        if (aventureiro != EOF)
            ultimo = aventureiro;
        if(ultimo !=  '\n' && ultimo != '\0')
            linhas += 1;
    } while (0);


    instrucao = (struct str_instrucao *) malloc(linhas * sizeof(*instrucao));
    fseek(Mem_ins, 0, SEEK_SET);


    char buffer_linha[32]; //  buffer p ler a linha toda  ja com o \n

    for (int i = 0 ; i < linhas; i++)
    {

        if (fgets(buffer_linha, sizeof(buffer_linha), Mem_ins) == NULL) break;

        uint16_t inst_bin = (uint16_t) strtol(buffer_linha, NULL, 2);
        instrucao[i].instrucao_bruta = inst_bin;


        instrucao[i].opcode = (inst_bin >> 12) & 0x0F;
        instrucao[i].rs     = (inst_bin >> 9)  & 0x07;
        instrucao[i].rt     = (inst_bin >> 6)  & 0x07;
        instrucao[i].rd     = (inst_bin >> 3)  & 0x07;
        instrucao[i].funct  =  inst_bin        & 0x07;
        instrucao[i].addr   =  inst_bin        & 0x7F;



        if (instrucao[i].opcode == 0) {
            instrucao[i].tipo = r;
        } else if (instrucao[i].opcode == 4 || instrucao[i].opcode == 8 || instrucao[i].opcode == 11 || instrucao[i].opcode == 15) {
            instrucao[i].tipo = i;
        } else if (instrucao[i].opcode == 2) {
            instrucao[i].tipo = j;
        }

        printf("\n instrucao lida : %u / 0x%04X\n", inst_bin, inst_bin);
        printf("opcode: %i\nrs: %i | rt: %i | rd: %i\nfunct: %i | imediato: %i | addr: %i | tipo: %i\n",
               instrucao[i].opcode, instrucao[i].rs, instrucao[i].rt, instrucao[i].rd,
               instrucao[i].funct, instrucao[i].immediato, instrucao[i].addr, instrucao[i].tipo);
    }

    free(instrucao);
    fclose(Mem_ins);
    return 0;
}
