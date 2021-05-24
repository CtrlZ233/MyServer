#include "ThreadPool.h"
namespace ThreadUtils {

ThreadObject::ThreadObject(int id, ThreadPool *threadPool) : id_(id){    
    p_threadPool_ = threadPool;
}

void ThreadObject::operator() () {
    std::function<void()> func;
    bool flag;
    
    while (!p_threadPool_->IsShutDown()) {
        {
            std::unique_lock<std::mutex> lock(p_threadPool_->conditionMutex_); // 加锁防止读脏数据，虽然用了SafeQueue后不可能能读脏数据
            while (p_threadPool_->tasks_.empty()) { // 使用while防止spurious wakeup
                p_threadPool_->conditionLock_.wait(lock);
            }
            flag = p_threadPool_->tasks_.pop(func);
        }
        if (flag) {
            printf("processing...\n");
            func();
        }
    }
}

ThreadPool::ThreadPool(const int maxNum) : threads_(std::vector<std::thread>(maxNum)), isShutDown_(false) { }

void ThreadPool::init() {
    for(int i = 0; i < threads_.size(); ++i) {
        threads_[i] = std::thread(ThreadObject(i, this));
    }
}

void ThreadPool::ShutDown() {
    isShutDown_ = true;
    conditionLock_.notify_all();
    for (int i = 0; i < threads_.size(); ++i) {
        if (threads_[i].joinable()) {
            threads_[i].join();
        }
    }
}

}