// Автор: Томских Т.К. (Ondosh)

#include "calc.hpp"

namespace calculating {
    /*
    
    */
    float calculate_a(float x, float y, float z){
        float a;
        a = (3 + exp(y - 1)) / (1 + (pow(x, 2)*abs(y - tan(z))));
        return a;
    }

    float calculate_b(float x, float y, float z){
        float b;
        b = (1 + abs(y - x)) + (pow(y - x, 2) / 2) + (pow(abs(y - x), 3) / 3);
        return b;
    }
}
