# -*- mode: makefile -*-

.PHONY : makehelp compile

# Компилятор для языка Си
GCC = gcc -Wall -std=c99

# Объектные файлы проекта
OBJ = main.o

# Имя выходного исполняего бинарного файла
OUTPUT_BIN_NAME = "longa"

# Правило получения объектных файлов из c-файлов
.c.o: 
	$(GCC) -c $< -o $@

# Действие по умолчанию
default: makehelp

# Подсказка к мейкфайлу
makehelp:
	@echo "makefile for long arithmetic project"
	@echo "available actions:"
	@echo "    compile"

# Компилирование исходников
compile: $(OBJ)
	$(GCC) $(OBJ) -o $(OUTPUT_BIN_NAME)


