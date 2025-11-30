#include <vector>
#include "module.hpp"
#include <cmath>
namespace mathfunc {
    int sum_of_powers(const std::vector<int>& nums) {
        using namespace std;
        
        int result = 0;
        for (int num : nums) {
            result += pow(num, 2);
        }
        return result;
    }
}