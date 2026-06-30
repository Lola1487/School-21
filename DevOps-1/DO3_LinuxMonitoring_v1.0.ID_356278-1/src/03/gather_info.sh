#!/bin/bash

# Утилиты для преобразований
prefix_to_mask() {
  local prefix=$1
  local i mask=""
  local full_octets=$((prefix/8))
  local partial_bits=$((prefix%8))
  for ((i=0; i<4; i++)); do
    if (( i < full_octets )); then
      mask+="255"
    elif (( i == full_octets )); then
      if (( partial_bits == 0 )); then
        mask+="0"
      else
        mask+=$((256 - 2**(8-partial_bits)))
      fi
    else
      mask+="0"
    fi
    if (( i < 3 )); then
      mask+="."
    fi
  done
  echo "$mask"
}

kb_to_gb() {
  echo "scale=3; $1/1024/1024" | bc
}

kb_to_mb() {
  echo "scale=2; $1/1024" | bc
}

# Массивы с цветами
declare -A BG_COLORS=(
  [1]="107"  # white background
  [2]="41"   # red background
  [3]="42"   # green background
  [4]="44"   # blue background
  [5]="45"   # purple background
  [6]="40"   # black background
)

declare -A FG_COLORS=(
  [1]="97"   # white font
  [2]="91"   # red font
  [3]="92"   # green font
  [4]="94"   # blue font
  [5]="95"   # purple font
  [6]="90"   # black font
)

# Функция для цветного вывода
color_echo() {
  local label=$1
  local value=$2
  local label_style="\033[${BG_COLORS[$bg_label]};${FG_COLORS[$fg_label]}m"
  local value_style="\033[${BG_COLORS[$bg_value]};${FG_COLORS[$fg_value]}m"
  local reset="\033[0m"
  printf "${label_style}%-12s${reset}${value_style} = %s${reset}\n" "$label" "$value"
}

# Сбор информации о системе
HOSTNAME=$(hostname)

if command -v timedatectl &>/dev/null; then
  TZ_NAME=$(timedatectl show -p Timezone --value)
else
  TZ_NAME=$(cat /etc/timezone 2>/dev/null || echo "Unknown")
fi

# Упрощаем форматирование времени
UTC_OFFSET=$(date +%z)
TIMEZONE="$TZ_NAME UTC ${UTC_OFFSET:0:3}:${UTC_OFFSET:3:2}"

USER=$(whoami)

if [ -f /etc/os-release ]; then
  OS_NAME=$(grep "^PRETTY_NAME=" /etc/os-release | cut -d= -f2- | tr -d '"')
else
  OS_NAME=$(uname -s)
fi
OS="$OS_NAME"

DATE=$(date +"%d %b %Y %H:%M:%S")
UPTIME=$(uptime -p | sed 's/up //')
UPTIME_SEC=$(awk '{print int($1)}' /proc/uptime)

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

MemTotal_kb=$(grep MemTotal /proc/meminfo | awk '{print $2}')
MemFree_kb=$(grep MemFree /proc/meminfo | awk '{print $2}')
Buffers_kb=$(grep Buffers /proc/meminfo | awk '{print $2}')
Cached_kb=$(grep ^Cached /proc/meminfo | awk '{print $2}')
MemUsed_kb=$((MemTotal_kb - MemFree_kb - Buffers_kb - Cached_kb))

RAM_TOTAL=$(kb_to_gb $MemTotal_kb)
RAM_USED=$(kb_to_gb $MemUsed_kb)
RAM_FREE=$(kb_to_gb $MemFree_kb)

space_root_kb=$(df --block-size=1K / 2>/dev/null | awk 'NR==2 {print $2}' | sed 's/K//')
space_root_used_kb=$(df --block-size=1K / 2>/dev/null | awk 'NR==2 {print $3}' | sed 's/K//')
space_root_free_kb=$(df --block-size=1K / 2>/dev/null | awk 'NR==2 {print $4}' | sed 's/K//')

SPACE_ROOT=$(kb_to_mb $space_root_kb)
SPACE_ROOT_USED=$(kb_to_mb $space_root_used_kb)
SPACE_ROOT_FREE=$(kb_to_mb $space_root_free_kb)
