// Автор: Томских Т.К. (Ondosh)

#include <cassert>
#include <iostream>
#include "calc.hpp"

int main(){
    float x, y, z;
    float a, b;

    using namespace std;
    using namespace calculating;
    using namespace constants;

    assert(abs(calculate_b(1, 1, 1) - 1) < e);
    assert(abs(calculate_a(1, 2, 3) - 1.81963 ) < e);
    assert(abs(calculate_b(2, 2, 2) - 1) < e);

    
    cin.exceptions(ios_base::failbit);
    try {   
        cout << "Введите х: ";
        cin >> x;
        cout << "Введите у: ";
        cin >> y;
        cout << "Введите z: ";
        cin >> z;

        a = calculate_a(x, y, z);
        b = calculate_b(x, y, z);

        cout << a << endl;
        cout << b << endl;
    } 
    catch (const ios_base::failure& err) {
        cout << "Ошибка ввода: " << err.what() << endl;
        cout << "Введены некорректные данные!" << endl;
        
        // Сбрасываем флаги ошибок и очищаем буфер
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        return 1;
    }
    return 0;
}