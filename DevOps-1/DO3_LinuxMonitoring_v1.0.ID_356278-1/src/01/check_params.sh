#!/bin/bash

check_param() {
  param="$1"
  if [ -z "$param" ]; then
    echo "Ошибка: параметр не передан."
    exit 1
  fi

   if [[ "$param" =~ ^-?[0-9]+([.][0-9]+)?$ ]]; then
    echo "Некорректный ввод: параметр не должен быть числом."
    exit 1
  fi
}

