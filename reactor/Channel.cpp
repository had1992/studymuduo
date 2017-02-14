//
// Created by had on 2/14/17.
//

#include <poll.h>
#include "Channel.h"
#include "EventLoop.h"

const int Channel::kNoneEvent = 0;
const int Channel::kReadEvent = POLLIN | POLLPRI;
const int Channel::kWriteEvent = POLLOUT;

Channel::Channel(EventLoop *loop, int fd)
        :loop_(loop),fd_(fd),events_(0),revents_(0),index_(-1) {

}

void Channel::handleEvent() {
    if (revents_ & POLLNVAL) {
        //todo LOG_WARN
    }
    if (revents_ & (POLLERR | POLLNVAL)) {
        if (errorCallback_) errorCallback_();
    }
    if (revents_ & (POLLIN | POLLPRI | POLLRDHUP)) {
        if (readCallback_) readCallback_();
    }
    if (revents_ & POLLOUT) {
        if (writeCallback_) writeCallback_();
    }
}

void Channel::update() {
    //todo loop_->updateChannel(this);
}
