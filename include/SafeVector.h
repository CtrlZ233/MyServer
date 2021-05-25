#ifndef SAFE_VECTOR_H_
#define SAFE_VECTPR_H_

#include <vector>
#include <mutex>

namespace SafeContainer {

template <typename T>
class SafeVector {
public:
    SafeVector() {}
    SafeVector(SafeVector & sv) = delete;
    SafeVector & operator = (const SafeVector & sv) = delete;

    void push_back(const T & t) {
        std::lock_guard<std::mutex> lock(mutex_);
        vector_.push_back(t);
    }

    void clear() {
        std::lock_guard<std::mutex> lock(mutex_);
        vector_.clear();
    }

    void reserve(int size) {
        std::lock_guard<std::mutex> lock(mutex_);
        vector_.reserve(size);
    }

    void swap(SafeVector<T> & sv) {
        std::lock_guard<std::mutex> lock(mutex_);
        std::
        vector_.swap(sv.vector_);
    }

    int size() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return vector_.size();
    }

    T & operator [](size_t i) {
        return vector_[i];          // maybe segment fault
    }


private:
    std::mutex mutex_;
    std::vector<T> vector_;
};


}


#endif