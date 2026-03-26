# Nome do compilador
CC = gcc

# Opções de compilação (Wall mostra todos os avisos)
CFLAGS = -Wall

# Nome do executável final
TARGET = simulador

# Lista de arquivos fonte (.c)
SRCS = main.c registradores.c ULA.c leitura_de_comandos.c

# Regra principal (executada ao digitar apenas 'make')
all: $(TARGET)

# Como construir o executável
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

# Regra para limpar o projeto (remove o executável)
clean:
	rm -f $(TARGET)
