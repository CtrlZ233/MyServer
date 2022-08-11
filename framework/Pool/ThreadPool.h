#ifndef THREAD_POOL_H_
#define THREAD_POOL_H_

#include <thread>
#include <vector>
#include <functional>
#include <future>
#include <map>
#include "SafeList.h"
namespace ThreadUtils{

    class ThreadPool;

    class ThreadObject {
    public:
        ThreadObject(ThreadPool *threadPool);

        void operator() ();

    private:
        ThreadPool* p_threadPool_; 
    };


    typedef std::function<void()> Task;

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

        template <typename F, typename... Args>
        auto AddTask(F&& f, Args&&... args) -> std::future<decltype(f(args...))> {
            std::function<decltype(f(args...))()> func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
            auto ptask = std::make_shared<std::packaged_task<decltype(f(args...))()>>(func);
            
            std::function<void()> wrapper_func = [ptask]() { (*ptask)(); };
            tasks_.push_back(wrapper_func);
            conditionLock_.notify_one();
            return ptask->get_future();
        }

    private:
        int maxNum_;
        std::vector<std::thread> threads_;
        SafeContainer::SafeList<Task> tasks_;
        bool isShutDown_;
        std::condition_variable conditionLock_;
        std::mutex conditionMutex_;
    };

}

#endif
