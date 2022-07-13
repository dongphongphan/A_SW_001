// g++ -std=c++11 -o thread_pool thread_pool.cpp

#include <stdio.h>
#include <vector>
#include <thread>
#include <future>
#include <unistd.h>

//#include <dispatch/dispatch.h>
#include <semaphore.h>

#include <iostream>
//#include <numeric>
//#include <chrono>
//#include <algorithm>
//#include <functional>

#define NUM_THREAD 10

class myThread
{
    int n;
    //std::condition_variable cv;
    //int var;
    //std::mutex mtx1;
    sem_t* update_sem;
    sem_t* fetch_sem;

    void printFoo(std::string str){std::cout << str;}
public:
    myThread(int in):
        n(in)//,var(0)
    {
        sem_unlink("update_sem");
        sem_unlink("fetch_sem");
        update_sem = sem_open("update_sem", O_CREAT, 0, 1);
        fetch_sem =  sem_open("fetch_sem",  O_CREAT, 0, 0);  
    }
    ~myThread(){}
    int update(int i)
    {
        sem_wait(update_sem);
        //std::unique_lock<std::mutex> lck(mtx1);
        //while(var != 0){ cv.wait(lck);}
        printFoo("Update");
        //var = 1;
        //cv.notify_one();
        sem_post(fetch_sem);
        return i;
    }
    int fetch(int i)
    {
        sem_wait(fetch_sem);
        //std::unique_lock<std::mutex> lck(mtx1);
        //while(var != 1) cv.wait(lck);
        printFoo("Fetch\n");
        //var = 0;
        //cv.notify_one();
        sem_post(update_sem);
        return i;
    }

    void start()
    {
        for(int i = 0; i < NUM_THREAD; i++)
        {
            std::thread t1( [this,i] () { return this->update(i); });
            std::thread t2( [this,i] () {return this->fetch(i); });
            t1.join();
            t2.join();
        }
    }

};
using FuncType = std::function<int (const std::string&)>;
int main(void)
{
    myThread t(NUM_THREAD);
    t.start();

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