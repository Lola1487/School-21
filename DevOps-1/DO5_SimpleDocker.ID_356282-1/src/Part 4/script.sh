#!/bin/bash
# Компилируем бинарник
gcc /home/hello.c -o /home/hello.fcgi -lfcgi

# Запускаем fcgi с нашим бинарником в фоне
spawn-fcgi -p 8080 -n /home/hello.fcgi &

# Запускаем nginx в фоновом режиме (foreground)
nginx -g 'daemon off;'
