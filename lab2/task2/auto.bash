#!/bin/bash

# Список файлов для подстановки вместо FileA
files=("spinlock.c" "mutex.c" "conditional.c" "semaphor.c" "solophor.c")

# Имя целевого файла, в который копируются файлы
TARGET="queue.c"

# Числа для подстановки в аргументы программы
VALUES=(1000 10000 1000000)

# Обработка остальных файлов
for file in "${files[@]}"; do
  cp "$file" "$TARGET"
  echo "Компилируем и запускаем queue-threads для $file"
  make
  if [ $? -ne 0 ]; then
    echo "Ошибка компиляции для $file. Пропускаем этот файл."
    continue
  fi

  for VALUE in "${VALUES[@]}"; do
    echo "Запуск queue-threads для $file с аргументом $VALUE"
    time ./queue-threads "$VALUE"
  done

  echo "Завершено выполнение для $file"
done

echo "Все файлы обработаны."
