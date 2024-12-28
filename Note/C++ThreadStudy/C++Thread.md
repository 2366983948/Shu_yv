# C++ 多线程编程学习笔记

- [一、基本使用](#一基本使用)
  - [1. 创建线程](#创建线程)
  - [2. thread 类方法](#thread-类方法)

- [二、数据未定义错误](#二数据未定义错误)
  - [1. 传递临时变量](#1传递临时变量)
  - [2. 传递指针或引用指向局部变量的问题](#2传递指针或引用指向局部变量的问题)
  - [3. 传递指针或引用指向已释放的内存的问题](#3传递指针或引用指向已释放的内存的问题)
  - [4. 类成员函数作为入口函数，类对象被提前释放](#4类成员函数作为入口函数类对象被提前释放)
  - [5. 入口函数为类的私有成员函数](#5入口函数为类的私有成员函数)

- [三、互斥量解决数据共享](#三互斥量解决数据共享)

- [四、互斥量死锁](#四互斥量死锁)
  - [扩展：死锁相关知识](#扩展死锁相关知识)

- [五、lock_guard 与 std::unique_lock](#五lock_guard-与-stdunique_lock)
  - [1. lock_guard](#1-lock_guard)
  - [2. std::unique_lock](#2-stdunique_lock)

- [六、std::call_once与其使用场景](#六stdcall_once与其使用场景)

- [七、condition_variable 与其使用场景](#七condition_variable-与其使用场景)

- [八、跨平台线程池](#八跨平台线程池)

- [九、异步编程](#九异步编程)
  - [future,async](#futureasync)
  - [packaged_task](#packaged_task)
  - [promise](#promise)

- [十、原子操作 std::atomic](#十原子操作-stdatomic)

[参考文章](http://www.seestudy.cn/?list_9/31.html)
[参考视频](https://www.bilibili.com/video/BV1d841117SH)
## 一、基本使用
### 创建线程
```c++
#include <thread>
void thread_func()
{

}
int main(){
    std::thread t(thread_func);//创建线程t
}
```
### thread 类方法
|函数|作用|
|-|-|
|void join()|阻塞当前线程，直到线程t结束|
|bool joinable()|返回线程是否可以执行join函数|
|void detach()|分离线程，线程t执行完毕后，自动销毁|

## 二、数据未定义错误
### 1传递临时变量
```c++
#include <thread>
using namespace std;

void thread_func(int &x)
{
    x++;
}

int main(){
    std::thread t(thread_func,1);//创建线程t
    t.join();
    return 0;
}
```
- 错误:临时变量销毁，导致引用失效
- 结果：无法编译
- 解决：使用 `std::ref()` 函数，把a转变成a的引用
```c++ 
int a = 1;
std::thread t(thread_func,ref(a));
```
### 2传递指针或引用指向局部变量的问题
```c++
thread t;
void thread_func(int &x)
{
    x++;
}

void test(){
    int a = 1;
    t = std::thread(thread_func,ref(a));//创建线程t
}

int main(){
    test();
    t.join();
    return 0;
}
```
- 错误：a是test的局部变量，test函数执行完毕，a就销毁了，导致引用失效
- 结果：可以编译，运行时出错
- 解决：把a定义在 `全局区`

### 3传递指针或引用指向已释放的内存的问题
```c++
thread t;
void thread_func(int *x)
{
    cout<<*x<<endl;
}

int main(){
    int* ptr = new int(1);
    t = std::thread(thread_func,ptr);//创建线程t
    t.join();
    return 0;
}
```
- 错误：指针指向的区域被释放
- 结果：可以编译，可以运行，但结果随机
- 解决：使用 `智能指针`
### 4类成员函数作为入口函数，类对象被提前释放
```c++
class A{
    public:
    void foo(){
        cout<<"foo"<<endl;
    }
};

int main(){
    A a;
    std::thread t(&A::foo,&a);
    delete(&a);

    t.join();
    return 0;
}

// 上面也会出错
// 正确写法
int main(){
    shared_ptr<A> a = make_shared<A>();
    std::thread t(&A::foo,&a);
    delete(&a);

    t.join();
    return 0;
}
```
- 智能指针：当变量不在被需要的时候，操作系统会调用析构函数，自动释放内存

### 5入口函数为类的私有成员函数
```c++
class A{
private:
    void foo(){
        cout<<"foo"<<endl;
    }
};

int main(){
    shared_ptr<A> a = make_shared<A>();
    std::thread t(&A::foo,&a);
    delete(&a);

    t.join();
    return 0;
}
//正确写法
class A{
private:
    friend void thread_fun();
    void foo(){
        cout<<"foo"<<endl;
    }
};

void thread_fun(){
    shared_ptr<A> a = make_shared<A>();
    std::thread t(&A::foo,&a);
}

int main(){
    thread_fun();
    delete(&a);

    t.join();
    return 0;
}
```
## 三、互斥量解决数据共享
```c++
int shared_data = 0;
void func() {
    for (int i = 0; i < 100000; ++i) {
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
```
- 错误：线程1，2没有互斥地访问共享数据
- 结果：可以编译，可以运行，但结果不正确（偏小）
- 解决：使用 `互斥锁`

正确写法如下
```c++
#include <mutex>
std::mutex mtx;//互斥锁
int shared_data = 0;
void func() {
    for (int i = 0; i < 100000; ++i) {
        mtx.lock();
        shared_data++;
        mtx.unlock();
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
```
## 四、互斥量死锁
假设有两个线程 T1 和 T2，它们需要对两个互斥量 mtx1 和 mtx2 进行访问，而且需要按照以下顺序获取互斥量的所有权：
- T1 先获取 mtx1 的所有权，再获取 mtx2 的所有权。
- T2 先获取 mtx2 的所有权，再获取 mtx1 的所有权。

如果两个线程同时执行，就会出现死锁问题。因为 T1 获取了 mtx1 的所有权，但是无法获取 mtx2 的所有权，而 T2 获取了 mtx2 的所有权，但是无法获取 mtx1 的所有权，两个线程互相等待对方释放互斥量，导致死锁。
### 扩展：死锁相关知识
1. 死锁定义：在多线程环境下，当两个或两个以上的线程都互相等待其他线程释放资源，而都无法释放自己所请求的资源，导致线程处于等待状态，从而导致系统假死。
2. 死锁发生必要条件：
- 互斥：一个资源只能被一个进程使用。
- 请求和保持：进程已经保持至少一个资源，但又提出了新的资源请求，而该资源已被其他进程占有。
- 不剥夺条件：进程已获得的资源，在未使用完之前，不能强行剥夺。
- 循环等待：若干进程之间形成一种头尾相接的循环链表。
3. 死锁解决办法
- 死锁预防：破坏必要条件之一
- 死锁避免：再资源分配时检测是否有风险。（银行家算法）
- 死锁解除
- 死锁检测
    - 资源剥夺
    - 进程撤销
    - 进程回退

## 五、lock_guard 与 std::unique_lock
### 1. lock_guard
std::lock_guard 是 C++ 标准库中的一种互斥量封装类，用于保护共享数据，防止多个线程同时访问同一资源而导致的数据竞争问题。

std::lock_guard 的特点如下：
- 当构造函数被调用时，该互斥量会被自动锁定。
- 当析构函数被调用时，该互斥量会被自动解锁。
- std::lock_guard 对象不能复制或移动，因此它只能在局部作用域中使用。
```c++
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
//可以正确运行
```
### 2. std::unique_lock
std::unique_lock 是 C++ 标准库中提供的一个互斥量封装类，用于在多线程程序中对互斥量进行加锁和解锁操作。它的主要特点是可以对互斥量进行更加灵活的管理，包括延迟加锁、条件变量、超时等。

std::unique_lock 提供了以下几个成员函数：
- lock()：尝试对互斥量进行加锁操作，如果当前互斥量已经被其他线程持有，则当前线程会被阻塞，直到互斥量被成功加锁。
- try_lock()：尝试对互斥量进行加锁操作，如果当前互斥量已经被其他线程持有，则函数立即返回 false，否则返回 true。
- try_lock_for(const std::chrono::duration<Rep, Period>& rel_time)：尝试对互斥量进行加锁操作，如果当前互斥量已经被其他线程持有，则当前线程会被阻塞，直到互斥量被成功加锁，或者超过了指定的时间。
- try_lock_until(const std::chrono::time_point<Clock, Duration>& abs_time)：尝试对互斥量进行加锁操作，如果当前互斥量已经被其他线程持有，则当前线程会被阻塞，直到互斥量被成功加锁，或者超过了指定的时间点。
- unlock()：对互斥量进行解锁操作。

除了上述成员函数外，std::unique_lock 还提供了以下几个构造函数：
- unique_lock() noexcept = default：默认构造函数，创建一个未关联任何互斥量的 std::unique_lock 对象。
- explicit unique_lock(mutex_type& m)：构造函数，使用给定的互斥量 m 进行初始化，并对该互斥量进行加锁操作。
- unique_lock(mutex_type& m, defer_lock_t) noexcept：构造函数，使用给定的互斥量 m 进行初始化，但不对该互斥量进行加锁操作。
- unique_lock(mutex_type& m, try_to_lock_t) noexcept：构造函数，使用给定的互斥量 m 进行初始化，并尝试对该互斥量进行加锁操作。如果加锁失败，则创建的 std::unique_lock 对象不与任何互斥量关联。
- unique_lock(mutex_type& m, adopt_lock_t) noexcept：构造函数，使用给定的互斥量 m 进行初始化，并假设该互斥量已经被当前线程成功加锁。
```c++
int shared_data = 0;
timed_mutex mtx;    //可以延迟的互斥锁
void func() {
    for (int i = 0; i < 3; ++i) {
        std::unique_lock<timed_mutex> lock(mtx,defer_lock);//第二个参数是为了不自动加锁
        //等待上锁，最多等2秒
        if (lock.try_lock_for(std::chrono::seconds(2))) {
            this_thread::sleep_for(std::chrono::seconds(3));//线程休眠3秒
            shared_data++;
        }
        else {
            cout << "获取资源失败" << endl;
        }
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
```
## 六、std::call_once与其使用场景
单例设计模式是一种常见的设计模式，用于确保某个类只能创建一个实例。
```c++
//单例模式举例，日志类
//懒汉模式：在第一次调用getInstance时才创建对象
//饿汉模式：提前创建对象，调用getInstance时返回对象
static Log* log; 
class Log{
public:
    Log(){}
    Log(const Log& log) = delete;
    Log& operator=(const Log& log) = delete;
    static Log& getInstance(){
        if(!log){
            log = new Log();
        }
        return *log;
    } 
    void PrintLog(string msg){

    }
}
int main(){
    Log::getInstance().PrintLog("hello world");
}
```
- 多线程时，多个线程同时调用创建实例，导致出错

使用call_once可以解决这个问题，使用call_once可以保证函数只被调用一次。
```c++
class Log {
public:
    Log() = default;
    Log(const Log&) = delete;
    Log& operator=(const Log&) = delete;

    static Log& getInstance() {
        std::call_once(flag, init);
        return *log;
    }

    void PrintLog(std::string msg) {
        // 实现日志打印逻辑
    }

private:
    static Log* log;
    static std::once_flag flag;

    static void init() {
        if (!log) {
            log = new Log();
        }
    }
};
int main(){
    Log::getInstance().PrintLog("hello world");
}
```
## 七、condition_variable 与其使用场景
std::condition_variable 的步骤如下：
- 创建一个 `std::condition_variable` 对象。
- 创建一个互斥锁 `std::mutex` 对象，用来保护共享资源的访问。
- 在需要等待条件变量的地方使用 `std::unique_lock<std::mutex>` 对象锁定互斥锁，并调用 `std::condition_variable::wait()`、`std::condition_variable::wait_for()` 或 `std::condition_variable::wait_until()` 函数等待条件变量。
- 在其他线程中需要通知等待的线程时，调用 `std::condition_variable::notify_one()` 或 `std::condition_variable::notify_all()` 函数通知等待的线程。

使用场景：生产者消费者模型
```c++
#include<iostream>
#include<thread>
#include<mutex>
#include<string>
#include<condition_variable>
#include<queue>
using namespace  std;

// 全局变量用于生产者-消费者模式
std::mutex g_mutex;  // 互斥锁，保护共享资源（队列）
std::condition_variable g_cv;  // 条件变量，用于线程间通信
std::queue<int> g_queue;  // 共享队列，存储生产者生成的数据

// 生产者函数：负责生成数据并放入队列
void Producer() {
    for (int i = 0; i < 10; i++) {
        {
            // 使用 unique_lock 锁定互斥锁，确保对共享资源的独占访问
            std::unique_lock<std::mutex> lock(g_mutex);
            g_queue.push(i);  // 将数据放入队列
            std::cout << "Producer: produced " << i << std::endl;  // 打印生产信息
        }
        // 通知一个等待的消费者线程，有新数据可以消费
        g_cv.notify_one();
        // 模拟生产时间间隔，休眠100毫秒
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

// 消费者函数：负责从队列中取出数据并处理
void Consumer() {
    while (true) {
        // 使用 unique_lock 锁定互斥锁，确保对共享资源的独占访问
        std::unique_lock<std::mutex> lock(g_mutex);
        // 等待条件变量，直到队列中有数据可消费
        g_cv.wait(lock, []() { return !g_queue.empty(); });
        // 取出队列中的第一个元素
        int value = g_queue.front();
        g_queue.pop();  // 移除已消费的数据
        std::cout << "Consumer: consumed " << value << std::endl;  // 打印消费信息
    }
}

int main() {
    // 创建生产者线程和消费者线程
    std::thread producer_thread(Producer);
    std::thread consumer_thread(Consumer);

    // 等待生产者线程完成
    producer_thread.join();

    // 注意：当前实现中消费者线程会无限循环等待，这里需要额外处理以优雅退出
    // 例如可以通过信号量或标志位来通知消费者线程结束

    // 等待消费者线程完成（实际上不会结束，因为消费者是无限循环）
    // 这里可以考虑使用其他方式终止消费者线程
    consumer_thread.join();

    return 0;
}
```
## 八、跨平台线程池
```c++
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <queue>

class ThreadPool {
public:
    ThreadPool(int numThreads) : stop(false) {
        for (int i = 0; i < numThreads; ++i) {
            threads.emplace_back([this] {
                while (true) {
                    std::unique_lock<std::mutex> lock(mutex);
                    condition.wait(lock, [this] { return stop || !tasks.empty(); });
                    if (stop && tasks.empty()) {
                        return;
                    }
                    std::function<void()> task(std::move(tasks.front()));
                    tasks.pop();
                    lock.unlock();
                    task();
                }
                });
        }
    }

    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(mutex);
            stop = true;
        }
        condition.notify_all();
        for (std::thread& thread : threads) {
            thread.join();
        }
    }

    template<typename F, typename... Args>
    void enqueue(F&& f, Args&&... args) {
        std::function<void()> task(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
        {
            std::unique_lock<std::mutex> lock(mutex);
            tasks.emplace(std::move(task));
        }
        condition.notify_one();
    }

private:
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> tasks;
    std::mutex mutex;
    std::condition_variable condition;
    bool stop;
};

int main() {
    ThreadPool pool(4);
    for (int i = 0; i < 8; ++i) {
        pool.enqueue([i] {
            std::cout << "Task " << i << " is running in thread " << std::this_thread::get_id() << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "Task " << i << " is done" << std::endl;
            });
    }
    return 0;
}
```
## 九、异步编程
### future,async
```c++
#include<future>

int func() {
    int i = 0;
    for (; i < 1000; i++) {
        
    }
    return i;
}
int main() {
    std::future<int>future_result = std::async(std::launch::async, func);//异步执行
    std::cout << future_result.get() << std::endl;//调用get()时如果线程没有执行完会阻塞等待
    return 0;
}
```
### packaged_task
packaged_task 是一个模板类，用于包装一个可调用对象，使其可以在异步线程中执行。
```c++
#include <iostream>
#include<future>
using namespace std;

int func() {
    int i = 0;
    for (; i < 1000; i++) {
        
    }
    return i;
}
int main() {
    packaged_task<int()>task(func);//包装的任务是一个不带参数且返回 int 类型的函数
    auto future_result = task.get_future();

    thread t1(std::move(task));
//     std::move 是 C++11 引入的一个工具函数，用于将对象从左值转换为右值引用，从而允许移动语义（move semantics）的应用。
// 在这里，task 是一个 std::packaged_task<int()> 对象。由于 std::packaged_task 不支持复制（即不能直接复制），只能通过移动语义将其所有权转移给新的线程对象 t1。

    std::cout << future_result.get() << std::endl;
    return 0;
}
```
### promise
`promise`是一个类模板，用于在一个线程中产生一个值，并在另一个线程中获取这个值。promise通常与future和async一起使用，用于实现异步编程。
```c++
#include <iostream>
#include<future>
using namespace std;

void func( promise<int>&f) {
    f.set_value(1000);
}
int main() {
    promise<int> f;
    auto future_result = f.get_future();

    thread t1(func,ref(f));
    t1.join();
    std::cout << future_result.get() << std::endl;
    return 0;
}
```
## 十、原子操作 std::atomic
原子操作是指在多线程环境下，对共享变量进行操作时，保证操作的原子性。在C++中，可以使用原子类型（如std::atomic）来实现原子操作。
```c++
#include <iostream>
#include<thread>
#include<atomic>
using namespace std;

atomic<int>shared_data = 0;
void func() {
    for (int i = 0; i < 100000; ++i) {
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
//可以正确运行
```
以下是一些常用的 `std::atomic` 操作：
1. `load()`：将 `std::atomic` 变量的值加载到当前线程的本地缓存中，并返回这个值。
2. `store(val)`：将 `val` 的值存储到 `std::atomic` 变量中，并保证这个操作是原子性的。
3. `exchange(val)`：将 `val` 的值存储到 `std::atomic` 变量中，并返回原先的值。
4. `compare_exchange_weak(expected, val)` 和 `compare_exchange_strong(expected, val)`：比较 `std::atomic` 变量的值和 `expected` 的值是否相同，如果相同，则将 `val` 的值存储到 `std::atomic` 变量中，并返回 `true`；否则，将 `std::atomic` 变量的值存储到 `expected` 中，并返回 `false`。