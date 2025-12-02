/**
 * @file main.cpp
 * @brief Главная программа: интерактивный интерфейс для вычисления суммы квадратов.
 *
 * Позволяет пользователю:
 * - либо сгенерировать случайный массив (числа от 1 до 10),
 * - либо загрузить массив из файла.
 *
 * После вычисления выводит результат и предлагает сохранить массив.
 */

#include <iostream>
#include <vector>
#include <cstdlib>   // rand(), srand()
#include <ctime>     // time()
#include <cassert>   // assert
#include <string>    // std::string
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
         << "Ваш выбор (1 или 2): ";

    int mode;
    if (!(cin >> mode) || (mode != 1 && mode != 2)) {
        cerr << "Ошибка: нужно ввести 1 или 2.\n";
        return 1;
    }

    vector<int> nums;

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