//
// Created by had on 2/17/17.
//

#include "ThreadPool.h"
#include "Thread.h"

ThreadPool::ThreadPool(string& name)
        :running_(false),name_(name),
         ML_(), NoEmpty(ML_),NoFull(ML_){

}

ThreadPool::~ThreadPool() {

}

size_t ThreadPool::queueSize() const {
    return 0;
}

void ThreadPool::start(int numThreads) {
    assert(threads.empty());
    running_ = true;
    Task runinthread = bind(&ThreadPool::runInThread, this);
    for (int i = 0; i < numThreads; ++i) {
        char Num[4];
        snprintf(Num,4,"%d",i+1);
        threads.push_back(
                unique_ptr<Thread>(new Thread(runinthread, name_+Num)));
        threads[i]->start();
    }
}

void ThreadPool::stop() {

}

void ThreadPool::run(const ThreadPool::Task &f) {
    //add
    if(maxQueueSize_ > 0){

    }
}

bool ThreadPool::isFull() const {
    return false;
}

void ThreadPool::runInThread() {

}

ThreadPool::Task ThreadPool::take() {
    MutexLockGuard MLG(ML_);
    while(tasks.empty()){
        NoEmpty.wait();
    }
    Task task;
    if(!tasks.empty()){
        task = tasks.front();
        tasks.pop_front();
        if(maxQueueSize_ > 0){
            NoFull.notify();
        }
    }
}
