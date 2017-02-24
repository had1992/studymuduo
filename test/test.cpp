//
// Created by had on 2/15/17.
//

#include <iostream>
#include "../reactor/EventLoop.h"
#include "../reactor/Channel.h"

using namespace std;

EventLoop eventloop;

int main(){
    Channel channel(&eventloop,1);
    channel.enableReading();
    channel.disableWriting();
    channel.setReadCallback([](){
        cout << "read something" << endl;
        char * x = new char[50];
        int getcnums = read(1,x,50);
        x[getcnums-1] = '\0';
        cout << x << endl;
    });
    eventloop.loop();
}

