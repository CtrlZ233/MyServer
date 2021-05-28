#include "Timer.h"
namespace Timer {

Timer::Timer() : curTimeStamp_(0) {
    timer_.resize(PlATE_NUM);
    for (auto & p : timer_) {
        p.resize(SHIFT);
    }
}

void Timer::TimerInit() {
    curTimeStamp_ = 0;
    for (auto & p : timer_) {
        for (auto & q : p) {
            q.clear();
        }
    }
}

TimerNodePtr Timer::AddTimer(Task t, uint32_t interval, size_t repeat) {
    if (interval <= 0) {
        t();
        return TimerNodePtr();
    }
    
    uint32_t taskTimeStamp = curTimeStamp_ + interval;
    auto elem = std::make_shared<TimerNode>(t, interval, taskTimeStamp, repeat, false);
    
    ReHash(elem);
    return elem;
}

TimerNodePtr Timer::AddTimer(Task t, uint32_t interval) {
    return AddTimer(t, interval, 1);
}

void Timer::DeleteTimer(TimerNodePtr pnode) {
    pnode->shutDown_ = true;
}

void Timer::ReHash(TimerNodePtr pnode) {
    uint32_t taskTimeStamp = pnode->timeStamp_;
    int i = 0;
    for (; i < PlATE_NUM; ++i) {
        // printf("%d, %d\n", taskTimeStamp >> (WIDTH * (PlATE_NUM - i - 1) ), curTimeStamp_ >> (WIDTH * (PlATE_NUM - i - 1) ));
        if (taskTimeStamp >> (WIDTH * (PlATE_NUM - i - 1) ) != 
            curTimeStamp_ >> (WIDTH * (PlATE_NUM - i - 1) ) ) {
                break;
            }
    }
    if (taskTimeStamp != curTimeStamp_)
        i++;
    // printf("%d %d\n", PlATE_NUM - i, (taskTimeStamp >> (PlATE_NUM - i)) & (SHIFT - 1));
    timer_[PlATE_NUM - i][(taskTimeStamp >> (WIDTH * (PlATE_NUM - i))) & (SHIFT - 1)].push_back(pnode);
}

void Timer::ReHash(int i) {
    if (i > 3) return;
    ReHash(i + 1);
    // printf("%d\n", curTimeStamp_);
    if ((curTimeStamp_ & ((1 << (WIDTH * i)) - 1)) == 0) {
        auto & slot = timer_[i][(curTimeStamp_ >> (WIDTH * i)) & (SHIFT - 1)];
        for (auto elem : slot) {
            if (!elem->shutDown_) {
                ReHash(elem);
            }
        }
        slot.clear();
    }
}

void Timer::Update() {
    
    auto & slot =  timer_[0][curTimeStamp_ & (SHIFT - 1)];
    for (auto  elem : slot) {
        if (!elem->shutDown_) {
            elem->task_();
            
            elem->repeat_--;
            // printf("%d\n", curTimeStamp_);
            if (elem->repeat_ > 0) {
                elem->timeStamp_ = curTimeStamp_ + elem->interval_;
                ReHash(elem);
            }
        }
    }
    slot.clear();
    curTimeStamp_++;
    // printf("%d\n", slot.size());
    ReHash(1);
}



}
