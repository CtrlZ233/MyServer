#include "Timer.h"
#include <unistd.h>
namespace Timer {

    Timer::Timer() : curTimeStamp_(0), shutDown_(false) {
        timer_.resize(PlATE_NUM);
        for (auto & p : timer_) {
            // 为什么要使用如此别扭的用法？ 因为vector的元素要求可移动插入和拷贝构造，
            // 但是线程安全的容器不支持移动和拷贝。因此使用指向该容器的指针
            for (int i = 0; i < SHIFT; ++i) {
                p.push_back(ListPtr(new SafeContainer::SafeList<TimerNodePtr>()));
            }
        }
    }

    Timer::~Timer() {
        shutDown_ = true;
    }

    void Timer::TimerInit() {
        curTimeStamp_ = 0;
        for (auto & p : timer_) {
            for (auto & q : p) {
                q->clear();
            }
        }
    }

    WeakTimerNodePtr Timer::AddTimer(Task t, uint32_t interval, size_t repeat) {
        if (interval <= 0) {
            t();
            return WeakTimerNodePtr();
        }
        
        uint32_t taskTimeStamp = curTimeStamp_ + interval;
        auto elem = std::make_shared<TimerNode>(t, interval, taskTimeStamp, repeat, false);
        
        ReHash(elem);
        return elem;
    }   

    WeakTimerNodePtr Timer::AddTimer(Task t, uint32_t interval) { // 使用WeakPtr减短TimerNode对象的生命周期
        return AddTimer(t, interval, 1);
    }

    void Timer::DeleteTimer(WeakTimerNodePtr pnode) {
        TimerNodePtr obj(pnode.lock());         // 尝试提升，提升失败则说明该定时器节点已经失效。
        if (obj){
            obj->shutDown_ = true;
        }
        
    }

    void Timer::ReHash(TimerNodePtr pnode) {
        uint32_t taskTimeStamp = pnode->timeStamp_;
        uint32_t curTimeStamp = curTimeStamp_; // 获取当前的时间戳
        int i = 0;

        // 寻找任务时间戳和当前时间戳第一个不相同的时针。
        for (; i < PlATE_NUM; ++i) {
            if (taskTimeStamp >> (WIDTH * (PlATE_NUM - i - 1) ) != 
                curTimeStamp >> (WIDTH * (PlATE_NUM - i - 1) ) ) {
                    break;
                }
        }
        if (taskTimeStamp != curTimeStamp)
            i++;
        // printf("%d %d\n", PlATE_NUM - i, (taskTimeStamp >> (PlATE_NUM - i)) & (SHIFT - 1));
        
        // 将任务时间戳Hash到它应该的位置
        timer_[PlATE_NUM - i][(taskTimeStamp >> (WIDTH * (PlATE_NUM - i))) & (SHIFT - 1)]->push_back(pnode);
    }


    // 在每次当前时间戳递增后，都应该查看是否进位，如果进位，则需要对进位的slot中的时间戳进行重Hash.
    void Timer::ReHash(int i) {
        if (i > 3) return;
        ReHash(i + 1);
        // printf("%d\n", curTimeStamp_);
        if ((curTimeStamp_ & ((1 << (WIDTH * i)) - 1)) == 0) {
            auto slot = timer_[i][(curTimeStamp_ >> (WIDTH * i)) & (SHIFT - 1)]->getList();
            for (auto elem : slot) {
                if (!elem->shutDown_) {
                    ReHash(elem);
                }
            }
            timer_[i][(curTimeStamp_ >> (WIDTH * i)) & (SHIFT - 1)]->clear();
        }
    }


    // 由于Update只会在一个线程中运行中运行，因此可能产生线程安全的操作是Update与AddTimer操作的线程安全
    // DeleteTimer仅对bool赋值，是原子操作。Update涉及到的push_back和clear，与AddTimer之间的push_back之间的冲突。
    // 且冲突进发生在list上，可采用SafeList解决。
    // 最后，由于list动态分配内存，AddTimer的push_back操作不会导致遍历该list时的迭代器失效。
    void Timer::Update() {
        
        auto slot = timer_[0][curTimeStamp_ & (SHIFT - 1)]->getList();
        for (auto elem : slot) {
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
        timer_[0][curTimeStamp_ & (SHIFT - 1)]->clear();
        curTimeStamp_++;
        // printf("%d\n", slot.size());
        ReHash(1);
    }

    void Timer::Start(int interval) {
        while(!shutDown_) {
            usleep(interval);
            Update();
        }
    }

    void Timer::ShutDown() {
        shutDown_ = true;
    }

}