#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int leitura_binario(char *bin, int inicio, int final, int sinal);


int main()
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
               
    FILE *Mem_ins = fopen("memoria1.mem", "r");

    fgets(instrução->total, 17, Mem_ins);
    printf("%s\n", instrução->total);

    instrução->opcode = leitura_binario(instrução->total, 0, 3, 0);
    printf("opcode: %i\n", instrução->opcode);
    
    instrução->rs = leitura_binario(instrução->total, 4, 6, 0);

    instrução->rt = leitura_binario(instrução->total, 7, 9, 0);

    instrução->rd = leitura_binario(instrução->total, 10, 12, 0);

    printf("rs: %i\nrt: %i\nrd: %i\n", instrução->rs, instrução->rt, instrução->rd);

    instrução->immediato = leitura_binario(instrução->total, 10, 15, 1);
    printf("imediato: %i\n", instrução->immediato);
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