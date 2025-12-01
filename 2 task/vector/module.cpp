// Реализация математических функций модуля

#include <vector>
#include "module.hpp"
#include <ctime>
#include <iostream>

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