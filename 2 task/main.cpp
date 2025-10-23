#include <iostream>
#include <vector>
#include <string>

int main() {

    using namespace std;
    vector<int> nums; 

    string user_str = "1";
    cout << "Вводите нужные числа через Enter. \nЕсли числа закончились, нажмите Enter с пустой строкой";
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
    
    cout << nums.size();
    return 0;
}