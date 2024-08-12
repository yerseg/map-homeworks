#include <iostream>
#include <thread>

void func1() {
    using namespace std::chrono_literals;

    std::cout << "#id = " << std::this_thread::get_id() << std::endl;
    for (int i = 0; i < 10; i++) {
        std::this_thread::sleep_for(100ms);
        std::cout << "Hello from 1 thread!" << std::endl;
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

void func2() {
    using namespace std::chrono_literals;

    std::cout << "#id = " << std::this_thread::get_id() << std::endl;
    for (int i = 0; i < 10; i++) {
        std::this_thread::sleep_for(100ms);
        std::cout << "Hello from 2 thread!" << std::endl;
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

class A {
public:
    void funcA() {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    void operator()() {
        std::cout << "Functor" << std::endl;
    }
};

int main() {
    std::cout << std::thread::hardware_concurrency() << std::endl;
    // std::thread t1(func1);
    // std::thread t2(func2);
    // if (t1.joinable())
    //{
    //	std::cout << "t1.joinable()" << std::endl;
    // }
    // t1.join();
    // t2.join();
    A obj;
    // std::thread t3(&A::funcA, &obj);
    // t3.join();
    // std::thread t4(obj);
    // t4.join();
    // std::thread t5([]() { std::cout << "lambda" << std::endl; });
    // t5.join();

    std::thread t6(func1);
    std::thread t7 = std::move(t6);
    t6 = std::thread(func2);
    t6.join();
    t7.join();

    return 0;
}
