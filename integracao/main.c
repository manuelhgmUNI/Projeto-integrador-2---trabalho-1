#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "funcoes.h"
#include "registradores.h"
#include "leitura_de_comandos.h"

void limpa_buff();

int main()
{
    int menu          = 0;
    int num_instrucoes = 0;

   //incializar
    typ_stt estado;
    estado.pc        = 0;
    estado.hist_topo = 0; //hist pilha

    BancoRegistradores banco;
    inicia_registradores(&banco);
    estado.registradores = &banco;

   //zerar
    typ_mem_dados mem_dados;
    memset(mem_dados.dados, 0, sizeof(mem_dados.dados));//zerar
    estado.mem_dados = &mem_dados;

    typ_instrucaoSep *memoria_instrucoes = NULL;

    do
    {
        //5,6,7 imprimir simulador, .asm, .dat
        printf("\n   -=|| MIPS UNIPAMPA ||=-   \n");
        printf(" PC: %d | Instrucoes Carregadas: %d\n", estado.pc, num_instrucoes);
        printf("+------+----------------------------------------------------+\n");
        printf("| [1]  | Carregar memoria de instrucoes (.mem)              |\n");
        printf("| [2]  | Carregar memoria de dados (.dat)                   |\n"); 
        printf("| [3]  | Imprimir memorias (instrucoes e dados)             |\n");
        printf("| [4]  | Imprimir banco de registradores                    |\n");
        printf("| [8]  | Executar Programa (Run)                            |\n"); // executa tudo em loop
        printf("| [9]  | Executar uma instrucao (Step)                      |\n"); //no step ele avança um pc por vez e ja preenche o pc_hist
        printf("| [10] | Voltar uma instrucao (Back)                        |\n"); //precisa refatorar, ela resgata somente o pc, mas n resgata os dados da mem e dos registradores (!!!!!)
        printf("| [0]  | Resetar PC e Registradores                         |\n");
        printf("| [123]| Sair                                               |\n");
        printf("+------+----------------------------------------------------+\n");
        printf("Entrada: ");

        if (scanf("%i", &menu) != 1) {
            limpa_buff();
            continue;
        }
        limpa_buff();

        switch (menu)
        {
        case 1:
            if (memoria_instrucoes != NULL) free(memoria_instrucoes);
            num_instrucoes = carregar_memoria_instrucoes(&memoria_instrucoes);
            estado.instrucao_t = (typ_ins*)memoria_instrucoes;
            estado.pc          = 0;
            estado.hist_topo   = 0; 
            estado.sinal[inc_pc] = 0;
            break;

        case 2: {
            char nome_dat[25];
            printf("Nome do arquivo .dat: ");
            if (scanf("%24s", nome_dat) != 1) { limpa_buff(); break; }
            limpa_buff();

            FILE *f = fopen(nome_dat, "r");
            if (f == NULL) {
                printf("Erro ao abrir '%s'.\n", nome_dat);
                break;
            }
            memset(mem_dados.dados, 0, sizeof(mem_dados.dados));
            int val, idx = 0;
            while (idx < 256 && fscanf(f, "%d", &val) == 1)
                mem_dados.dados[idx++] = (int8_t)val;
            fclose(f);
            printf("memoria de dados carregada (%d posicoes).\n", idx);
            break;
        }

        case 3:
            if (memoria_instrucoes == NULL) {
                printf("Erro\n");
            } else {
                printf("\nmemoria de instrucoes\n");
                for (int i = 0; i < num_instrucoes; i++) {
                    printf("[%03d] %s | Op: %d | Funct: %d\n", i,
                           memoria_instrucoes[i].total,
                           memoria_instrucoes[i].opcode,
                           memoria_instrucoes[i].funct);
                }
               
                printf("\nmem de dados \n");
                int tem = 0;
                for (int i = 0; i < 256; i++) {
                    if (mem_dados.dados[i] != 0) {
                        printf("[%03d] = %d\n", i, mem_dados.dados[i]);
                        tem = 1;
                    }
                }
                if (!tem) printf("(vazia)\n");
            }
            break;

        case 4:
            imprime_registradores(&banco);
            break;

        case 8: //run
            if (memoria_instrucoes == NULL) {
                printf("erro\n");
                break;
            }
            printf("executando\n");
            estado.hist_topo = 0; //clear antes do run
            while (estado.pc < num_instrucoes) {
               executarCiclo(&estado, estado.pc);
                estado.pc++;
            }
            printf("finalizado PC: %d\n", estado.pc);
            break;

        case 9: //step
            if (memoria_instrucoes == NULL) {
                printf("erro \n");
            } else if (estado.pc >= num_instrucoes) {
                printf("fim do programa .\n");
            } else {
               //historico pc
                if (estado.hist_topo < 256)
                    estado.pc_hist[estado.hist_topo++] = estado.pc;

                printf("eexecutando pc[%d]: %s\n", estado.pc,
                memoria_instrucoes[estado.pc].total);

                executarCiclo(&estado, estado.pc);
                estado.pc++;
                imprime_registradores(&banco);
            }
            break;

            //volta um passo mas pega so o pc, teriamos que ver uma forme de armazenar o restante
        case 10:
            if (estado.hist_topo == 0) {
                printf("nao tem instrucao anterior para voltar\n");
            } else {
                estado.pc = estado.pc_hist[--estado.hist_topo];
                printf("back:  restaurado para %d.\n", estado.pc);
                imprime_registradores(&banco);//reg  e mem dados nao sao desfeitos :/
            }
            break;

        case 0:
            estado.pc        = 0;
            estado.hist_topo = 0;
            inicia_registradores(&banco);
            memset(mem_dados.dados, 0, sizeof(mem_dados.dados));
            printf("foi resetado :) .\n");
            break;

        case 123:
            printf("exiting\n");
            break;

        default:
            printf("invalido \n");
            break;
        }
    }
    while (menu != 123);

    if (memoria_instrucoes != NULL) free(memoria_instrucoes);
    return 0;
}

void limpa_buff()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
