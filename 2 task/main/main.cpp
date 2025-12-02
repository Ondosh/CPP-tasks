// Главная программа: интерфейс пользователя и управление логикой.
// Поддерживает два режима:
//   1) Генерация случайного массива
//   2) Загрузка массива из файла
// После обработки выводит сумму квадратов элементов и опционально сохраняет массив.

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <string>
#include "module.hpp"

int main() {
    using namespace std;
    using namespace mathfunc;
    using namespace auxiliary;
    using namespace file_work;

    // Тесты функции sum_of_powers
    {
        assert(sum_of_powers(nullptr, 0) == 0);           // пустой массив
        int a1[] = {3};
        assert(sum_of_powers(a1, 1) == 9);               // 3^2 = 9
        int a2[] = {1, 2, 3};
        assert(sum_of_powers(a2, 3) == 14);              // 1+4+9 = 14
        int a3[] = {2, 2};
        assert(sum_of_powers(a3, 2) == 8);               // 4+4 = 8
        int a4[] = {1, 1, 1, 1};
        assert(sum_of_powers(a4, 4) == 4);               // 4×1 = 4
    }

    cout << "Выберите режим работы:\n"
         << "1 - сгенерировать случайный массив (ввести длину)\n"
         << "2 - загрузить массив из файла\n"
         << "Ваш выбор (1 или 2): " << flush;

    int mode;
    if (!(cin >> mode) || (mode != 1 && mode != 2)) {
        cerr << "Ошибка: нужно ввести 1 или 2.\n";
        return 1;
    }

    int* nums = nullptr;
    size_t count = 0;

    if (mode == 1) {
        // Генерация случайного массива (числа от 1 до 10)
        srand(time(0));

        const int MAX_SIZE = 1'000'000;
        int n;
        cout << "\nСколько чисел сгенерировать? (1–" << MAX_SIZE << "): " << flush;
        if (!(cin >> n) || n <= 0 || n > MAX_SIZE) {
            cerr << "Ошибка: некорректное количество чисел.\n";
            return 1;
        }
        
        nums = random_array(n, count);
        if (!nums) {
            cerr << "Ошибка: не удалось выделить память.\n";
            return 1;
        }

    } else if (mode == 2) {
        // Загрузка массива из файла (по одному числу на строку)
        string filename;
        cout << "\nВведите имя файла для загрузки: " << flush;
        cin >> filename;

        nums = load_array_from_file(filename.c_str(), count);
        if (!nums) {
            cerr << "Ошибка: не удалось загрузить данные из файла.\n";
            return 1;
        }

        cout << "\nЗагружено " << count << " чисел из файла \"" << filename << "\".\n";
    }

    // Вычисление суммы квадратов
    int result = sum_of_powers(nums, count);

    // Вывод результата и массива (по 10 элементов в строке)
    cout << "\nМассив:\n";
    print_array_by_10(nums, count);
    cout << "\nРезультат (сумма квадратов): " << result << "\n\n";

    // Сохранение сгенерированного массива (если был режим 1)
    if (mode == 1) {
        string save_filename;
        cout << "Сохранить этот массив в файл? (введите имя файла или '-' чтобы пропустить): " << flush;
        cin >> save_filename;

        if (save_filename != "-") {
            if (save_array_to_file(nums, count, save_filename)) {
                cout << "Массив успешно сохранён в файл \"" << save_filename << "\".\n";
            } else {
                cerr << "Предупреждение: не удалось сохранить файл.\n";
            }
        }
    }

    // Очистка выделенной памяти
    delete[] nums;
    nums = nullptr;

    return 0;
}