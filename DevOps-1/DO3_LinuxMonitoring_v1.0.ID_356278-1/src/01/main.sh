#!/bin/bash

# Определяем директорию, где находится этот скрипт
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Подключаем check_params.sh из этой же папки
source "$SCRIPT_DIR/check_params.sh"

# Проверяем количество параметров
if [ $# -ne 1 ]; then
    echo "Ошибка: скрипт должен запускаться с одним параметром."
    exit 1
fi

check_param "$1"

echo "Введённый параметр: $1"

