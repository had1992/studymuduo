//
// Created by had on 2/17/17.
//
#include <assert.h>
#include <memory>
#include <unistd.h>
#include <sys/syscall.h>
#include <exception>
#include "Thread.h"

struct ThreadData
{
    typedef Thread::Func ThreadFunc;
    ThreadFunc func_;
    string name_;
    weak_ptr<pid_t> wkTid_;

    ThreadData(const ThreadFunc& func,
               const string& name,
               const shared_ptr<pid_t>& tid)
            : func_(func),
              name_(name),
              wkTid_(tid)
    { }
    void runInThread()
    {
        pid_t tid = static_cast<pid_t>(syscall(__NR_gettid));
        shared_ptr<pid_t> ptid = wkTid_.lock();
        if (ptid)
        {
            *ptid = tid;
            ptid.reset();
        }
        func_();
    }
};

void* startThread(void* obj)
{
    ThreadData* data = static_cast<ThreadData*>(obj);
    data->runInThread();
    delete data;
    return NULL;
}

Thread::Thread(const Thread::Func &func, const string &name)
        :func_(func),
         started_(false),
         joined_(false),
         pthreadId_(0),
         tid_(new pid_t(0)),
         name_(name){

}

Thread::~Thread() {

}

void *Thread::runInThread(void *) {
    func_();
    return NULL;
}

void Thread::start() {
    assert(!started_);
    started_ = true;
    ThreadData * threaddata = new ThreadData(func_,name_,tid_);
    if(pthread_create(&pthreadId_,NULL,&startThread,threaddata)){
        started_ = false;
        delete threaddata;
        //todo log_fail
    }
}

int Thread::join() {
    assert(started_);
    assert(!joined_);
    joined_ = true;
    return pthread_join(pthreadId_, NULL);
}
