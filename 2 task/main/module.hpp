#ifndef MODULE_HPP
#define MODULE_HPP

#include <string>
#include <cstddef>

namespace mathfunc {
    int sum_of_powers(const int* arr, size_t size);
}

namespace auxiliary {
    int* random_array(int n, size_t& out_size);
    void print_array_by_10(const int* arr, size_t size);
}

namespace file_work {
    bool save_array_to_file(const int* arr, size_t size, const std::string& filename);
    int* load_array_from_file(const std::string& filename, size_t& out_size);
}

#endif // MODULE_HPP