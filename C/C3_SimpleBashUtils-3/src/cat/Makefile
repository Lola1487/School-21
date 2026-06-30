all : rebuild

s21_cat :
	gcc -x c -std=c11 s21_cat.c -o s21_cat -Wall -Werror -Wextra
rm :
	rm -rf s21_cat
rebuild : rm s21_cat

clangN :
	clang-format -style=Google -n *.c
clangI :
	clang-format -style=Google -i *.c

