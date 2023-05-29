#ifndef SDP_PRINT_UTILS_H_
#define SDP_PRINT_UTILS_H_

#include <cstddef>
#include <iostream>
#include <vector>
#include <iomanip>
#include <array>

namespace sdp {
namespace utils {

template<typename T>
void print(const std::vector<T>& vec) {
    if (vec.empty()) {
        return;
    }

    const std::size_t len = vec.size();

    for (std::size_t ix = 0; ix < len - 1; ix++) {
        std::cout << std::fixed << vec.at(ix) << ", ";
    }

    std::cout << vec.at(len - 1) << "\n";
}

template<typename T, std::size_t N>
void print(const std::array<T, N>& arr) {
    if (arr.empty()) {
        return;
    }

    for (std::size_t ix = 0; ix < N - 1; ix++) {
        std::cout << std::fixed << arr.at(ix) << ", ";
    }

    std::cout << arr.at(N - 1) << "\n";
}

}  // namespace utils
}  // namespace sdp

#endif  // SDP_PRINT_UTILS_H_
