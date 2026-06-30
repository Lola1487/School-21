#!/bin/bash

DIR="$1"
START_TIME=$(date +%s.%N)

# Общее количество папок
total_folders=$(find "$DIR" -type d 2>/dev/null | wc -l)

# Топ-5 папок по размеру
mapfile -t top5_folders < <(
    du -sb "$DIR"*/ 2>/dev/null | sort -nr | head -5
)

# Общее количество файлов
total_files=$(find "$DIR" -type f 2>/dev/null | wc -l)

# Количество файлов по типам
conf_files=$(find "$DIR" -type f -name "*.conf" 2>/dev/null | wc -l)
log_files=$(find "$DIR" -type f -name "*.log" 2>/dev/null | wc -l)
exec_files=$(find "$DIR" -type f -executable 2>/dev/null | wc -l)
text_files=$(find "$DIR" -type f -exec sh -c 'file -b "$1" | grep -q text' _ {} \; -print 2>/dev/null | wc -l)
archive_files=$(find "$DIR" -type f \( -name "*.zip" -o -name "*.tar" -o -name "*.gz" -o -name "*.bz2" -o -name "*.xz" -o -name "*.7z" -o -name "*.rar" \) 2>/dev/null | wc -l)
symlinks=$(find "$DIR" -type l 2>/dev/null | wc -l)

# Топ-10 файлов по размеру
mapfile -t top10_files < <(
    find "$DIR" -type f -exec du -b {} + 2>/dev/null | sort -nr | head -10 | while read size path; do
        # Определяем тип файла
        if [[ "$path" == *.exe ]] || [[ "$path" == *.bin ]] || [[ -x "$path" ]]; then
            type="executable"
        elif [[ "$path" == *.log ]]; then
            type="log"
        elif [[ "$path" == *.conf ]]; then
            type="configuration"
        elif [[ "$path" == *.txt ]] || [[ "$path" == *.md ]]; then
            type="text"
        elif [[ "$path" == *.zip ]] || [[ "$path" == *.tar ]] || [[ "$path" == *.gz ]] || \
             [[ "$path" == *.bz2 ]] || [[ "$path" == *.xz ]] || [[ "$path" == *.7z ]] || [[ "$path" == *.rar ]]; then
            type="archive"
        else
            type="unknown"
        fi

        # Форматируем размер
        if [ $size -ge 1073741824 ]; then
            human_size=$(echo "scale=2; $size/1073741824" | bc)GB
        elif [ $size -ge 1048576 ]; then
            human_size=$(echo "scale=2; $size/1048576" | bc)MB
        elif [ $size -ge 1024 ]; then
            human_size=$(echo "scale=2; $size/1024" | bc)KB
        else
            human_size="${size}B"
        fi

        echo "$path, $human_size, $type"
    done
)

# Топ-10 исполняемых файлов по размеру с MD5
mapfile -t top10_execs < <(
    find "$DIR" -type f -executable -exec du -b {} + 2>/dev/null | sort -nr | head -10 | while read size path; do
        # Вычисляем MD5
        if command -v md5sum >/dev/null 2>&1; then
            md5=$(md5sum "$path" 2>/dev/null | cut -d' ' -f1)
        elif command -v md5 >/dev/null 2>&1; then
            md5=$(md5 -q "$path" 2>/dev/null)
        else
            md5="MD5_NOT_AVAILABLE"
        fi

        # Форматируем размер
        if [ $size -ge 1073741824 ]; then
            human_size=$(echo "scale=2; $size/1073741824" | bc)GB
        elif [ $size -ge 1048576 ]; then
            human_size=$(echo "scale=2; $size/1048576" | bc)MB
        elif [ $size -ge 1024 ]; then
            human_size=$(echo "scale=2; $size/1024" | bc)KB
        else
            human_size="${size}B"
        fi

        echo "$path, $human_size, $md5"
    done
)

END_TIME=$(date +%s.%N)
duration=$(echo "$END_TIME - $START_TIME" | bc -l)
