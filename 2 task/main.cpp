#include <iostream>
#include <vector>
#include <string>
#include "module.hpp"

int main() {

    using namespace std;
    vector<int> nums; 
    string user_str = "1";
    int result = 1;
    cout << "Вводите нужные числа через Enter. \nЕсли числа закончились, нажмите Enter с пустой строкой\n";
    while (true)
    {
        getline(cin, user_str);
        if (!user_str.empty())
        {
            nums.push_back(stoi(user_str));
        }
        else {
            break;
        }
    }
    result = mul_vector_nums(nums);

    cout << result;
    return 0;
}