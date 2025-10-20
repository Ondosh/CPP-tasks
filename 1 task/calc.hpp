// Автор: Томских Т.К. (Ondosh)

#ifndef MODULE // Защита от повторного включения
#define MODULE
#include "math.h"

namespace calculating {
    /*
    * Вычисляет значение по особой формуле из задания
    * @param
    */
    float calculate_a(float x, float y, float z);
    /*
    Вычисляет значение по особой формуле из задания
    */
    float calculate_b(float x, float y, float z);
}

namespace constants {
    float const e = 0.0001; 
}
#endif