#ifndef OBSERVER_H_
#define OBSERVER_H_
#include <set>
#include <memory>
#include <mutex>
namespace ObserverPattern {

    class Observer;

    class Subject {
    public:
        void add(std::shared_ptr<Observer> obs_p);
        void remove(std::shared_ptr<Observer> obs_p);

        // How to know the observers all is alive? using smart pointer!
        void notify();

    private:
        mutable std::mutex mutex_;
        std::set<std::weak_ptr<Observer>> observers_;
    };

    class Observer {
    public:
        // 不能调用subject_->add和remove，会导致死锁
        // 避免长时间的response操作，将response中的耗时操作放入线程池
        virtual void response() = 0;
        void observe(std::shared_ptr<Subject> sub_);

        virtual ~Observer();
    private:
        std::weak_ptr<Subject> subject_;
    };

}


#endif