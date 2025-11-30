// Реализация математических функций модуля

#include <vector>
#include "module.hpp"

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