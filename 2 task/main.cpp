#include <iostream>
#include <vector>
#include <cstdlib>  // для rand()
#include <ctime>    // для time()
#include "module.hpp"

int main() {
    using namespace std;
    using namespace mathfunc;

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