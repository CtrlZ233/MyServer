#ifndef SAFE_QUEUE_H_
#define SAFE_QUEUE_H_

#include <queue>
#include <mutex>
namespace SafeContainer{

template<class T>
class SafeQueue{
public:
    SafeQueue() {}
    SafeQueue(SafeQueue & sq) = delete;
    SafeQueue & operator = (const SafeQueue & sq) = delete;

    void push(const T & t) {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(t);
    }

    bool pop(T & t) {
        std::lock_guard<std::mutex> lock(mutex_);
        if(!queue_.empty()) {
            t = std::move(queue_.front());
            queue_.pop();
            return true;
        }
        return false;
        
    }
    bool empty() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.empty();
    }

private:
    std::queue<T> queue_;
    std::mutex mutex_;
};

}

#endif