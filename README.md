# Simulador Mini MIPS - 8 bits em C

Um emulador didático de um processador desenvolvido em linguagem C. Este projeto simula o caminho de dados (datapath) e o ciclo de instrução de uma arquitetura baseada no Mini MIPS 8 bits, incluindo o controle de sinais, gerenciamento de memória, banco de registradores e a execução de instruções dos tipos R, I e J.

---

## Funcionalidades

* **Ciclo de Instrução Completo:** Simula as etapas de busca, decodificação, execução, acesso à memória e *write-back*.
* **Unidade de Controle:** Lógica de definição de sinais (ex: `esc_mem`, `esc_reg`, `ula_fon`, `branch`, `jump`) com base no opcode da instrução.
* **Unidade Lógica e Aritmética (ULA):** Execução de operações fundamentais como `ADD`, `SUB`, `AND` e `OR`.
* **Tipos de Instruções Suportadas:**
    * **Tipo R:** Operações aritméticas e lógicas entre registradores.
    * **Tipo I:** Operações com imediatos (`addi`), acesso à memória (`lw`, `sw`) e desvios condicionais (`beq`).
    * **Tipo J:** Desvios incondicionais (`jump`).
* **Gerador de Assembly:** Capacidade de traduzir instruções da máquina sendo simulada de volta para um formato de código Assembly legível (via `asm_gerador.c` e `asm2_gerador.c`).
* **Estatísticas de Execução:** Contagem de instruções processadas por tipo (R, I, J) e instruções `NOP`.

---

## 📂 Estrutura do Projeto

* `main.c`: Ponto de entrada do programa e inicialização das estruturas do simulador.
* `executar.c`: Responsável por coordenar a execução de uma instrução (lê os registradores, passa pela ULA, acessa memória e atualiza o PC).
* `controlador.c`: Define os sinais de controle do processador (Multiplexadores e Habilitações) para a instrução atual.
* `ULA.c`: Implementação da Unidade Lógica e Aritmética.
* `registradores.c`: Gerenciamento do banco de registradores.
* `memoria_de_dados.c`: Simulação da memória principal RAM para leitura e escrita.
* `leitura_de_comandos.c`: Responsável pelo *parsing* e carregamento do código de máquina/instruções para a memória.
* `asm_gerador.c` / `asm2_gerador.c`: Módulos que exportam as instruções carregadas na memória para um arquivo ou string em formato Assembly.
* `structs.h` / `funcoes.h`: Cabeçalhos contendo as definições de estruturas de dados (estado do processador, instruções) e assinaturas de funções.

---

## 🛠️ Tecnologias Utilizadas

* **Linguagem C:** Utilizada por sua eficiência e proximidade com o hardware, ideal para simulação de arquiteturas.
* **GCC (GNU Compiler Collection):** Para compilação do projeto.

---

## ⚙️ Como Compilar e Executar

**1. Clone o repositório:**
```bash
git clone [https://github.com/SEU_USUARIO/NOME_DO_REPOSITORIO.git](https://github.com/SEU_USUARIO/NOME_DO_REPOSITORIO.git)
cd NOME_DO_REPOSITORIO
