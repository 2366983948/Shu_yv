#include<iostream>
#include<thread>
#include<mutex>
using namespace  std;

int shared_data = 0;
mutex mtx;
void func() {
    for (int i = 0; i < 100000; ++i) {
        std::lock_guard<mutex> lock(mtx);
        shared_data++;
    }
}
int main() {
    std::thread t1(func);
    std::thread t2(func);
    t1.join();
    t2.join();
    std::cout << "shared_data = " << shared_data << std::endl;    
    return 0;
}