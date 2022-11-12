#include "HeartBeat.h"
#include <thread>
namespace MessageHandler {
    static Timer::Timer GLOABL_TIMER;
    static std::thread th(&Timer::Timer::Start, &GLOABL_TIMER, 10000);

}