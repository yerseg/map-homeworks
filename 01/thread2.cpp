#include <iostream>
#include <string>
#include <thread>
#include <vector>

void func3(int x, std::string& str) {
    str += "def";
    std::cout << x << " " << str << std::endl;
}

int func4(int x) {
    return x * 4;
}

thread_local int g_x = 2;

void func5() {
    using namespace std::chrono_literals;

    std::this_thread::sleep_for(100ms);
    g_x = g_x * 10;
    std::cout << g_x << std::endl;
}

void func6() {
    using namespace std::chrono_literals;

    std::this_thread::sleep_for(500ms);
    g_x = g_x + 10;
    std::cout << g_x << std::endl;
}

std::once_flag flag;

void print_once() {
    std::cout << "!";
}

void print(size_t x) {
    std::call_once(flag, print_once);
    std::cout << x << " ";
}

int main() {
    // std::string s = "abs";
    // std::thread t1(func3, 3, std::ref(s));
    // t1.join();
    // std::cout << s << std::endl;
    // int res;
    // std::thread t2([&]() { res = func4(20); });
    // t2.join();
    // std::cout << res << std::endl;
    // std::thread t3(func6);
    // std::thread t4(func5);
    // t3.join();
    // t4.join();

    std::vector<std::thread> threads;
    for (size_t i = 0; i < 10; i++) {
        threads.emplace_back(print, i);
    }
    for (auto& t : threads) {
        t.join();
    }
    std::cout << std::endl;
    return 0;
}
