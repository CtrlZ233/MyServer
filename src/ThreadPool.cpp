#include "ThreadPool.h"
#include <iostream>
namespace ThreadUtils {

ThreadObject::ThreadObject(int id, ThreadPool *threadPool) : id_(id){    
    p_threadPool_ = threadPool;
}

void ThreadObject::operator() () {
    std::function<void()> func;
    Task t(nullptr, -1);
    bool flag;
    
    while (!p_threadPool_->IsShutDown()) {
        {
            std::unique_lock<std::mutex> lock(p_threadPool_->conditionMutex_); // 加锁防止读脏数据，虽然用了SafeQueue后不可能能读脏数据
            while (p_threadPool_->tasks_.empty() && !p_threadPool_->IsShutDown()) { // 使用while防止spurious wakeup
                p_threadPool_->conditionLock_.wait(lock);
            }
            t = p_threadPool_->tasks_.front();
            p_threadPool_->tasks_.pop_front();
            func = t.func_;
            p_threadPool_->taskIDsInThreads_[this->id_].setValue(t.taskID_);
            p_threadPool_->threadTaskQuitFlags_[this->id_].setValue(false);
        }
        {
            // printf("processing...\n");
            func();
            p_threadPool_->taskIDsInThreads_[this->id_].setValue(-1);
        }
    }
}

ThreadPool::ThreadPool(const int maxNum) : threads_(std::vector<std::thread>(maxNum)), isShutDown_(false) {
    threadTaskQuitFlags_ = std::vector<SafeContainer::SafeValue<bool>> (maxNum);
    taskIDsInThreads_ = std::vector<SafeContainer::SafeValue<int>> (maxNum);
    maxNum_ = maxNum;
    for (int i = 0; i < maxNum; ++i) {
        std::cout << i << std::endl;
        threadTaskQuitFlags_[i].setValue(false);
        taskIDsInThreads_[i].setValue(-1);
    }
}

void ThreadPool::init() {
    for(int i = 0; i < threads_.size(); ++i) {
        auto t = ThreadObject(i, this);
        threads_[i] = std::thread(t);
        threadTaskQuitFlags_[i].setValue(false);
        auto id = threads_[i].get_id();
        mp[*(uint32_t *)(&id)] = i;
    }
    taskIDs_ = 0;
}

void ThreadPool::DeleteTask(int taskID) {
    // search the running threads;
    for (int i = 0; i < taskIDsInThreads_.size(); ++i) {
        if (taskIDsInThreads_[i].getValue() == taskID) {
            threadTaskQuitFlags_[i].setValue(true);
            return;
        }
    }
    Task t(nullptr, taskID);
    tasks_.deleteElem(t);
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