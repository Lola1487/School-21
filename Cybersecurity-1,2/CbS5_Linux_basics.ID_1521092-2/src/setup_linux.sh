#!/bin/bash

# Проверка на root
if [ "$(id -u)" -ne 0 ]; then
    echo "This script must be run as root! Use: sudo $0"
    exit 1
fi

echo "=== Linux System Configuration Script ==="

# 1. Создание группы default_users и пользователя user с опцией -g
echo "[1] Creating group default_users and user user..."
groupadd default_users 2>/dev/null
useradd -m -g default_users -s /bin/bash user 2>/dev/null
echo "user:password123" | chpasswd

# 2. Создание группы secret_users и пользователей secret_agent, secret_spy, secret_boss с опцией -g
echo "[2] Creating group secret_users and secret agents..."
groupadd secret_users 2>/dev/null
for u in secret_agent secret_spy secret_boss; do
    useradd -m -g secret_users -s /bin/bash "$u" 2>/dev/null
    echo "$u:secretpass123" | chpasswd
done

# 3. Права 770 на домашние директории secret_users
echo "[3] Setting 770 permissions on /home/secret_*..."
chmod 770 /home/secret_agent /home/secret_spy /home/secret_boss
chgrp secret_users /home/secret_agent /home/secret_spy /home/secret_boss

# 4. Права 777 на /var
echo "[4] Setting 777 permissions on /var..."
chmod 777 /var

# 5. Установка и проверка apache2
echo "[5] Installing and checking apache2..."
apt-get update -qq
apt-get install -y apache2
systemctl start apache2
systemctl enable apache2
systemctl status apache2 --no-pager

# 6. Sudo без пароля для default_users
echo "[6] Configuring sudo without password for default_users..."
echo "%default_users ALL=(ALL) NOPASSWD: ALL" > /etc/sudoers.d/default_users_nopasswd
chmod 440 /etc/sudoers.d/default_users_nopasswd

echo "=== Done! ==="
