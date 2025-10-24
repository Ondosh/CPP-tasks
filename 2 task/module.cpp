#include <vector>
#include "module.hpp"

int mul_vector_nums(const std::vector<int>& nums) {
    int result = 1;
    for (int num : nums) {
        result *= num;
    }
    return result;
}
