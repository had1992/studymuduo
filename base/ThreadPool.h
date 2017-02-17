//
// Created by had on 2/17/17.
//

#ifndef MUDUO_THREADPOOL_H
#define MUDUO_THREADPOOL_H

#include <deque>
#include <functional>
#include <string>
#include <memory>
#include <vector>

#include "../Mutex.h"
#include "../Condition.h"
#include "Thread.h"

using namespace std;

class ThreadPool {
public:
    typedef function<void()> Task;
    ThreadPool(string& name);
    ~ThreadPool();

    size_t queueSize() const;

    void start(int numThreads);
    void stop();
    void run(const Task& f);

private:
    bool isFull() const;
    void runInThread();
    Task take();

private:
    bool running_;
    string name_;

    size_t  maxQueueSize_;
    deque<Task> tasks;

//    vector<Thread*> threads;
    vector<unique_ptr<Thread> > threads;

    MutexLock ML_;
    Condition NoFull;
    Condition NoEmpty;
};


#endif //MUDUO_THREADPOOL_H
