#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

source "$SCRIPT_DIR/check_params.sh"
source "$SCRIPT_DIR/gather_info.sh"

# Проверяем параметры (функция из check_params.sh запускается при source)
# Но нам нужно установить глобальные переменные цветов
bg_label=$1
fg_label=$2
bg_value=$3
fg_value=$4

# Вывод всех значений с цветами
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
