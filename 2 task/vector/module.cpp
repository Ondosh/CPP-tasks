// Реализация математических функций модуля

#include <vector>
#include "module.hpp"
#include <ctime>
#include <iostream>
#include <fstream>

namespace mathfunc {

    /**
     * @brief Вычисляет сумму квадратов всех элементов вектора целых чисел.
     * @param numbers — константная ссылка на вектор целых чисел
     * @return Сумма квадратов элементов вектора (тип int)
     * @pre Вектор может быть пустым — в этом случае возвращается 0.
     * @post Результат всегда неотрицателен (>= 0).
     * @example
     * std::vector<int> v = {2, 3, 4};
     * int s = sum_of_powers(v); // s == 4 + 9 + 16 == 29
     */
    int sum_of_powers(const std::vector<int>& numbers) {
        int result = 0;
        for (int num : numbers) {
            result += num * num;
        }
        return result;
    }
} 

namespace auxiliary {
    std::vector<int> random_vector(int n) {
        using namespace std;

        srand((time(0)));

        vector<int> nums;

        for (size_t i = 0; i < n; i++)
        {
            int random_num = rand() % 10 + 1;  // rand() % 10 даёт 0–9, +1 → 1–10
            nums.push_back(random_num);
        }
        
        return nums;
    }

    void print_vector_by_10(const std::vector<int>& vec) {
        for (size_t i = 0; i < vec.size(); ++i) {
            std::cout << vec[i] << " ";

            // После каждого 10-го элемента (индексы 9, 19, 29, ...) — перенос строки
            if ((i + 1) % 10 == 0) {
                std::cout << std::endl;
            }
        }
    }
}

namespace file_work {
    /**
     * @brief Сохраняет вектор целых чисел в текстовый файл (по одному числу на строке).
     * @param vec — вектор для сохранения
     * @param filename — имя файла
     * @return true при успехе, false при ошибке открытия файла
     */
    bool save_vector_to_file(const std::vector<int>& vec, const std::string& filename) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Ошибка: не удалось открыть файл для записи: " << filename << "\n";
            return false;
        }

        for (const int& num : vec) {
            file << num << '\n';
        }

        file.close();
        return true;
    }
    
    /**
     * @brief Загружает вектор целых чисел из текстового файла (по одному числу на строке).
     * Пропускает пустые строки, останавливается при первой ошибке формата.
     * @param filename — имя файла
     * @return вектор прочитанных чисел (пустой, если файл не найден или ошибка)
     */
    std::vector<int> load_vector_from_file(const std::string& filename) {
        std::ifstream file(filename);
        std::vector<int> vec;

        if (!file.is_open()) {
            std::cerr << "Ошибка: не удалось открыть файл для чтения: " << filename << "\n";
            return vec; // пустой вектор
        }

        int num;
        while (file >> num) {
            vec.push_back(num);
        }

        // Проверим, не произошла ли ошибка чтения (например, буква вместо числа)
        if (file.bad()) {
            std::cerr << "Ошибка: сбой при чтении файла " << filename << "\n";
        }
        // Если file.eof() — всё в порядке, просто конец файла
        // Если file.fail() (но не bad) — например, "abc" вместо числа → игнорируем остаток

        file.close();
        return vec;
    }        
}
