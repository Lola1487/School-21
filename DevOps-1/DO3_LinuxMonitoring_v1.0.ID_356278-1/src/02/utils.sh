#!/bin/bash

kb_to_gb() {
    local kb=$1
    echo "scale=3; $kb/1024/1024" | bc
}

kb_to_mb() {
    local kb=$1
    echo "scale=2; $kb/1024" | bc
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
