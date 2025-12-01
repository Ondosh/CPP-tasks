#include "module.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

namespace mathfunc {
    int sum_of_powers(const int* arr, size_t size) {
        if (!arr || size == 0) return 0;
        int result = 0;
        for (size_t i = 0; i < size; ++i) {
            result += arr[i] * arr[i];
        }
        return result;
    }
}

namespace auxiliary {
    int* random_array(int n, size_t& out_size) {
        if (n <= 0) {
            out_size = 0;
            return nullptr;
        }

        int* arr = new (std::nothrow) int[n];
        if (!arr) {
            out_size = 0;
            return nullptr;
        }

        for (int i = 0; i < n; ++i) {
            arr[i] = std::rand() % 10 + 1; // 1–10
        }

        out_size = static_cast<size_t>(n);
        return arr;
    }

    void print_array_by_10(const int* arr, size_t size) {
        if (!arr) return;
        for (size_t i = 0; i < size; ++i) {
            std::cout << arr[i] << " ";
            if ((i + 1) % 10 == 0) {
                std::cout << std::endl;
            }
        }
        if (size % 10 != 0) {
            std::cout << std::endl;
        }
    }
}

namespace file_work {
    bool save_array_to_file(const int* arr, size_t size, const std::string& filename) {
        if (!arr) return false;
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Ошибка: не удалось открыть файл для записи: " << filename << "\n";
            return false;
        }
        for (size_t i = 0; i < size; ++i) {
            file << arr[i] << '\n';
        }
        return true;
    }

    int* load_array_from_file(const std::string& filename, size_t& out_size) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Ошибка: не удалось открыть файл: " << filename << "\n";
            out_size = 0;
            return nullptr;
        }

        // Сначала подсчитаем количество чисел
        int temp;
        size_t count = 0;
        while (file >> temp) {
            ++count;
        }
        file.clear(); // сбросить флаг eof
        file.seekg(0); // вернуться в начало

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