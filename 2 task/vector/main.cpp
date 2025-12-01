#include <iostream>
#include <vector>
#include <cstdlib>  // для rand()
#include <ctime>    // для time()
#include <cassert>  // для assert
#include "module.hpp"

int main() {
    using namespace std;
    using namespace mathfunc;
    using namespace auxiliary;
    
    // Проверка правильной работы функции
    assert(sum_of_powers({}) == 0);
    assert(sum_of_powers({3}) == 9);        // 3^2 = 9
    assert(sum_of_powers({1, 2, 3}) == 14); // 1^2 + 2^2 + 3^2 = 1 + 4 + 9 = 14
    assert(sum_of_powers({2, 2}) == 8);     // 4 + 4 = 8
    assert(sum_of_powers({1, 1, 1, 1}) == 4);

    // Инициализация генератора случайных чисел
    srand((time(0)));
    int n = 0;

    cout << "Сколько чисел вы хотите видеть в массиве? Введите целое число: ";
    cin >> n;

    // Инициализация вектора и создание массива случайных чисел с указанной пользователем длиной
    vector<int> nums = random_vector(n);

    // Вычисление результата
    int result = sum_of_powers(nums);

    // Вывод чисел
    cout << "Случайные числа: ";
    print_vector_by_10(nums);
    cout << "\nРезультат: " << result << endl;

    return 0;
}