//
// Created by had on 2/14/17.
//

#ifndef MUDUO_TIMESTAMP_H
#define MUDUO_TIMESTAMP_H

#include <sys/time.h>

class Timestamp{
public:
    Timestamp(unsigned long value):time_value(value){}
    ~Timestamp(){}
    static unsigned long now(){
        struct timeval tm;
        gettimeofday(&tm,NULL);
        return tm.tv_sec;
    }
private:
    unsigned long time_value;
//    static struct timeval tm;
};

//不能在头文件定义变量，不然会出现多重定义
//timeval Timestamp::tm;

#endif //MUDUO_TIMESTAMP_H
