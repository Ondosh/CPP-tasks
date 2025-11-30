#include <vector>
#include "module.hpp"
#include <cmath>

int mul_vector_nums(const std::vector<int>& nums) {
    using namespace std;
    
    int result = 0;
    for (int num : nums) {
        result += pow(num, 2);
    }
    return result;
}
