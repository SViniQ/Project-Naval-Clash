# Nome do executável
TARGET = programa

# Diretórios
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -I$(INC_DIR) -std=c99

# Arquivos
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# Regra principal
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compila cada arquivo .c para .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Cria o diretório de build
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Limpa os arquivos compilados
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Regra padrão
.PHONY: clean
