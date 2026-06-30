#!/bin/bash

# Определяем папку, где находится сам скрипт
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Подключаем другие скрипты
source "$SCRIPT_DIR/utils.sh"
source "$SCRIPT_DIR/gather_info.sh"

# Выводим информацию
echo "HOSTNAME = $HOSTNAME"
echo "TIMEZONE = $TIMEZONE"
echo "USER = $USER"
echo "OS = $OS"
echo "DATE = $DATE"
echo "UPTIME = $UPTIME"
echo "UPTIME_SEC = $UPTIME_SEC"
echo "IP = $IP"
echo "MASK = $MASK"
echo "GATEWAY = $GATEWAY"
echo "RAM_TOTAL = ${RAM_TOTAL} GB"
echo "RAM_USED = ${RAM_USED} GB"
echo "RAM_FREE = ${RAM_FREE} GB"
echo "SPACE_ROOT = ${SPACE_ROOT} MB"
echo "SPACE_ROOT_USED = ${SPACE_ROOT_USED} MB"
echo "SPACE_ROOT_FREE = ${SPACE_ROOT_FREE} MB"

# Предлагаем сохранить в файл
read -rp "Сохранить данные в файл? (Y/N): " answer
if [[ "$answer" =~ ^[Yy]$ ]]; then
    filename="$(date +'%d_%m_%y_%H_%M_%S').status"
    {
        echo "HOSTNAME = $HOSTNAME"
        echo "TIMEZONE = $TIMEZONE"
        echo "USER = $USER"
        echo "OS = $OS"
        echo "DATE = $DATE"
        echo "UPTIME = $UPTIME"
        echo "UPTIME_SEC = $UPTIME_SEC"
        echo "IP = $IP"
        echo "MASK = $MASK"
        echo "GATEWAY = $GATEWAY"
        echo "RAM_TOTAL = ${RAM_TOTAL} GB"
        echo "RAM_USED = ${RAM_USED} GB"
        echo "RAM_FREE = ${RAM_FREE} GB"
        echo "SPACE_ROOT = ${SPACE_ROOT} MB"
        echo "SPACE_ROOT_USED = ${SPACE_ROOT_USED} MB"
        echo "SPACE_ROOT_FREE = ${SPACE_ROOT_FREE} MB"
    } > "$filename"
    echo "Данные сохранены в файл $filename"
else
    echo "Данные не сохранены."
fi
