#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

using namespace std::chrono_literals;

bool flag = false;
std::mutex m3;

void wait_flag() {
    std::unique_lock<std::mutex> l(m3);
    while (!flag) {
        l.unlock();
        std::this_thread::sleep_for(200ms);
        l.lock();
        std::cout << "Flag not set" << std::endl;
    }
    std::cout << "Flag was set!!!" << std::endl;
}

void set_flag() {
    std::this_thread::sleep_for(1s);
    std::unique_lock<std::mutex> l(m3);
    flag = true;
    l.unlock();
}

std::mutex mut;
std::queue<int> data_queue;
std::condition_variable data_cond;

void data_preparation_thread() {
    int cnt = 0;
    while (cnt < 10) {
        const int data = rand() % 100;
        std::lock_guard<std::mutex> lk(mut);
        std::this_thread::sleep_for(10ms);
        data_queue.push(data);
        std::cout << "Push " << data << std::endl;
        data_cond.notify_all();
        if (data == 0)
            break;
    }
}

void data_processing_thread() {
    while (true) {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk, [] { return !data_queue.empty(); });
        int data = data_queue.front();
        data_queue.pop();
        lk.unlock();
        std::cout << "  Pop " << data << std::endl;
        if (data == 0)
            break;
    }
}

int main() {
    // std::thread t3(wait_flag);
    // std::thread t4(set_flag);
    // t3.join();
    // t4.join();

    std::thread t1(data_preparation_thread);
    std::thread t2(data_processing_thread);
    t1.join();
    t2.join();
    return 0;
}