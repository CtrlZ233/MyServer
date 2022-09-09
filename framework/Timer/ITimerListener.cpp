#include "ITimerListener.h"

namespace Timer {
    ITimerListener::ITimerListener(unsigned int time_val) : interval(time_val), timer() {
        std::thread th(&Timer::Start, &timer, 10000);
        curTimerNode = timer.AddTimer(std::bind(&ITimerListener::HandleTimeOut, this), interval, 1);
    }

    void ITimerListener::ResetTimer() {
        timer.DeleteTimer(curTimerNode);
        curTimerNode = timer.AddTimer(std::bind(&ITimerListener::HandleTimeOut, this), interval, 1);
    }

    ITimerListener::~ITimerListener() {
        timer.ShutDown();
    }
}