#include <chrono>
#include <iostream>
#include <thread>

void print_x(int x) {
    std::cout << x << std::endl;
}

void start_print() {
    int t = 10;
    std::thread t1(print_x, t);
    t1.detach();
}

int main() {
    using namespace std::chrono_literals;

    std::thread t2(start_print);
    t2.join();
    std::this_thread::sleep_for(2s);
    return 0;
}
