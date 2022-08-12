#include "ThreadPool.h"
#include <iostream>
namespace ThreadUtils {

    ThreadObject::ThreadObject(ThreadPool *threadPool) {    
        p_threadPool_ = threadPool;
    }

    void ThreadObject::operator() () {
        
        while (!p_threadPool_->IsShutDown()) {
            std::function<void()> func;
            {
                
                // 加锁防止读脏数据，虽然用了SafeQueue后不可能能读脏数据
                std::unique_lock<std::mutex> lock(p_threadPool_->conditionMutex_);
                // 使用while防止spurious wakeup
                while (p_threadPool_->tasks_.empty() && !p_threadPool_->IsShutDown()) {
                    p_threadPool_->conditionLock_.wait(lock);
                }
                Task t = p_threadPool_->tasks_.front();
                p_threadPool_->tasks_.pop_front();
                func = t;
            }
            {
                // printf("processing...\n");
                func();
            }
        }
    }

    ThreadPool::ThreadPool(const int maxNum) : threads_(std::vector<std::thread>(maxNum)), isShutDown_(false) {
        maxNum_ = maxNum;
    }

    void ThreadPool::init() {
        for(int i = 0; i < threads_.size(); ++i) {
            auto t = ThreadObject(this);
            threads_[i] = std::thread(t);
        }
    }

    void ThreadPool::ShutDown() {
        isShutDown_ = true;
        // printf("ShutDowning...\n");
        conditionLock_.notify_all();
        for (int i = 0; i < threads_.size(); ++i) {
            if (threads_[i].joinable()) {
                threads_[i].join();
            }
        }
    }

}