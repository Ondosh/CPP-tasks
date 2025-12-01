#ifndef MATH_FUNCTIONS
#define MATH_FUNCTIONS

#include <vector>
#include <ctime>
#include <iostream>

namespace mathfunc {
    int sum_of_powers (const std::vector<int>& numbers);
}

namespace auxiliary {
    std::vector<int> random_vector(int n);
    void print_vector_by_10(const std::vector<int>& vec);
}
#endif