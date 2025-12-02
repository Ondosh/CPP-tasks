// Author: Ondosh
// Заголовочный файл: объявления функций в трёх пространствах имён:
// - mathfunc: математические операции
// - auxiliary: вспомогательные утилиты
// - file_work: работа с файлами

#ifndef MODULE_HPP
#define MODULE_HPP

#include <string>
#include <cstddef>  // size_t

namespace mathfunc {
    // Возвращает сумму квадратов элементов массива.
    // arr — указатель на массив (может быть nullptr)
    // size — количество элементов
    int sum_of_powers(const int* arr, size_t size);
}

namespace auxiliary {
    // Генерирует массив из n случайных чисел (от 1 до 10).
    // Возвращает указатель на новый массив или nullptr при ошибке.
    // out_size — получает фактический размер массива.
    int* random_array(int n, size_t& out_size);

    // Выводит массив на экран, по 10 элементов в строке.
    void print_array_by_10(const int* arr, size_t size);
}

namespace file_work {
    // Сохраняет массив в текстовый файл (по одному числу на строку).
    // Возвращает true при успехе.
    bool save_array_to_file(const int* arr, size_t size, const std::string& filename);

    // Загружает массив из текстового файла.
    // Возвращает указатель на новый массив или nullptr при ошибке.
    // out_size — получает количество загруженных элементов.
    int* load_array_from_file(const std::string& filename, size_t& out_size);
}

#endif // MODULE_HPP