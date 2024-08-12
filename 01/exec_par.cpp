#include <algorithm>
#include <chrono>
#include <execution>
#include <iostream>
#include <random>
#include <vector>

void Sort(std::vector<int> v) {
    auto start = std::chrono::high_resolution_clock::now();
    std::sort(v.begin(), v.end());
    auto end = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "std::sort time = " << time.count() << std::endl;
}

void ParSort(std::vector<int> v) {
    auto start = std::chrono::high_resolution_clock::now();
    std::sort(std::execution::par, v.begin(), v.end());
    auto end = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "std::parallel sort time = " << time.count() << std::endl;
}

int main() {
    std::vector<int> V(1'000'000);
    std::mt19937 gen;
    std::uniform_int_distribution<int> dis(0, 1'000'000);
    auto rand_num([=]() mutable { return dis(gen); });
    std::generate(V.begin(), V.end(), rand_num);

    Sort(V);
    ParSort(V);
    return 0;
}
