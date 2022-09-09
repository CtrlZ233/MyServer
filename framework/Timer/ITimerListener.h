#ifndef I_TIMER_LISTENER_H_
#define I_TIMER_LISTENER_H_

#include "Timer.h"
#include "thread"

namespace Timer {
    class ITimerListener {
        public:
            virtual void HandleTimeOut() = 0;

            ITimerListener(unsigned int time_val);

            void ResetTimer();

            virtual ~ITimerListener();

        private:
            uint32_t interval;
            Timer timer;
            WeakTimerNodePtr curTimerNode;
    };
}



#endif