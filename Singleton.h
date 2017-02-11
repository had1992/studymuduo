//
// Created by had on 2/11/17.
//

#ifndef MUDUO_SINGLETON_H
#define MUDUO_SINGLETON_H

#include <pthread.h>
#include "uncopyable.h"

template <class T>
class Singleton:public uncopyable{
public:
    static T& getInstance(){
        pthread_once(&ponce_,&Singleton::init);
    }
private:
    Singleton(){}
    ~Singleton(){}
    static void init(){
        instance_ = new T();
    }
private:
    static T* instance_;
    static pthread_once_t ponce_;
};

template <class T>
T* Singleton::instance_ = NULL;
template <class T>
pthread_once_t Singleton::ponce_ = PTHREAD_ONCE_INIT;

#endif //MUDUO_SINGLETON_H
