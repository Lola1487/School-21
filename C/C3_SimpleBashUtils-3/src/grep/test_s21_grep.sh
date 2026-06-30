#!/bin/bash

# Функция для выполнения тестов и сравнения с обычным grep
run_test() {
  echo "Выполнение теста: $1"

  # Выполнение теста с вашим вариантом s21_grep
  echo "Тест с s21_grep:"
  eval $2
  echo "-------------------------------------"

  # Выполнение того же теста с стандартным grep для сравнения
  echo "Тест с стандартным grep:"
  eval $3
  echo "-------------------------------------"
}

# Создание тестовых файлов
echo -e "This is pattern1.\nThis is pattern2.\nNothing here." > file1.txt
echo -e "Pattern1 is here.\nAnother pattern2.\nNo match." > file2.txt
echo -e "Pattern1 found here.\nNo match." > file3.txt
echo -e "pattern1\npattern2" > patterns.txt

# Тест 1: Простой поиск с флагом -e
run_test "Поиск с флагом -e" \
  "./s21_grep -e \"pattern1\" file1.txt" \
  "grep -e \"pattern1\" file1.txt"

# Тест 2: Поиск с флагом -i (игнорирование регистра)
run_test "Поиск с флагом -i" \
  "./s21_grep -i \"pattern1\" file1.txt" \
  "grep -i \"pattern1\" file1.txt"

# Тест 3: Инвертированный поиск с флагом -v
run_test "Инвертированный поиск с флагом -v" \
  "./s21_grep -v \"pattern1\" file1.txt" \
  "grep -v \"pattern1\" file1.txt"

# Тест 4: Подсчет количества совпадений с флагом -c
run_test "Подсчет количества совпадений с флагом -c" \
  "./s21_grep -c \"pattern1\" file1.txt" \
  "grep -c \"pattern1\" file1.txt"

# Тест 5: Печать только имен файлов с флагом -l
run_test "Печать только имен файлов с флагом -l" \
  "./s21_grep -l \"pattern1\" file1.txt file2.txt file3.txt" \
  "grep -l \"pattern1\" file1.txt file2.txt file3.txt"

# Тест 6: Печать номера строки с флагом -n
run_test "Печать номера строки с флагом -n" \
  "./s21_grep -n \"pattern1\" file1.txt" \
  "grep -n \"pattern1\" file1.txt"

# Тест 7: Вывод только совпавших частей строки с флагом -o
run_test "Вывод только совпавших частей строки с флагом -o" \
  "./s21_grep -o \"pattern1\" file1.txt" \
  "grep -o \"pattern1\" file1.txt"

# Тест 8: Комбинированный поиск с флагами -i и -v
run_test "Поиск с флагами -i и -v" \
  "./s21_grep -i -v \"pattern1\" file1.txt" \
  "grep -i -v \"pattern1\" file1.txt"

# Тест 9: Комбинированный поиск с флагами -c и -l
run_test "Поиск с флагами -c и -l" \
  "./s21_grep -c -l \"pattern1\" file1.txt file2.txt file3.txt" \
  "grep -c -l \"pattern1\" file1.txt file2.txt file3.txt"

# Тест 10: Поиск с флагом -e (несколько паттернов)
run_test "Поиск с флагом -e (несколько паттернов)" \
  "./s21_grep -e \"pattern1\" -e \"pattern2\" file1.txt" \
  "grep -e \"pattern1\" -e \"pattern2\" file1.txt"

# Тест 11: Поиск с флагом -f (чтение паттернов из файла)
run_test "Поиск с флагом -f" \
  "./s21_grep -f patterns.txt file1.txt" \
  "grep -f patterns.txt file1.txt"

# Тест 12: Печать только имени файла без строки с флагом -h
run_test "Печать только имени файла с флагом -h" \
  "./s21_grep -h \"pattern1\" file1.txt file2.txt" \
  "grep -h \"pattern1\" file1.txt file2.txt"

# Тест 13: Поиск с флагом -s (игнорирование ошибок с недоступными файлами)
run_test "Поиск с флагом -s" \
  "./s21_grep -s \"pattern1\" nonexistentfile.txt file1.txt" \
  "grep -s \"pattern1\" nonexistentfile.txt file1.txt"

# Тест 14: Поиск с комбинацией флагов -i -v -n -o
run_test "Поиск с флагами -i -v -n -o" \
  "./s21_grep -i -v -n -o \"pattern1\" file1.txt" \
  "grep -i -v -n -o \"pattern1\" file1.txt"

# Тест 15: Поиск с несколькими файлами
run_test "Поиск с несколькими файлами" \
  "./s21_grep \"pattern1\" file1.txt file2.txt file3.txt" \
  "grep \"pattern1\" file1.txt file2.txt file3.txt"
