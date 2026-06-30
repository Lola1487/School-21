#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

source "$SCRIPT_DIR/config.sh"
source "$SCRIPT_DIR/functions.sh"

# Сбор информации о системе
HOSTNAME=$(hostname)

# Временная зона
if command -v timedatectl &>/dev/null; then
    TZ_NAME=$(timedatectl show -p Timezone --value)
else
    TZ_NAME=$(cat /etc/timezone 2>/dev/null || echo "Unknown")
fi

# Упрощаем форматирование времени
UTC_OFFSET=$(date +%z)
TIMEZONE="$TZ_NAME UTC ${UTC_OFFSET:0:3}:${UTC_OFFSET:3:2}"

USER=$(whoami)

# Информация об ОС
if [ -f /etc/os-release ]; then
    OS_NAME=$(grep "^PRETTY_NAME=" /etc/os-release | cut -d= -f2- | tr -d '"')
else
    OS_NAME=$(uname -s)
fi
OS="$OS_NAME"

DATE=$(date +"%d %b %Y %H:%M:%S")
UPTIME=$(uptime -p | sed 's/up //')
UPTIME_SEC=$(awk '{print int($1)}' /proc/uptime)

# Сетевые настройки
IP=""
MASK=""
while read -r line; do
    if [[ $line =~ inet\ ([0-9]+\.[0-9]+\.[0-9]+\.[0-9]+)/([0-9]+) ]]; then
        ip_addr=${BASH_REMATCH[1]}
        prefix=${BASH_REMATCH[2]}
        if [[ "$ip_addr" != "127.0.0.1" ]]; then
            IP=$ip_addr
            MASK=$(prefix_to_mask "$prefix")
            break
        fi
    fi
done < <(ip -4 addr show 2>/dev/null)

# Альтернативный способ если IP не найден
if [ -z "$IP" ]; then
    IP=$(hostname -I 2>/dev/null | awk '{print $1}')
    MASK="255.255.255.0"
fi

GATEWAY=$(ip route | grep default | head -n1 | awk '{print $3}' 2>/dev/null)

# Память
MemTotal_kb=$(grep MemTotal /proc/meminfo | awk '{print $2}')
MemFree_kb=$(grep MemFree /proc/meminfo | awk '{print $2}')
Buffers_kb=$(grep Buffers /proc/meminfo | awk '{print $2}')
Cached_kb=$(grep ^Cached /proc/meminfo | awk '{print $2}')
MemUsed_kb=$((MemTotal_kb - MemFree_kb - Buffers_kb - Cached_kb))

RAM_TOTAL=$(kb_to_gb $MemTotal_kb)
RAM_USED=$(kb_to_gb $MemUsed_kb)
RAM_FREE=$(kb_to_gb $MemFree_kb)

# Дисковое пространство
space_root_kb=$(df --block-size=1K / 2>/dev/null | awk 'NR==2 {print $2}' | sed 's/K//')
space_root_used_kb=$(df --block-size=1K / 2>/dev/null | awk 'NR==2 {print $3}' | sed 's/K//')
space_root_free_kb=$(df --block-size=1K / 2>/dev/null | awk 'NR==2 {print $4}' | sed 's/K//')

SPACE_ROOT=$(kb_to_mb $space_root_kb)
SPACE_ROOT_USED=$(kb_to_mb $space_root_used_kb)
SPACE_ROOT_FREE=$(kb_to_mb $space_root_free_kb)

# Выводим информацию с цветами
color_echo "HOSTNAME" "$HOSTNAME"
color_echo "TIMEZONE" "$TIMEZONE"
color_echo "USER" "$USER"
color_echo "OS" "$OS"
color_echo "DATE" "$DATE"
color_echo "UPTIME" "$UPTIME"
color_echo "UPTIME_SEC" "$UPTIME_SEC"
color_echo "IP" "$IP"
color_echo "MASK" "$MASK"
color_echo "GATEWAY" "$GATEWAY"
color_echo "RAM_TOTAL" "${RAM_TOTAL} GB"
color_echo "RAM_USED" "${RAM_USED} GB"
color_echo "RAM_FREE" "${RAM_FREE} GB"
color_echo "SPACE_ROOT" "${SPACE_ROOT} MB"
color_echo "SPACE_ROOT_USED" "${SPACE_ROOT_USED} MB"
color_echo "SPACE_ROOT_FREE" "${SPACE_ROOT_FREE} MB"

# Пустая строка и вывод цветовой схемы
echo
echo "Column 1 background = $(color_name_or_default "$column1_background" "$DEFAULT_COLUMN1_BG")"
echo "Column 1 font color = $(color_name_or_default "$column1_font_color" "$DEFAULT_COLUMN1_FG")"
echo "Column 2 background = $(color_name_or_default "$column2_background" "$DEFAULT_COLUMN2_BG")"
echo "Column 2 font color = $(color_name_or_default "$column2_font_color" "$DEFAULT_COLUMN2_FG")"
