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
        gettimeofday(&tm,NULL);
        return tm.tv_sec;
    }
private:
    unsigned long time_value;
    static struct timeval tm;
};

timeval Timestamp::tm;

#endif //MUDUO_TIMESTAMP_H
