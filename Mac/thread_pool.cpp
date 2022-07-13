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

#define NUM_THREAD 4
 #define TASK_POOL 10
typedef struct task
{
    void (*FuncP) (int i);
    int in;
}Task;

void sampleTask(int i)
{
    std::cout<<"Exe Tsk "<< i << std::endl;
    sleep(1);
}
class myThread
{
    int n;
    std::condition_variable taskQueueCV;
    int var;
    std::mutex taskQueueMtx;

    Task taskList[TASK_POOL];
    int taskCount;

    std::thread threadPool[NUM_THREAD];

    void printFoo(std::string str){std::cout << str;}

    void executeTask(int idx)
    {
        while(1)
        {
            std::unique_lock<std::mutex> lck(taskQueueMtx);
            if(taskCount > 0)
            {
                taskCount--;
                lck.unlock();
                Task tem = taskList[taskCount];
                tem.FuncP(tem.in);
            }
            else
            {
                std::cout<<"wait T"<< idx << std::endl;
                taskQueueCV.wait(lck);
                std::cout<<"wkup T"<< idx << std::endl;
            }
        }
    }
public:
    myThread(int in):
        n(in),var(0),taskCount(0)
    {
    }
    ~myThread(){}
    bool insertTask(Task& in)
    {
        std::unique_lock<std::mutex> lck(taskQueueMtx);
        if(taskCount > TASK_POOL) {
            std::cout<<"insertTask err Task queue full\n";
            return false;
        }
        taskList[taskCount].FuncP = in.FuncP;
        taskList[taskCount].in = in.in;
        taskCount++;
        std::cout<<"insertTsk:"<< in.in << " cnt:"<< taskCount<< "\n";
        lck.unlock();
        taskQueueCV.notify_all();
        return true;
    }

    void start()
    {
        std::cout<<"start\n";
        for(int i = 0; i < NUM_THREAD; i++)
        {
            threadPool[i] = std::thread{ [this,i] () { return this->executeTask(i); } };
        }
    }
    void jointT()
    {
        for(int i = 0; i < NUM_THREAD; i++)
        {
            threadPool[i].join();
        }
    }
};

void testInsertTask(myThread& t, int No)
{
    for(int i = 0; i < No; i++)
    {
        Task temp = {
            .FuncP = &sampleTask,
            .in = i
        };
        t.insertTask(temp);
    }
}
int main(void)
{
    myThread t(NUM_THREAD);
    t.start();
    std::cout<<"===Main sleep 2s\n";
    sleep(2);
    testInsertTask(t,TASK_POOL);
    std::cout<<"===Main sleep 2s\n";
    sleep(2);
    testInsertTask(t,9);
    t.jointT();
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