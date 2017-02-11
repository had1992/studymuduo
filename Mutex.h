//
// Created by had on 2/11/17.
//

#ifndef MUDUO_MUTEX_H
#define MUDUO_MUTEX_H

#include <pthread.h>
#include <assert.h>
#include <unistd.h>
#include <syscall.h>
#include "uncopyable.h"

class MutexLock:public uncopyable{
public:
    MutexLock():holder_(0){
        pthread_mutex_init(&mutex_,NULL);
    }
    ~MutexLock(){
        assert(holder_==0);
        pthread_mutex_destroy(&mutex_);
    }
public:
    void lock(){
        pthread_mutex_lock(&mutex_);
        holder_ = (pid_t)syscall(__NR_gettid);
    }
    void unlock(){
        holder_ = 0;
        pthread_mutex_unlock(&mutex_);
    }
    bool isLockedByThisThread(){
        return holder_== (pid_t)syscall(__NR_gettid);
    }
    pthread_mutex_t* getPthreadMutex(){
        return &mutex_;
    }
private:
    pthread_mutex_t mutex_;
    pid_t holder_;
};

class MutexLockGuard:public uncopyable{
public:
    MutexLockGuard(MutexLock& mutex):mutex_(mutex){
        mutex_.lock();
    }
    ~MutexLockGuard(){
        mutex_.unlock();
    }
private:
    MutexLock& mutex_;
};

#define MutexLockGuard(x) assert(false)

#endif //MUDUO_MUTEX_H
