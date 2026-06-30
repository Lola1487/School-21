#!/bin/bash
# Запускаем fcgi с нашим бинарником в фоне
spawn-fcgi -p 8080 -n /home/hello.fcgi &

# Запускаем nginx в foreground
nginx -g 'daemon off;'
