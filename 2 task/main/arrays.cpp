// Author: Ondosh
// Реализация функций модуля для работы с массивами целых чисел
// Соответствует объявлениям в module.hpp

#include "arrays.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

namespace file_work {
    /**
     * @brief Сохраняет массив в текстовый файл
     * @param arr Указатель на массив для сохранения
     * @param size Количество элементов в массиве
     * @param filename Имя файла для сохранения
     * @return true если сохранение успешно, false в случае ошибки
     * @note Каждый элемент сохраняется на отдельной строке
     */
    bool save_array_to_file(const int* arr, size_t size, const std::string& filename) {
        // Сохраняет массив в файл (по одному числу на строку)
        if (!arr) return false;
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Ошибка: не удалось открыть файл для записи: " << filename << "\n"; //throw exception
            return false;
        }
        for (size_t i = 0; i < size; ++i) {
            file << arr[i] << '\n';
        }
        return true;
    }

    /**
     * @brief Загружает массив из текстового файла
     * @param filename Имя файла для загрузки
     * @param out_size[out] Количество загруженных элементов
     * @return Указатель на новый массив или nullptr при ошибке
     * @warning Вызывающая сторона отвечает за освобождение памяти с помощью delete[]
     * @note Файл должен содержать по одному целому числу на каждой строке
     */
    int* load_array_from_file(const std::string& filename, size_t& out_size) {
        // Загружает массив из файла
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Ошибка: не удалось открыть файл: " << filename << "\n";
            out_size = 0;
            return nullptr;
        }

        // Подсчёт количества чисел
        int temp;
        size_t count = 0;
        while (file >> temp) {
            ++count;
        }
        file.clear();
        file.seekg(0); // возврат в начало

        if (count == 0) {
            out_size = 0;
            return nullptr;
        }

        int* arr = new (std::nothrow) int[count];
        if (!arr) {
            out_size = 0;
            return nullptr;
        }

        for (size_t i = 0; i < count; ++i) {
            file >> arr[i];
        }

        out_size = count;
        return arr;
    }
}