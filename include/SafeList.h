#ifndef SAFE_LIST_H_
#define SAFE_LIST_H_

#include <list>
#include <mutex>
#include <functional>
namespace SafeContainer{

template <typename T>
class SafeList{
public:
    SafeList<T>() {};
    SafeList(const SafeList & sl) = delete;
    SafeList & operator = (const SafeList & sl) = delete;

    void push_back(const T & t) {
        std::lock_guard<std::mutex> lock(mutex_);
        list_.push_back(t);
    }

    void push_back(T && t) {
        std::lock_guard<std::mutex> lock(mutex_);
        list_.push_back(std::move(t));
    }
    
    T& front() {
        std::lock_guard<std::mutex> lock(mutex_);
        return list_.front();
    }

    void pop_front() {
        std::lock_guard<std::mutex> lock(mutex_);
        list_.pop_front();
    }

    void clear() {
        std::lock_guard<std::mutex> lock(mutex_);
        list_.clear();
    }

    int size() {
        std::lock_guard<std::mutex> lock(mutex_);
        return list_.size();
    }

    // T & operator [] (size_t i) {
    //     return list_.
    // }
    void traverse(std::function<void (T)> func) {
        std::lock_guard<std::mutex> lock(mutex_);
        for (auto & i : list_) {
            func(i);
        }
    }

    std::list<T> getList() {
        std::lock_guard<std::mutex> lock(mutex_);
        return list_;
    }

    bool empty()  {
        return size() == 0;
    }

private:
    std::list<T> list_;
    std::mutex mutex_;
};

}


#endif