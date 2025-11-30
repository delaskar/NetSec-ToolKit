# Compilador y flags
CC = gcc
CFLAGS = -Wall -Wextra -g -I./include

# Directorios
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = .

# Archivos fuente
SOURCES = $(SRC_DIR)/main.c \
          $(SRC_DIR)/scanner.c \
          $(SRC_DIR)/validation.c \
          $(SRC_DIR)/output.c \
          $(SRC_DIR)/utils.c \
          $(SRC_DIR)/thread_scanner.c \
          $(SRC_DIR)/banner.c

# Archivos objeto
OBJECTS = $(OBJ_DIR)/main.o \
          $(OBJ_DIR)/scanner.o \
          $(OBJ_DIR)/validation.o \
          $(OBJ_DIR)/output.o \
          $(OBJ_DIR)/utils.o \
          $(OBJ_DIR)/thread_scanner.o \
          $(OBJ_DIR)/banner.o

# Ejecutable final
TARGET = $(BIN_DIR)/scanner

# Regla principal
all: $(OBJ_DIR) $(TARGET)

# Crear directorio obj si no existe
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Regla para compilar el ejecutable
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET) -lpthread
	@echo "✓ Compilación exitosa: $(TARGET)"

# Reglas para compilar cada archivo .c a .o
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.c -o $(OBJ_DIR)/main.o

$(OBJ_DIR)/scanner.o: $(SRC_DIR)/scanner.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/scanner.c -o $(OBJ_DIR)/scanner.o

$(OBJ_DIR)/validation.o: $(SRC_DIR)/validation.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/validation.c -o $(OBJ_DIR)/validation.o

$(OBJ_DIR)/output.o: $(SRC_DIR)/output.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/output.c -o $(OBJ_DIR)/output.o

$(OBJ_DIR)/utils.o: $(SRC_DIR)/utils.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/utils.c -o $(OBJ_DIR)/utils.o

$(OBJ_DIR)/thread_scanner.o: $(SRC_DIR)/thread_scanner.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/thread_scanner.c -o $(OBJ_DIR)/thread_scanner.o

$(OBJ_DIR)/banner.o: $(SRC_DIR)/banner.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/banner.c -o $(OBJ_DIR)/banner.o

# Limpiar archivos generados
clean:
	rm -rf $(OBJ_DIR) $(TARGET) scan_results.txt
	@echo "✓ Limpieza completa"

# Limpiar y recompilar
rebuild: clean all

# Ayuda
help:
	@echo "Uso del Makefile:"
	@echo "  make          - Compila el proyecto"
	@echo "  make clean    - Elimina archivos generados"
	@echo "  make rebuild  - Limpia y recompila"
	@echo "  make help     - Muestra esta ayuda"

.PHONY: all clean rebuild help
