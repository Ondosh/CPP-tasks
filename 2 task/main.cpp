#include <iostream>
#include <vector>
#include <cstdlib>  // для rand()
#include <ctime>    // для time()
#include <cassert>  // для assert
#include "module.hpp"

int main() {
    using namespace std;
    using namespace mathfunc;

    // Проверка правильной работы функции
    assert(sum_of_powers({}) == 0);
    assert(sum_of_powers({3}) == 9);        // 3^2 = 9
    assert(sum_of_powers({1, 2, 3}) == 14); // 1^2 + 2^2 + 3^2 = 1 + 4 + 9 = 14
    assert(sum_of_powers({2, 2}) == 8);     // 4 + 4 = 8
    assert(sum_of_powers({1, 1, 1, 1}) == 4);

    // Объявляем вектор чисел
    vector<int> nums;

    // Инициализация генератора случайных чисел
    srand((time(0)));

    // Генерация 5 случайных чисел от 1 до 10
    for (int i = 0; i < 5; ++i) {
        int random_num = rand() % 10 + 1;  // rand() % 10 даёт 0–9, +1 → 1–10
        nums.push_back(random_num);
    }

    // Вычисление результата
    int result = sum_of_powers(nums);

    // Вывод чисел (опционально)
    cout << "Случайные числа: ";
    for (size_t i = 0; i < nums.size(); ++i) {
        if (i > 0) cout << ", ";
        cout << nums[i];
    }
    cout << "\nРезультат: " << result << endl;

    return 0;
}