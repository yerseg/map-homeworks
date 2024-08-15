#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

using namespace std::chrono_literals;

std::mutex m1;
std::mutex m2;

void deadlock_func_1() {
    std::cout << "Start deadlock_func_1..." << std::endl;
    std::scoped_lock L{m1, m2};
    // std::lock(m1, m2);
    // std::lock_guard<mutex> la{m1, std::adopt_lock};
    // std::unique_lock<mutex>la{ m1, std::defer_lock };
    std::this_thread::sleep_for(100ms);
    std::cout << "deadlock_func_1 acquires mutex 1..." << std::endl;
    // std::lock_guard<mutex> lb{m2, std::adopt_lock};
    // std::unique_lock<mutex> lb{ m2, std::defer_lock };
    // std::lock(m1, m2);
    std::cout << "Never print A" << std::endl;
}

void deadlock_func_2() {
    std::scoped_lock L{m1, m2};
    // std::lock(m1, m2);
    std::cout << "Start deadlock_func_2..." << std::endl;
    // std::lock_guard<mutex> lb{m2, std::adopt_lock};
    // std::unique_lock<mutex>lb{ m2, std::defer_lock };
    std::this_thread::sleep_for(200ms);
    std::cout << "deadlock_func_2 acquires mutex 2..." << std::endl;
    // std::lock_guard<mutex> la{m1, std::adopt_lock};
    // std::unique_lock<mutex>la{ m1, std::defer_lock };
    std::cout << "Never print B" << std::endl;
    // std::lock(m1, m2);
}

int main() {
    std::thread t1(deadlock_func_1);
    std::thread t2(deadlock_func_2);
    t1.join();
    t2.join();

    return 0;
}
