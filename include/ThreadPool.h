#ifndef THREAD_POOL_H_
#define THREAD_POOL_H_

#include <thread>
#include <vector>
#include <functional>
#include <future>
#include <map>
#include "SafeQueue.h"
#include "SafeList.h"
namespace ThreadUtils{
class ThreadPool;

class ThreadObject {
public:
    ThreadObject(int id, ThreadPool *threadPool);

    void operator() ();

private:
    uint32_t id_;
    ThreadPool* p_threadPool_; 
};

struct Task
{
    std::function<void()> func_;
    int taskID_;
    Task(std::function<void()> func, int taskID) : func_(func), taskID_(taskID) {} 
    bool operator == (Task t) {
        return taskID_ == t.taskID_;
    }
};



class ThreadPool {  
public:
    friend class ThreadObject;
    explicit ThreadPool(const int maxNum);
    ThreadPool (const ThreadPool &) = delete;
    ThreadPool & operator = (const ThreadPool &) = delete;

    virtual ~ThreadPool() {
        ShutDown();
    }

    void init();

    bool IsShutDown() const { return isShutDown_; }
    void ShutDown();
    void DeleteTask(int taskID);

    template <typename F, typename... Args>
    auto AddTask(F&& f, Args&&... args) -> std::pair<std::future<decltype(f(args...))>, int> {
        std::function<decltype(f(args...))()> func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
        auto ptask = std::make_shared<std::packaged_task<decltype(f(args...))()>>(func);
        
        std::function<void()> wrapper_func = [ptask]() { (*ptask)(); };
        int taskID = -1;
        int d = 1;
        tasks_.push_back(Task(wrapper_func, taskIDs_));
        {
            std::lock_guard<std::mutex> lock(taskIDMutex_);
            taskID = taskIDs_;
            ++taskIDs_;
        }
        conditionLock_.notify_one();
        return std::make_pair(ptask->get_future(), taskID);
    }

private:
    int maxNum_;
    std::vector<std::thread> threads_;
    std::vector<SafeContainer::SafeValue<int>> taskIDsInThreads_;
    std::vector<SafeContainer::SafeValue<bool>> threadTaskQuitFlags_;
    std::map<uint32_t, int> mp;
    SafeContainer::SafeList<Task> tasks_;
    bool isShutDown_;
    std::condition_variable conditionLock_;
    std::mutex conditionMutex_;
    int taskIDs_;
    std::mutex taskIDMutex_;
};

}

#endif
