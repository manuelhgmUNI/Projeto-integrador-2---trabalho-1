#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "structs.h"

int8_t mem_data(typ_mdd *mem, unsigned int endereco, int8_t D, bool str, bool ld, bool clear)
{
    if (mem == NULL) {
        fprintf(stderr, "ERROR: mem_data com ponteiro NULL\n");
        return 0;
    }

    if (clear) {
        memset(mem->dados, 0, sizeof(mem->dados));
    }

    if (endereco >= 256) {
        endereco &= 0xFF; 
    }

    if (str) {
        mem->dados[endereco] = D;
    }

    if (ld) {
        return mem->dados[endereco];
    }

    return D;
}