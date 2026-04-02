#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

int8_t mem_data(unsigned int endereco, int8_t D, bool str, bool ld, bool clear)
{
    FILE *data = NULL;
    bool existia = 1;
    data = fopen("memoria_de_dados.dat", "rb+");
    if (data == NULL)
    {
        data = fopen("memoria_de_dados.dat", "wb+");
        existia = 0;
        if (data == NULL)
            printf("erro na abertura do arquivo!\n");
    }

    if (existia == 0 || clear == 1) // zera
    {
        int8_t zeros[256] = {0};
        fwrite(zeros, sizeof(int8_t), 256, data);
        fseek(data, 0, SEEK_SET);
    }

    if (str == 1) // escreve
    {
        fseek(data, endereco, SEEK_SET);
        fwrite(&D, sizeof(int8_t), 1, data);
    }
    else
        if (ld == 1) // le
        {
            fseek(data, endereco, SEEK_SET);
            fread(&D, sizeof(int8_t), 1, data);
        }
    
    return D;
}