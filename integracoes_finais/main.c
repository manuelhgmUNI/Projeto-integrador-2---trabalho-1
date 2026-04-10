#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "funcoes.h"

void limpa_buff();

int main()
{
    int menu          = 0;
    int num_instrucoes = 0;

   //incializar
    typ_stt estado;
    memset(&estado, 0, sizeof(typ_stt));
    estado.pc        = 0;

    BancoRegistradores banco;
    inicia_registradores(&banco);
    estado.registradores = &banco;

   //zerar
    typ_mem_dados mem_dados;
    memset(mem_dados.dados, 0, sizeof(mem_dados.dados)); // zerar
    estado.mem_dados = &mem_dados;

    // inicializar backup do backstep
    estado.topo_pilha=0;
    estado.total_instrucoes = 0;
    estado.r_instrucoes = 0;
    estado.i_instrucoes = 0;
    estado.j_instrucoes = 0;

    typ_instrucaoSep *memoria_instrucoes = NULL;

    do
    {
        //5,6,7 imprimir simulador, .asm, .dat
        printf("\n   -=|| MIPS UNIPAMPA ||=-   \n");
        printf(" PC: %d | Instrucoes Carregadas: %d\n", estado.pc, num_instrucoes);
        printf("+------+----------------------------------------------------+\n");
        printf("| [1]  | Carregar memoria de instrucoes (.mem)              |\n");
        printf("| [2]  | Carregar memoria de dados (.dat)                   |\n"); //implementado
        printf("| [3]  | Imprimir memorias (instrucoes e dados)             |\n");
        printf("| [4]  | Imprimir banco de registradores                    |\n");
        printf("| [5]  | Imprimir estado completo (memoria + registradores) |\n");
        printf("| [6]  | Salvar binario                                       |\n"); //asm
        printf("| [7]  | Salvar .dat                                        |\n"); //salvando o .dat
        printf("| [8]  | Executar Programa (Run)                            |\n"); // executa tudo em loop
        printf("| [9]  | Executar uma instrucao (Step)                      |\n"); 
        printf("| [10] | Voltar uma instrucao (Back)                        |\n"); //precisa refatorar, ela resgata somente o pc, mas n resgata os dados da mem e dos registradores (!!!!!)
        printf("| [11] | Gerar .asm                                         |\n");
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

        case 5:
            printf("\n  ESTADO COMPLETO \n");
            imprime_registradores(&banco);
            printf("\nmem de dados:\n");
            for (int i = 0; i < 256; i++) {
                if (mem_dados.dados[i] != 0) {
                    printf("[%03d]=%d ", i, mem_dados.dados[i]);
                }
            }
            printf("\n");
            break;

        case 6: {
            char nome_asm[25];
            printf("Nome do arquivo de saida .asm: ");
            if (scanf("%24s", nome_asm) == 1) {
                FILE *f = fopen(nome_asm, "w");
                if (f) {
                    for (int i = 0; i < num_instrucoes; i++) {
                        fprintf(f, "%s\n", memoria_instrucoes[i].total);
                    }
                    fclose(f);
                    printf("Arquivo .asm salvo: %s\n", nome_asm);
                } else printf("Erro ao criar %s\n", nome_asm);
            }
            limpa_buff();
            break;
        }

        case 7: {
            char nome_dat[25];
            printf("Nome do arquivo de saida .dat: ");
            if (scanf("%24s", nome_dat) == 1) {
                FILE *f = fopen(nome_dat, "w");
                if (f) {
                    for (int i = 0; i < 256; i++) {
                        fprintf(f, "%d\n", mem_dados.dados[i]);
                    }
                    fclose(f);
                    printf("Arquivo .dat salvo: %s\n", nome_dat);
                } else printf("Erro ao criar %s\n", nome_dat);
            }
            limpa_buff();
            break;
        }

        case 8: //run
            if (memoria_instrucoes == NULL) {
                printf("erro\n");
                break;
            }
            printf("executando\n");
            while (estado.pc < num_instrucoes) {
                executar(&estado, banco, false);
            }
            printf("finalizado PC: %d\n", estado.pc);
            break;

        case 9: //step
    
            if (estado.pc >= num_instrucoes) {
                printf("fim do programa .\n");
            } else {
                // backup do proximo estado para Back
               if (estado.topo_pilha < 2000)
               {
                    estado.pilha_back[estado.topo_pilha].pc = estado.pc;
                    estado.pilha_back[estado.topo_pilha].banco_reg = banco;
                    estado.pilha_back[estado.topo_pilha].mem_dados = mem_dados;
                    estado.topo_pilha++; // sobe o topo da pilha       
               }else printf("limite atingido\n");
               
                printf("eexecutando pc[%d]: %s\n", estado.pc,
                       memoria_instrucoes[estado.pc].total);

                executar(&estado, banco, false);
                imprime_registradores(&banco);
            }
            break;

        case 10:
            
            if (estado.topo_pilha > 0) {
                //decrementa
                estado.topo_pilha--; 

                //restauracao
                estado.pc = estado.pilha_back[estado.topo_pilha].pc;
                banco = estado.pilha_back[estado.topo_pilha].banco_reg;
                mem_dados = estado.pilha_back[estado.topo_pilha].mem_dados;
                
                printf("back: restaurado para PC=%d\\n", estado.pc);
                imprime_registradores(&banco);
            } else {
                printf("nao tem instrucao anterior para voltar\\n");
            }           
            break;

        
        case 11:
           if (memoria_instrucoes != NULL && num_instrucoes > 0) {
                printf("gerando :)...\n");
                
                asm_gerador(memoria_instrucoes, num_instrucoes);
                
                printf("arquivo assembly pronto\n");
            } else {
                printf("erro\n");
            }
            break;
        case 12:
            printf("Estatisticas: \n");
            printf("Total de instrucoes: %s\n", estado.total_instrucoes);
            printf("R: %i\n", estado.r_instrucoes);
            printf("I: %i\n", estado.i_instrucoes);
            printf("J: %i\n", estado.j_instrucoes);
            break;
        case 0:
            estado.pc = 0;
            estado.topo_pilha = 0;
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
