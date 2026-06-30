all : rebuild

s21_grep :
	gcc -x c -std=c11 s21_grep.c -o s21_grep -Wall -Werror -Wextra
remove :
	rm -rf s21_grep
rebuild : remove s21_grep

clangN :
	clang-format -style=Google -n *.c
clangI :
	clang-format -style=Google -i *.c
