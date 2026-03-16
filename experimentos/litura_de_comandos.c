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
    

    FILE *Mem_ins = fopen("memoria1.mem", "r");

    fgets(instrução->total, 17, Mem_ins);
    printf("%s\n", instrução->total);

    instrução->opcode = leitura_binario(instrução->total, 0, 3, 0);
    printf("opcode: %i\n", instrução->opcode);
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
        if (bin[inicio] == 0)
        {
            for (int i = inicio, j = 0; i <= final; i++, j++ )
                if (bin[i] == 1)
                    resultado += (1 << j);
        }
        else if (bin[inicio] == 1)
        {
            resultado = 1;
            for (int i = inicio, j = 0; i <= final; i++, j++ )
                if (bin[i] == 0)
                    resultado += (1 << j);
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