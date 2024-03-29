#ifndef I_TIMER_LISTENER_H_
#define I_TIMER_LISTENER_H_

#include "Timer.h"

namespace Timer {
    class ITimerListener {
        public:
            virtual void HandleTimeOut() = 0;

            explicit ITimerListener(unsigned int time_val);

            void ResetTimer();

            void Start();

            virtual ~ITimerListener() = default;

        private:
            uint32_t interval;
            WeakTimerNodePtr curTimerNode;
    };
}



#endif