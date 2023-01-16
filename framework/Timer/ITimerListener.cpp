#include "ITimerListener.h"
#include <thread>

namespace Timer {
    static Timer GLOABL_TIMER;
    static std::thread th(&Timer::Start, &GLOABL_TIMER, 10000);
    ITimerListener::ITimerListener(unsigned int time_val) : interval(time_val) {}

    void ITimerListener::ResetTimer() {
        GLOABL_TIMER.DeleteTimer(curTimerNode);
        curTimerNode = GLOABL_TIMER.AddTimer(std::bind(&ITimerListener::HandleTimeOut, this), interval, 1);
    }

    void ITimerListener::Start() {
        curTimerNode = GLOABL_TIMER.AddTimer(std::bind(&ITimerListener::HandleTimeOut, this), interval, 1);
    }

    ITimerListener::~ITimerListener() {}
}