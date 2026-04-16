#include<stdio.h>
#include<stdlib.h>
#include"leitura_de_comandos.h"

int leitura_binario(char *bin, int inicio, int final, int sinal);


int leitura_memoria()
{
    enum tipos_de_instrução
    {
        r = 1,
        i = 2,
        j = 3,

    };
    struct str_instrucao
    {
        enum tipos_de_instrução tipo;
        char total[17];
        int opcode; // 0-3
        int rs; // 4-6
        int rt; // 7-9
        int rd; // 10-12
        int funct; // 13-15
        int immediato; // 10-15
        int addr; //endereço do jump
    }*instrução;
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
    str_i *instru;

    FILE *Mem_ins = fopen("memoria1.mem", "r");
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
    
    instrução = (struct str_instrucao *) malloc(linhas * sizeof(*instrução));

    fseek(Mem_ins, 0, SEEK_SET);

    for (int i = 0 ; i < linhas; i++)
    {
        fgets(instrução[i].total, 17, Mem_ins);
        int c;
        c = fgetc(Mem_ins);
        
        instrução[i].opcode = leitura_binario(instrução[i].total, 0, 3, 0);
        instrução[i].rs = leitura_binario(instrução[i].total, 4, 6, 0);
        instrução[i].rt = leitura_binario(instrução[i].total, 7, 9, 0);
        instrução[i].rd = leitura_binario(instrução[i].total, 10, 12, 0);
        instrução[i].funct = leitura_binario(instrução[i].total, 13, 15, 0);
        instrução[i].immediato = leitura_binario(instrução[i].total, 10, 15, 1);
        instrução[i].addr = leitura_binario(instrução[i].total, 9, 15, 0);
        
        if (instrução[i].opcode == 0)
        instrução[i].tipo = 1;
        else if (instrução[i].opcode == 4 || instrução[i].opcode == 8 || instrução[i].opcode == 11 || instrução[i].opcode == 15)
        instrução[i].tipo = 2;
        else if (instrução[i].opcode == 2)
        instrução[i].tipo = 3;

        printf("\n%s\n", instrução[i].total);
           
        printf("opcode: %i\nrs: %i | rt: %i | rd: %i\nfunct: %i | imediato: %i | addr: %i | tipo: %i\n", instrução[i].opcode, instrução[i].rs, instrução[i].rt, instrução[i].rd, instrução[i].funct, instrução[i].immediato, instrução[i].addr, instrução[i].tipo);
    }
    
    free(instrução);
}

int leitura_binario(char *bin, int inicio, int final, int sinal)
{

    int resultado = 0, tamanho = (final-inicio);
    if (sinal == 0)
    {
        for (int i = inicio, j = tamanho; i <= final; i++, j-- )
        {
            int temp = bin[i];
            if (bin[i] == '1')
                resultado += (1 << j);
        }
    }
    else if (sinal == 1)
    {
        if (bin[inicio] == '0')
        {
            for (int i = inicio, j = tamanho; i <= final; i++, j-- )
                if (bin[i] == '1')
                    resultado += (1 << j);
        }
        else if (bin[inicio] == '1')
        {
            resultado = 1;
            for (int i = inicio, j = tamanho; i <= final; i++, j-- )
                if (bin[i] == '0')
                    resultado += (1 << j);
            resultado *= (-1);
        }
        
        /*
        char *nbin = NULL;
        nbin = malloc((tamanho+1)*sizeof(*nbin));

        free(nbin);
        nbin = NULL;
        */
    }
    return resultado;
}