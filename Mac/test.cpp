// xcrun make test

#include <stdio.h>
#include <vector>
#include <thread>
#include <future>
#include <unistd.h>

#include <iostream>
//#include <numeric>
//#include <chrono>
//#include <algorithm>
//#include <functional>

#define NUM_THREAD 10
std::mutex mtx1, mtx2;

std::condition_variable cv;
int var = 2;

static int temp = -1;
static const int n = 10;
void worker(int i){
    while(i < 30) i++;
    return;
}
void printFoo(std::string str)
{
    std::cout << str;
}
int update(int i)
{
    for(int i = 0; i < n ;i++)
    {
        std::unique_lock<std::mutex> lck(mtx1);
        //while(var != 2){ cv.wait(lck);}
        printFoo("Update");
        var = 1;
        lck.unlock();
        cv.notify_one();
    }
    return i;
}
int fetch(int i)
{
    for(int i = 0; i < n ;i++)
    {
        std::unique_lock<std::mutex> lck(mtx1);
        while(var != 1){ cv.wait(lck);}
        printFoo("Fetch\n");

        var = 2;
        lck.unlock();
        //cv.notify_one();
    }
    return i;
}
void start()
{
    for(int i = 0; i < 1; i++)
    {
        std::thread t2(fetch,i);
        std::thread t1(update,i);
        t1.join();
        t2.join();
    }
}
using FuncType = std::function<int (const std::string&)>;
int main(void)
{
    std::thread t(start);
    t.join();
    return 1;
}
/*
void accumulate(std::vector<int>::iterator first,
                std::vector<int>::iterator last,
                std::promise<int> accumulate_promise)
{
    int sum = std::accumulate(first, last, 0);
    accumulate_promise.set_value(sum);  // Notify future
}
 
void do_work(std::promise<void> barrier)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    barrier.set_value();
}
 
int main()
{
    // Demonstrate using promise<int> to transmit a result between threads.
    std::vector<int> numbers = { 1, 2, 3, 4, 5, 6 };
    std::promise<int> accumulate_promise;
    std::future<int> accumulate_future = accumulate_promise.get_future();
    std::thread work_thread(accumulate, numbers.begin(), numbers.end(),
                            std::move(accumulate_promise));
 
    // future::get() will wait until the future has a valid result and retrieves it.
    // Calling wait() before get() is not needed
    //accumulate_future.wait();  // wait for result
    std::cout << "result=" << accumulate_future.get() << '\n';
    work_thread.join();  // wait for thread completion
 
    // Demonstrate using promise<void> to signal state between threads.
    std::promise<void> barrier;
    std::future<void> barrier_future = barrier.get_future();
    std::thread new_work_thread(do_work, std::move(barrier));
    barrier_future.wait();
    new_work_thread.join();
}*/