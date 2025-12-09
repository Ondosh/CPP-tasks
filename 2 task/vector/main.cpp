/**
 * @file main.cpp
 * @brief Главная программа: интерактивный интерфейс для вычисления суммы квадратов.
 *
 * Позволяет пользователю:
 * - либо сгенерировать случайный массив (числа от 1 до 10),
 * - либо загрузить массив из файла,
 * - либо ввести массив с клавиатуры.
 *
 * После вычисления выводит результат и предлагает сохранить массив.
 */

#include <iostream>
#include <vector>
#include <cstdlib>   // rand(), srand()
#include <ctime>     // time()
#include <cassert>   // assert
#include <string>    // std::string
#include <limits>    // numeric_limits
#include "module.hpp"

int main() {
    using namespace std;
    using namespace mathfunc;
    using namespace auxiliary;
    using namespace file_work;

    // Тесты (базовая проверка корректности)
    assert(sum_of_powers({}) == 0);
    assert(sum_of_powers({3}) == 9);
    assert(sum_of_powers({1, 2, 3}) == 14);   // 1² + 2² + 3² = 1 + 4 + 9 = 14
    assert(sum_of_powers({2, 2}) == 8);       // 4 + 4 = 8
    assert(sum_of_powers({1, 1, 1, 1}) == 4); // 1×4 = 4

    // Интерактивный ввод режима работы
    cout << "Выберите режим работы:\n"
         << "1 - сгенерировать случайный массив (ввести длину)\n"
         << "2 - загрузить массив из файла\n"
         << "3 - ввести массив с клавиатуры\n"
         << "Ваш выбор (1, 2 или 3): ";

    int mode;
    if (!(cin >> mode) || (mode < 1 || mode > 3)) {
        cerr << "Ошибка: нужно ввести 1, 2 или 3.\n";
        return 1;
    }

    vector<int> nums;
    
    // Инициализация генератора случайных чисел
    std::srand(time(0));

    // Получение данных
    if (mode == 1) {
        // Генерация случайного массива
        const int MAX_SIZE = 1'000'000;
        int n;
        cout << "\nСколько чисел сгенерировать? (1–" << MAX_SIZE << "): ";
        if (!(cin >> n) || n <= 0 || n > MAX_SIZE) {
            cerr << "Ошибка: некорректное количество чисел.\n";
            return 1;
        }

        nums = random_vector(n);

    } else if (mode == 2) {
        // Загрузка из файла
        string filename;
        cout << "\nВведите имя файла для загрузки: ";
        cin >> filename;

        nums = load_vector_from_file(filename);
        if (nums.empty()) {
            cerr << "Ошибка: не удалось загрузить данные из файла (файл не найден, пуст или содержит ошибки).\n";
            return 1;
        }

        cout << "\nЗагружено " << nums.size() << " чисел из файла \"" << filename << "\".\n";
        
    } else if (mode == 3) {
        // Ввод с клавиатуры
        int n;
        cout << "Сколько чисел вы хотите ввести? (введите количество): ";
        if (!(cin >> n) || n <= 0) {
            cerr << "Ошибка: некорректное количество чисел.\n";
            return 1;
        }
        
        const int MAX_SIZE_KEYBOARD = 10000; // Ограничение для ручного ввода
        if (n > MAX_SIZE_KEYBOARD) {
            cerr << "Ошибка: для ручного ввода максимальное количество - " 
                 << MAX_SIZE_KEYBOARD << " чисел.\n";
            return 1;
        }
        
        cout << "Введите " << n << " целых чисел (через пробел или каждое с новой строки):\n";
        
        nums.resize(n);
        for (int i = 0; i < n; i++) {
            if (!(cin >> nums[i])) {
                cerr << "Ошибка: некорректный ввод числа " << i + 1 << ".\n";
                return 1;
            }
        }
        
        cout << "\nУспешно введено " << n << " чисел.\n";
    }

    // Вычисление и вывод результата
    int result = sum_of_powers(nums);

    cout << "\nМассив:\n";
    print_vector_by_10(nums);
    cout << "Результат (сумма квадратов): " << result << "\n\n";

    // Сохранение (по желанию)
    string save_filename;
    cout << "Сохранить этот массив в файл? (введите имя файла или '-' чтобы пропустить): ";
    cin >> save_filename;

    if (save_filename != "-") {
        if (save_vector_to_file(nums, save_filename)) {
            cout << "Массив успешно сохранён в файл \"" << save_filename << "\".\n";
        } else {
            cerr << "Предупреждение: не удалось сохранить файл.\n";
        }
    }

    return 0;
}