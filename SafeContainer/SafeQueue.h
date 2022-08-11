#ifndef SAFE_QUEUE_H_
#define SAFE_QUEUE_H_

#include <queue>
#include <mutex>
namespace SafeContainer{

    template<class T>
    class SafeQueue{
    public:
        SafeQueue() {}
        SafeQueue(const SafeQueue & sq) {
            mutex_ = std::move(sq.mutex_);
            queue_ = sq.queue_;
        }
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
        bool empty()  {
            std::lock_guard<std::mutex> lock(mutex_);
            return queue_.empty();
        }


    private:
        std::queue<T> queue_;
        std::mutex mutex_;

    };

    template <typename T>
    class SafeValue {
    public:
        SafeValue() { }
        SafeValue(T value) : value_(value) { }
        SafeValue(SafeValue && s) {
            value_ = s.value_;
        }
        T getValue() {
            std::lock_guard<std::mutex> lock(mutex_);
            return value_;
        }

        void setValue(T value) {
            std::lock_guard<std::mutex> lock(mutex_);
            value_ = value;
        }

    private:
        T value_;
        std::mutex mutex_;
    };

}

#endif