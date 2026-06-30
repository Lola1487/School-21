# Задаем базовый образ контейнера
FROM nginx:latest

# Устанавливаем обновления, нужные программы и чистим кэш apt
RUN apt update -y && apt upgrade -y \
    && apt-get install -y gcc spawn-fcgi libfcgi-dev \
    && apt-get clean

# Копируем исходник cgi сервера
COPY hello.c /home/hello.c

# Компилируем FastCGI приложение
RUN gcc /home/hello.c -o /home/hello.fcgi -lfcgi

# Копируем твой nginx.conf как основной конфиг
COPY nginx.conf /etc/nginx/nginx.conf

# Копируем скрипт
COPY script.sh /script.sh
RUN chmod +x /script.sh

# Открываем порты
EXPOSE 80 443

# Запускаем сервер
ENTRYPOINT ["/script.sh"]
