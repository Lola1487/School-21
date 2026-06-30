 #!/bin/bash

# Получаем hostname
HOSTNAME=$(hostname)

# Получаем временную зону
if command -v timedatectl &>/dev/null; then
    TZ_NAME=$(timedatectl show -p Timezone --value)
else
    TZ_NAME=$(cat /etc/timezone 2>/dev/null || echo "Unknown")
fi

# Получаем смещение UTC
UTC_OFFSET=$(date +%z)
sign="${UTC_OFFSET:0:1}"
hours="${UTC_OFFSET:1:2}"
minutes="${UTC_OFFSET:3:2}"

# Рассчитываем смещение в часах с десятичной дробью
if [ "$minutes" != "00" ]; then
    offset=$(echo "scale=2; $hours + $minutes/60" | bc)
else
    offset=$hours
fi

# Форматируем смещение
if [ "$sign" == "-" ]; then
    TIMEZONE="$TZ_NAME UTC $sign$offset"
else
    TIMEZONE="$TZ_NAME UTC +$offset"
fi

# Получаем пользователя
USER=$(whoami)

# Получаем информацию об ОС
if [ -f /etc/os-release ]; then
    OS_NAME=$(grep "^PRETTY_NAME=" /etc/os-release | cut -d= -f2- | tr -d '"')
else
    OS_NAME=$(uname -s)
fi
OS="$OS_NAME"

# Получаем дату и время
DATE=$(date +"%d %b %Y %H:%M:%S")

# Получаем uptime
UPTIME=$(uptime -p | sed 's/up //')
UPTIME_SEC=$(awk '{print int($1)}' /proc/uptime)

# Получаем IP и маску сети
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

# Если IP не найден, используем альтернативный метод
if [ -z "$IP" ]; then
    IP=$(hostname -I 2>/dev/null | awk '{print $1}' | head -1)
    MASK="255.255.255.0"  # значение по умолчанию
fi

# Получаем шлюз по умолчанию
GATEWAY=$(ip route | grep default | head -n1 | awk '{print $3}' 2>/dev/null)

# Получаем информацию о памяти
MemTotal_kb=$(grep MemTotal /proc/meminfo | awk '{print $2}')
MemFree_kb=$(grep MemFree /proc/meminfo | awk '{print $2}')
Buffers_kb=$(grep Buffers /proc/meminfo | awk '{print $2}')
Cached_kb=$(grep ^Cached /proc/meminfo | awk '{print $2}')

# Рассчитываем используемую память
MemUsed_kb=$((MemTotal_kb - MemFree_kb - Buffers_kb - Cached_kb))

# Конвертируем в GB
RAM_TOTAL=$(kb_to_gb $MemTotal_kb)
RAM_USED=$(kb_to_gb $MemUsed_kb)
RAM_FREE=$(kb_to_gb $MemFree_kb)

# Получаем информацию о дисковом пространстве
space_root_kb=$(df --block-size=1K / 2>/dev/null | awk 'NR==2 {print $2}' | sed 's/K//')
space_root_used_kb=$(df --block-size=1K / 2>/dev/null | awk 'NR==2 {print $3}' | sed 's/K//')
space_root_free_kb=$(df --block-size=1K / 2>/dev/null | awk 'NR==2 {print $4}' | sed 's/K//')

# Конвертируем в MB
SPACE_ROOT=$(kb_to_mb $space_root_kb)
SPACE_ROOT_USED=$(kb_to_mb $space_root_used_kb)
SPACE_ROOT_FREE=$(kb_to_mb $space_root_free_kb)
