#include "Observer.h"
#include <iostream>
void ObserverPattern::Subject::add(std::shared_ptr<Observer> obs_p) {
    std::lock_guard<std::mutex> lock(mutex_);
    // observers_.push_back(obs_p);
    // 不可重复订阅同一个observer
    if (observers_.find(obs_p) != observers_.end()) {
        std::cout <<  "cannot subscribe repeatly!" << std::endl;
        exit(-1);
    }
    observers_.insert(obs_p);
}

void ObserverPattern::Subject::remove(std::shared_ptr<Observer> obs_p) {
    std::lock_guard<std::mutex> lock(mutex_);
    // 不可删除不存在的observer 
    auto iter = observers_.find(obs_p);
    if (iter == observers_.end()) {
        std::cout << "cannot remove invalid subscribe!" << std::endl;
        exit(-1);
    }
    observers_.erase(iter);
}

void ObserverPattern::Subject::notify() {
    std::lock_guard<std::mutex> lock(mutex_);
    for (auto iter = observers_.begin(); iter != observers_.end();) {
        std::shared_ptr<Observer> obj(iter->lock());
        if (obj) {
            obj->response();    // 此时obj不会处于正在被析构的危险情况
            ++iter;
        } else {
            iter = observers_.erase(iter);
        }
    }
}

void ObserverPattern::Observer::observe(std::shared_ptr<Subject> sub_) {
    sub_->add(std::shared_ptr<Observer>(this));
    subject_ = sub_;
}

ObserverPattern::Observer::~Observer() {
    std::shared_ptr<Subject> sub(subject_.lock());
    if (sub) {
        sub->remove(std::shared_ptr<Observer>(this));
    }
}