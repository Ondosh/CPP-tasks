/**
 * @file module.cpp
 * @brief Реализация функций, объявленных в module.hpp.
 *
 * Содержит определения для трёх пространств имён:
 * - mathfunc
 * - auxiliary
 * - file_work
 */

#include <vector>
#include <cstdlib>   // rand(), srand()
#include <ctime>     // time()
#include <iostream>  // cout, cerr
#include <fstream>   // ofstream, ifstream
#include <string>    // std::string
#include "module.hpp"

namespace mathfunc {

int sum_of_powers(const std::vector<int>& numbers) {
    int result = 0;
    for (int num : numbers) {
        result += num * num;  // Квадрат числа
    }
    return result;
}

}

namespace auxiliary {

std::vector<int> random_vector(int n) {
    // Инициализация генератора случайных чисел
    std::srand(time(0));

    std::vector<int> nums;
    nums.reserve(n);  // Оптимизация: избегаем лишних реаллокаций

    for (int i = 0; i < n; ++i) {
        // Генерируем число от 1 до 10 включительно
        int random_num = std::rand() % 10 + 1;
        nums.push_back(random_num);
    }
    return nums;
}

void print_vector_by_10(const std::vector<int>& vec) {
    if (vec.empty()) {
        std::cout << "(пустой массив)\n";
        return;
    }

    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
        // Добавляем пробел, если это не последний элемент в строке
        if ((i + 1) % 10 == 0) {
            std::cout << '\n';  // Перенос после 10-го, 20-го и т.д.
        } else if (i + 1 < vec.size()) {
            std::cout << " ";
        }
    }
    // Если последняя строка неполная — завершаем её переводом строки
    if (vec.size() % 10 != 0) {
        std::cout << '\n';
    }
}

} // namespace auxiliary

namespace file_work {

bool save_vector_to_file(const std::vector<int>& vec, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл для записи: " << filename << "\n";
        return false;
    }

    for (const int& num : vec) {
        file << num << '\n';
    }

    // Проверка на ошибки при записи
    if (file.fail()) {
        std::cerr << "Ошибка: сбой при записи в файл: " << filename << "\n";
        return false;
    }

    file.close();
    return true;
}

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

    // Проверка состояния потока после чтения
    if (file.bad()) {
        std::cerr << "Ошибка: критическая ошибка ввода/вывода при чтении " << filename << "\n";
    } else if (file.fail() && !file.eof()) {
        // Например, встречена буква вместо числа
        std::cerr << "Предупреждение: некорректные данные в файле " << filename << " (чтение остановлено)\n";
    }

    file.close();
    return vec;
}

} // namespace file_work