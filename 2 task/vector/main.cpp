#include <iostream>
#include <vector>
#include <cstdlib>   // для rand(), srand()
#include <ctime>     // для time()
#include <cassert>   // для assert
#include <string>    // для std::string
#include "module.hpp"

int main() {
    using namespace std;
    using namespace mathfunc;
    using namespace auxiliary;
    using namespace file_work;

    // Проверка корректности функции
    assert(sum_of_powers({}) == 0);
    assert(sum_of_powers({3}) == 9);
    assert(sum_of_powers({1, 2, 3}) == 14);
    assert(sum_of_powers({2, 2}) == 8);
    assert(sum_of_powers({1, 1, 1, 1}) == 4);

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

    if (mode == 1) {
        // Генерация случайного массива
        srand(time(0));

        const int MAX_SIZE = 1'000'000;
        int n;
        cout << "\nСколько чисел сгенерировать? (1–" << MAX_SIZE << "): ";
        if (!(cin >> n) || n <= 0 || n > MAX_SIZE) {
            cerr << "Ошибка: некорректное количество чисел.\n";
            return 1;
        }

        nums = random_vector(n); 

        cout << "\nСлучайный массив сгенерирован (" << nums.size() << " элементов).\n";

    } else if (mode == 2) {
        // Загрузка из файла
        string filename;
        cout << "\nВведите имя файла для загрузки: ";
        cin >> filename;

        nums = load_vector_from_file(filename);
        if (nums.empty()) {
            cerr << "Ошибка: не удалось загрузить данные из файла (файл не найден или пуст).\n";
            return 1;
        }

        cout << "\nЗагружено " << nums.size() << " чисел из файла \"" << filename << "\".\n";
    }

    // Вычисление результата
    int result = sum_of_powers(nums);

    // Вывод массива по 10 элементов в строке
    cout << "\nМассив:\n";
    print_vector_by_10(nums);
    cout << "\nРезультат (сумма квадратов): " << result << "\n\n";

    // Предложение сохранить массив в файл
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