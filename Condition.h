//
// Created by had on 2/11/17.
//

#ifndef MUDUO_CONDITION_H
#define MUDUO_CONDITION_H

#include "uncopyable.h"
#include "Mutex.h"

class Condition:public uncopyable{
public:
    Condition(MutexLock& ML):ML_(ML){
        pthread_cond_init(&pcond_,NULL);
    }
    void wait(){
        pthread_cond_wait(&pcond_,ML_.getPthreadMutex());
    }
    void notify(){
        pthread_cond_signal(&pcond_);
    }
    void notifyall(){
        pthread_cond_broadcast(&pcond_);
    }
private:
    MutexLock& ML_;
    pthread_cond_t pcond_;
};

#endif //MUDUO_CONDITION_H
