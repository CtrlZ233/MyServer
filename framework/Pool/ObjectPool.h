#ifndef OBJECT_POOL_H_
#define OBJECT_POOL_H_

#include <functional>
#include <memory>
#include <iostream>
#include "SafeList.h"

namespace ObjectPool {

    template <typename T>
    class ObjectPool {
    public: 
        ObjectPool(size_t initial_size = 10);

        std::unique_ptr<T, std::function<void(T*)>> acquire();

        bool empty()  {
            return pool_.empty();
        }

        size_t size() const {
            return pool_.size();
        }

    private: 
        size_t max_size_;
        size_t capicity_;
        size_t min_size_;
        std::mutex mutex_;
        SafeContainer::SafeList<std::unique_ptr<T>> pool_;
        // std::list<std::unique_ptr<T>> pool_;
    };




    template <typename T>
    ObjectPool<T>::ObjectPool(const size_t initial_size) {
        if (initial_size >= 1000) {
            std::cout << "the initial size of object pool is too large!" << std::endl;
        }
        for (size_t i = 0; i < initial_size; ++i) {
            pool_.push_back(std::make_unique<T>());
        }
    }

    template <typename T>
    std::unique_ptr<T, std::function<void(T*)>> ObjectPool<T>::acquire() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (empty()) {
            return nullptr;
        }

        std::unique_ptr<T, std::function<void(T*)>> ptr (pool_.front().release(), [this](T* t) {
            pool_.push_back(std::unique_ptr<T>(t));
        });

        pool_.pop_front();
        return ptr;
    }

}


#endif