#!/bin/bash

color_echo() {
    local label="$1"
    local value="$2"
    local label_style="\033[${BG_COLORS[$column1_background]};${FG_COLORS[$column1_font_color]}m"
    local value_style="\033[${BG_COLORS[$column2_background]};${FG_COLORS[$column2_font_color]}m"
    local reset="\033[0m"
    printf "${label_style}%-12s${reset}${value_style} = %s${reset}\n" "$label" "$value"
}

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
    local kb=$1
    echo "scale=3; $kb/1024/1024" | bc
}

kb_to_mb() {
    local kb=$1
    echo "scale=2; $kb/1024" | bc
}

# Функция для вывода информации о цветовой схеме
color_name_or_default() {
    local val=$1
    local def=$2
    if [[ "$val" == "$def" ]]; then
        echo "default (${COLOR_NAMES[$val]})"
    else
        echo "$val (${COLOR_NAMES[$val]})"
    fi
}
