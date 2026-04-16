
CC = gcc


CFLAGS = -Wall -Wextra -g


TARGET = simulador

SRCS = main.c controlador.c executar.c ULA.c registradores.c leitura_de_comandos.c


OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJS) $(TARGET)


run: $(TARGET)
	./$(TARGET)