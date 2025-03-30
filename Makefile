CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS = -lcunit
SRC_DIR = src
BUILD_DIR = build
TESTS_DIR = tests

# Исходные файлы
SRC_MATRIX = $(SRC_DIR)/matrix/matrix.c
SRC_OUTPUT = $(SRC_DIR)/output/output.c
SRC_MAIN = $(SRC_DIR)/main.c

# Объектные файлы
OBJ_MATRIX = $(BUILD_DIR)/matrix/matrix.o
OBJ_OUTPUT = $(BUILD_DIR)/output/output.o
OBJ_MAIN = $(BUILD_DIR)/main.o

# Целевые файлы
TARGET = $(BUILD_DIR)/matrix_project

# Правила по умолчанию
all: $(TARGET)

# Сборка основного проекта
$(TARGET): $(OBJ_MATRIX) $(OBJ_OUTPUT) $(OBJ_MAIN)
	$(CC) $(CFLAGS) -o $@ $^

# Компиляция исходных файлов
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)/matrix $(BUILD_DIR)/output
	$(CC) $(CFLAGS) -c $< -o $@

# Очистка
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
