// Главная программа: интерфейс пользователя и управление логикой.
// Поддерживает три режима:
//   1) Генерация случайного массива
//   2) Загрузка массива из файла
//   3) Ввод массива с клавиатуры
// После обработки выводит сумму квадратов элементов и опционально сохраняет массив.

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <string>
#include <limits>
#include <stdexcept>
#include "module.hpp"

int main() {
    using namespace std;
    using namespace mathfunc;
    using namespace auxiliary;
    using namespace file_work;

    // Тесты функции sum_of_powers
    {
        assert(mathfunc::sum_of_powers<int>(nullptr, 0) == 0);           // пустой массив
        int a1[] = {3};
        assert(sum_of_powers(a1, 1) == 9);               // 3^2 = 9
        int a2[] = {1, 2, 3};
        assert(sum_of_powers(a2, 3) == 14);              // 1+4+9 = 14
        int a3[] = {2, 2};
        assert(sum_of_powers(a3, 2) == 8);               // 4+4 = 8
        int a4[] = {1, 1, 1, 1};
        assert(sum_of_powers(a4, 4) == 4);               // 4×1 = 4
    }

    int* nums = nullptr;
    size_t count = 0;
    string filename;
    int mode = 0;

    try {
        cout << "Выберите режим работы:\n"
             << "1 - сгенерировать случайный массив (ввести длину)\n"
             << "2 - загрузить массив из файла\n"
             << "3 - ввести массив с клавиатуры\n"
             << "Ваш выбор (1, 2 или 3): " << flush;

        if (!(cin >> mode) || (mode < 1 || mode > 3)) {
            throw invalid_argument("Нужно ввести 1, 2 или 3.");
        }

        if (mode == 1) {
            // Генерация случайного массива (числа от 1 до 10)
            srand(time(0));

            const int MAX_SIZE = 1'000'000;
            int n;
            cout << "\nСколько чисел сгенерировать? (1–" << MAX_SIZE << "): " << flush;
            if (!(cin >> n) || n <= 0 || n > MAX_SIZE) {
                throw invalid_argument("Некорректное количество чисел.");
            }

            nums = auxiliary::random_array<int>(n, count);
            if (!nums) {
                throw runtime_error("Не удалось выделить память для массива.");
            }

        } else if (mode == 2) {
            // Загрузка массива из файла (по одному числу на строку)
            cout << "\nВведите имя файла для загрузки: " << flush;
            cin >> filename;

            nums = load_array_from_file(filename, count);
            if (!nums) {
                throw runtime_error("Не удалось загрузить данные из файла '" + filename + "'.");
            }

            cout << "\nЗагружено " << count << " чисел из файла \"" << filename << "\".\n";
            
        } else if (mode == 3) {
            // Ввод массива с клавиатуры
            cout << "\n=== Режим ввода с клавиатуры ===\n";
            
            int n;
            cout << "Сколько чисел вы хотите ввести? (введите количество): " << flush;
            if (!(cin >> n) || n <= 0) {
                throw invalid_argument("Некорректное количество чисел.");
            }
            
            const int MAX_SIZE_KEYBOARD = 10000; // Ограничение для ручного ввода
            if (n > MAX_SIZE_KEYBOARD) {
                throw invalid_argument("Для ручного ввода максимальное количество - " + 
                                     to_string(MAX_SIZE_KEYBOARD) + " чисел.");
            }
            
            count = n;
            nums = new int[count];
            
            cout << "Введите " << n << " целых чисел (через пробел или каждое с новой строки):" << endl;
            
            for (size_t i = 0; i < count; i++) {
                if (!(cin >> nums[i])) {
                    throw invalid_argument("Некорректный ввод числа " + to_string(i + 1) + ".");
                }
            }
            
            // Очистка буфера после ввода
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            cout << "\nУспешно введено " << n << " чисел.\n";
        }

        // Вычисление суммы квадратов
        int result = sum_of_powers(nums, count);

        // Вывод результата и массива (по 10 элементов в строке)
        cout << "\nМассив:\n";
        print_array_by_10(nums, count);
        cout << "\nРезультат (сумма квадратов): " << result << "\n\n";

        // Сохранение массива (если был режим 1 или 3)
        if (mode == 1 || mode == 3) {
            string save_filename;
            cout << "Сохранить этот массив в файл? (введите имя файла или '-' чтобы пропустить): " << flush;
            cin >> save_filename;

            if (save_filename != "-") {
                try {
                    if (save_array_to_file(nums, count, save_filename)) {
                        cout << "Массив успешно сохранён в файл \"" << save_filename << "\".\n";
                    } else {
                        cerr << "Предупреждение: не удалось сохранить файл.\n";
                    }
                } catch (const exception& e) {
                    cerr << "Ошибка при сохранении: " << e.what() << endl;
                }
            }
        }

    } catch (const exception& e) {
        // Освобождаем память при возникновении исключения
        delete[] nums;
        nums = nullptr;
        
        cerr << "Ошибка: " << e.what() << "\n";
        return 1;
    } catch (...) {
        // Обработка любых других исключений
        delete[] nums;
        nums = nullptr;
        
        cerr << "Неизвестная ошибка.\n";
        return 1;
    }

    // Очистка выделенной памяти
    delete[] nums;
    nums = nullptr;

    return 0;
}