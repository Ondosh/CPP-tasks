// Автор: Томских Т.К. (Ondosh)

#include <cassert>
#include <iostream>
#include "calc.hpp"

int main(){
    // Идентификация переменных для записи пользователем и для записи результата
    float x, y, z;
    float a, b;

    // Используем упрощающие написание кода namespaces
    using namespace std;
    using namespace calculating;
    using namespace constants;

    // Используем тесты с учётом погрешностей для проверки правильной работы функции
    assert(abs(calculate_b(1, 1, 1) - 1) < e);
    assert(abs(calculate_a(1, 2, 3) - 1.81963 ) < e);
    assert(abs(calculate_b(2, 2, 2) - 1) < e);

    // Включаем исключения для cin (защита от неправильного ввода)
    cin.exceptions(ios_base::failbit);
    try {
        // Юзер вводит переменные x, y, z для вычисления по формулам из модуля   
        cout << "Введите х: ";
        cin >> x;
        cout << "Введите у: ";
        cin >> y;
        cout << "Введите z: ";
        cin >> z;

        // Происходит вычисление по заданным формулам с использованием введённых переменных x, y, z
        a = calculate_a(x, y, z);
        b = calculate_b(x, y, z);

        // В терминал выводится результат отработанных функций вычисления
        cout << a << endl;
        cout << b << endl;
    } 

    // "Ловим" ошибку ввода
    catch (const ios_base::failure& err) {
        // Выводим в терминал ошибку
        cout << "Ошибка ввода: " << err.what() << endl;
        cout << "Введены некорректные данные!" << endl;
        
        // Сбрасываем флаги ошибок и очищаем буфер
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Заканчиваем работу с ошибкой 1
        return 1;
    }

    return 0;
}