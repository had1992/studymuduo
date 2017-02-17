//
// Created by had on 2/17/17.
//

#ifndef MUDUO_THREAD_H
#define MUDUO_THREAD_H

#include <string>
#include <functional>
#include <pthread.h>

using namespace std;

class Thread {
public:
    typedef function<void()> Func;
    explicit Thread(const Func& func, const string& name);
    ~Thread();
    void start();
    int join();
private:
    void* runInThread(void *);

private:
    Func func_;
    bool       started_;
    bool       joined_;
    pthread_t  pthreadId_;
    shared_ptr<pid_t > tid_;
    string name_;
};


#endif //MUDUO_THREAD_H
