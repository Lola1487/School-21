FROM nginx:latest

# Создаем пользователя без прав root
RUN useradd -m -s /bin/bash appuser

WORKDIR /home

# Устанавливаем обновления, нужные программы и чистим кэш
RUN apt update -y && apt upgrade -y \
    && apt-get install -y gcc spawn-fcgi libfcgi-dev \
    && rm -rf /var/lib/apt/lists/*

# Копируем исходник cgi сервера
COPY hello.c /home/hello.c

# Компилируем FastCGI приложение
RUN gcc /home/hello.c -o /home/hello.fcgi -lfcgi && \
    chown appuser:appuser /home/hello.fcgi

# Копируем скрипт и конфиг nginx
COPY script.sh /home/script.sh
COPY nginx.conf /etc/nginx/conf.d/default.conf

# Делаем скрипт исполняемым
RUN chmod +x /home/script.sh

# Переключаемся на пользователя
USER appuser

EXPOSE 80 443

# Добавляем проверку здоровья
HEALTHCHECK --interval=30s --timeout=3s --start-period=5s --retries=3 \
  CMD curl -f http://localhost/status || exit 1

ENTRYPOINT ["bash", "/home/script.sh"]
