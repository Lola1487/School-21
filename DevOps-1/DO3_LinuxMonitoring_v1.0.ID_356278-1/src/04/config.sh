#!/bin/bash

# Значения по умолчанию
DEFAULT_COLUMN1_BG=6
DEFAULT_COLUMN1_FG=1
DEFAULT_COLUMN2_BG=2
DEFAULT_COLUMN2_FG=4

# Определяем SCRIPT_DIR перед использованием
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
CONFIG_FILE="$SCRIPT_DIR/colors.conf"

# Загружаем конфигурацию если файл существует
if [[ -f "$CONFIG_FILE" ]]; then
    source "$CONFIG_FILE"
fi

# Использовать настройки из файла или дефолты
column1_background=${column1_background:-$DEFAULT_COLUMN1_BG}
column1_font_color=${column1_font_color:-$DEFAULT_COLUMN1_FG}
column2_background=${column2_background:-$DEFAULT_COLUMN2_BG}
column2_font_color=${column2_font_color:-$DEFAULT_COLUMN2_FG}

# Проверка параметров
check_param() {
    local val=$1
    local name=$2
    if ! [[ "$val" =~ ^[1-6]$ ]]; then
        echo "Ошибка: параметр цвета '$name' ($val) должен быть числом от 1 до 6."
        exit 1
    fi
}

check_param "$column1_background" "column1_background"
check_param "$column1_font_color" "column1_font_color"
check_param "$column2_background" "column2_background"
check_param "$column2_font_color" "column2_font_color"

# Запрет совпадения фона и цвета шрифта
if [ "$column1_background" -eq "$column1_font_color" ]; then
    echo "Ошибка: цвет фона и цвет шрифта для первого столбца не должны совпадать."
    exit 1
fi

if [ "$column2_background" -eq "$column2_font_color" ]; then
    echo "Ошибка: цвет фона и цвет шрифта для второго столбца не должны совпадать."
    exit 1
fi

declare -A COLOR_NAMES=(
    [1]="white"
    [2]="red"
    [3]="green"
    [4]="blue"
    [5]="purple"
    [6]="black"
)

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
