#ifndef TIMER_H_
#define TIMER_H_

#include <vector>
#include <list>
#include <functional>
#include <memory>
#include <iostream>
namespace Timer{
using Task = std::function<void()>;
// 只执行一次，每隔一段时间执行一次（有限次、无限次）
struct TimerNode {
    TimerNode (Task t, uint32_t interval, uint32_t timeStamp, 
                size_t repeat, bool aways, bool shutDown = false) :
                task_(t), interval_(interval), timeStamp_(timeStamp),
                repeat_(repeat), always_(aways), shutDown_(shutDown) {}
    Task task_;
    uint32_t interval_;
    uint32_t timeStamp_;
    size_t repeat_;
    bool always_;
    bool shutDown_;
};

using TimerNodePtr =  std::shared_ptr<TimerNode>;
using TimerPlate = std::vector<std::list<TimerNodePtr> >;


// 4级计时器，最小粒度为10 ms, 每级的槽位分别为 8 8 8 8（2的幂次），总共可表示2^32粒度的时间戳。
const int SHIFT = (1 << 8);
const int PlATE_NUM = 4;
const int WIDTH = 8; //  32 / 4 = 8
class Timer{
public:
    
    Timer();
    void TimerInit();
    TimerNodePtr AddTimer(Task t, uint32_t interval);
    TimerNodePtr AddTimer(Task t, uint32_t interval, size_t repeat);
    void DeleteTimer(TimerNodePtr pnode);
    // void Start();
    void Update();
private:
    
    void ReHash(TimerNodePtr pnode);
    void ReHash(int index);
    uint32_t curTimeStamp_; // 当前时间戳
    std::vector<TimerPlate> timer_;

};


}

#endif