#include <atomic>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std::chrono_literals;

void print(std::string_view str) {
    for (auto ch : str) {
        std::cout << ch;
    }
    std::cout << std::endl;
}

class spinlock_mutex {
    std::atomic_flag flag = ATOMIC_FLAG_INIT;

public:
    spinlock_mutex() = default;

    void lock() {
        while (flag.test_and_set(std::memory_order_acquire))
            ;
    }

    void unlock() {
        flag.clear(std::memory_order_release);
    }
};

spinlock_mutex sm1;
spinlock_mutex sm2;

void func5() {
    std::lock_guard<spinlock_mutex> lg(sm1);
    for (int i = 0; i < 10; i++) {
        std::this_thread::sleep_for(100ms);
        print(__PRETTY_FUNCTION__);
        std::cout << i << " ";
    }
    std::cout << std::endl;
}
void func6() {
    std::lock_guard<spinlock_mutex> grd(sm1);
    for (int i = 0; i < 10; i++) {
        std::this_thread::sleep_for(100ms);
        print(__PRETTY_FUNCTION__);
        std::cout << i << " ";
    }
    std::cout << std::endl;
    print(__PRETTY_FUNCTION__);
}

int main() {
    std::atomic<int> atomic_var;
    std::cout << std::boolalpha << atomic_var.is_lock_free() << std::endl;
    // std::thread t1(func5);
    // std::thread t2(func6);
    // t1.join();
    // t2.join();

    std::atomic<bool> atomic_var_1;
    std::atomic<bool> atomic_var_2;
    atomic_var_1 = false;
    atomic_var_1.store(true);
    std::cout << std::boolalpha << atomic_var_1.load() << std::endl;
    atomic_var_1.exchange(false, std::memory_order_acquire);
    std::cout << std::boolalpha << atomic_var_1.load() << std::endl;

    atomic_var.fetch_add(2);
    std::atomic<int*> ptr(new int[10]);
    std::cout << ptr << std::endl;
    ptr.fetch_add(1);
    std::cout << ptr << std::endl;
    atomic_var = 10;
    int k = 9;
    atomic_var.compare_exchange_weak(k, 100);
    std::cout << atomic_var << std::endl;
    std::cout << k << std::endl;

    return 0;
}
