#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Проверяем и подготавливаем аргумент
source "$SCRIPT_DIR/check_args.sh" "$@"

# Собираем информацию
source "$SCRIPT_DIR/collect_data.sh" "$DIR"

# Вывод результатов
echo "Total number of folders (including all nested ones) = $total_folders"

echo "TOP 5 folders of maximum size arranged in descending order (path and size):"
if [ ${#top5_folders[@]} -eq 0 ]; then
    echo "No folders found"
else
    i=1
    for entry in "${top5_folders[@]}"; do
        size=$(echo "$entry" | awk '{print $1}')
        path=$(echo "$entry" | cut -f2-)

        # Форматируем размер папки
        if [ $size -ge 1073741824 ]; then
            human_size=$(echo "scale=2; $size/1073741824" | bc)GB
        elif [ $size -ge 1048576 ]; then
            human_size=$(echo "scale=2; $size/1048576" | bc)MB
        elif [ $size -ge 1024 ]; then
            human_size=$(echo "scale=2; $size/1024" | bc)KB
        else
            human_size="${size}B"
        fi

        echo "$i - $path, $human_size"
        ((i++))
    done
fi

echo "Total number of files = $total_files"

echo "Number of:"
echo "Configuration files (with the .conf extension) = $conf_files"
echo "Text files = $text_files"
echo "Executable files = $exec_files"
echo "Log files (with the extension .log) = $log_files"
echo "Archive files = $archive_files"
echo "Symbolic links = $symlinks"

echo "TOP 10 files of maximum size arranged in descending order (path, size and type):"
if [ ${#top10_files[@]} -eq 0 ]; then
    echo "No files found"
else
    i=1
    for line in "${top10_files[@]}"; do
        echo "$i - $line"
        ((i++))
    done
fi

echo "TOP 10 executable files of the maximum size arranged in descending order (path, size and MD5 hash of file):"
if [ ${#top10_execs[@]} -eq 0 ]; then
    echo "No executable files found"
else
    i=1
    for line in "${top10_execs[@]}"; do
        echo "$i - $line"
        ((i++))
    done
fi

printf "Script execution time (in seconds) = %.1f\n" "$duration"
