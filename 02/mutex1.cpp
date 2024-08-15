#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std::chrono_literals;

std::mutex m;

void print(std::string_view str) {
    for (auto ch : str) {
        std::cout << ch;
    }
    std::cout << std::endl;
}

void func1() {
    std::lock_guard<std::mutex> grd(m);
    for (int i = 0; i < 10; i++) {
        std::this_thread::sleep_for(100ms);
        print(__PRETTY_FUNCTION__);
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

void func2() {
    // m.lock();
    std::lock_guard<std::mutex> grd(m);
    for (int i = 0; i < 10; i++) {
        std::this_thread::sleep_for(100ms);
        print(__PRETTY_FUNCTION__);
        std::cout << i << " ";
    }
    std::cout << std::endl;
    print(__PRETTY_FUNCTION__);
    // m.unlock();
}

std::recursive_mutex recursive_mtx;

void rec_print(int x) {
    recursive_mtx.lock();
    std::cout << x << " ";
    std::this_thread::sleep_for(100ms);
    if (x == 0) {
        std::cout << std::endl;
        recursive_mtx.unlock();
        return;
    }
    rec_print(--x);
    recursive_mtx.unlock();
}

int main() {
    // std::thread t1(func1);
    // std::thread t2(func2);
    // t1.join();
    // t2.join();

    std::thread t3(rec_print, 6);
    std::thread t4(rec_print, 4);
    t3.join();
    t4.join();

    return 0;
}
