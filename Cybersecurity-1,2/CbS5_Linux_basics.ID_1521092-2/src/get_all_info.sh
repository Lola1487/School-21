#!/bin/bash

# Проверка на root
if [ "$(id -u)" -ne 0 ]; then
    echo "This script must be run as root! Use: sudo $0"
    exit 1
fi

# Создаём файл info
echo "--- System Report ---" > info
echo "Generated on: $(date)" >> info
echo "" >> info

# 1. Версия ядра и ОС
echo "--- OS and Kernel Info ---" >> info
uname -a >> info
cat /etc/os-release >> info
echo "" >> info

# 2. Список установленных пакетов (только названия и версии)
echo "--- Installed Packages ---" >> info
if command -v dpkg &> /dev/null; then
    dpkg -l | grep '^ii' | awk '{print $2 " " $3}' >> info
elif command -v rpm &> /dev/null; then
    rpm -qa --queryformat "%{NAME} %{VERSION}\n" >> info
fi
echo "" >> info

# 3. Запущенные процессы
echo "--- Running Processes ---" >> info
ps aux --sort=-%cpu >> info
echo "" >> info

# 4. Открытые порты (только LISTEN для tcp и UNCONN для udp)
echo "--- Open Ports ---" >> info
ss -tulnp 2>/dev/null | grep -E "LISTEN|UNCONN" >> info
echo "" >> info

# 5. Установка cowsay и sl
echo "--- Installing cowsay and sl ---" >> info
apt-get update -qq
apt-get install -y cowsay sl
echo "cowsay and sl installed" >> info

# 6. Создание архива
tar -cf OS_RESULT.tar info

echo "Done! OS_RESULT.tar created"
