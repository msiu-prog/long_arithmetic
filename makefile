# -*- mode: makefile -*-

.PHONY : makehelp compile compile-lib compile-calc compile-main test

# Компилятор для языка Си
GCC = gcc -Wall -std=c99

# Объектные файлы проекта
LIBOBJ = long_arithmetic.o
MAINOBJ = main.o
CALCOBJ = calc.o

# Тестирующий исполняемый файл
TESTER = long_arithmetics_tests.rb

# Имена выходных исполняемых бинарных файлов
OUTPUT_BIN_NAME = "longa"
CALC_BIN_NAME = "calc"

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
	@echo "    compile-lib"
	@echo "    compile-calc"
	@echo "    compile-main"
	@echo "    test"
	@echo "    makehelp"

# Компилирование исходников
compile: compile-lib compile-calc compile-main

compile-lib: $(LIBOBJ)

compile-calc: $(LIBOBJ) $(CALCOBJ)
	$(GCC) $(LIBOBJ) $(CALCOBJ) -o $(CALC_BIN_NAME)

compile-main: $(LIBOBJ) $(MAINOBJ)
	$(GCC) $(LIBOBJ) $(MAINOBJ) -o $(OUTPUT_BIN_NAME)

# Тестирование библиотеки
test: compile-calc tests/*
	tests/$(TESTER)


