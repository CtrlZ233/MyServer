#include "PidAllocator.h"

namespace Utils {

    PidAllocator::PidAllocator() {
        current = 1;
    }

    unsigned int PidAllocator::alloc() {
        std::unique_lock<std::mutex> lock(modifyMutex);
        if (!recycled.empty()) {
            auto ans = recycled.back();
            recycled.pop_back();
            return ans;;
        }
        current++;
        return current - 1;
    }

    PidAllocator &PidAllocator::Instance() {
        static PidAllocator instance;
        return instance;
    }

    void PidAllocator::dealloc(unsigned int id) {
        printf("delloc pid: %u\n", id);
        std::unique_lock<std::mutex> lock(modifyMutex);
        recycled.push_back(id);
    }

    unsigned int PidAlloc() {
        return PidAllocator::Instance().alloc();
    }

    void PidDealloc(unsigned int pid) {
        PidAllocator::Instance().dealloc(pid);
    }

}