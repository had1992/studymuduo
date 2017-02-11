//
// Created by had on 2/11/17.
//

#ifndef MUDUO_UNCOPYABLE_H
#define MUDUO_UNCOPYABLE_H

class uncopyable{
protected:
    uncopyable(){}
    virtual ~uncopyable(){}
private:
    uncopyable(const uncopyable&) = delete;
    uncopyable& operator=(const uncopyable&) = delete;
};

#endif //MUDUO_UNCOPYABLE_H
