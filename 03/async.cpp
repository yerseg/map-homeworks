#include <chrono>
#include <exception>
#include <future>
#include <iostream>
#include <stdexcept>
#include <thread>

int main1() {
    std::cout << "Main thread id = " << std::this_thread::get_id() << std::endl;
    auto fut = std::async(std::launch::async, [] {
        std::cout << std::this_thread::get_id() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(10));
        std::cout << "Hello!" << std::endl;
    });
    // fut.get();
    return 0;
}

auto foo() -> std::string {
    throw std::runtime_error("error");
    return "HELLO!";
}

int main2() {
    std::cout << "Main thread id = " << std::this_thread::get_id() << std::endl;

    std::packaged_task task([] {
        std::cout << std::this_thread::get_id() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    });

    std::future<void> fut = task.get_future();
    std::thread t(std::move(task));

    try {
        fut.get();
    } catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }

    t.join();

    return 0;
}

struct custom_exception : public std::exception {
    const char* what() const noexcept override {
        return "excpt";
    }

    custom_exception() = default;

    custom_exception(const custom_exception& ex) {
    }
};

double div(double x) {
    if (x == 0) {
        throw custom_exception();
    }
    return 1 / x;
}

int main() {
    try {
        auto fut = std::async([] { return div(0.0); });
        std::cout << fut.get() << std::endl;
    } catch (const custom_exception& err) {
        std::cerr << err.what() << std::endl;
    }
    return 0;
}
