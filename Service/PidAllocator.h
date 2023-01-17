#ifndef PID_ALLOCATOR_H_
#define PID_ALLOCATOR_H_

#include <vector>
#include <mutex>

namespace Utils {

    class PidAllocator {
    public:
        static PidAllocator& Instance();

        unsigned int alloc();

        void dealloc(unsigned int id);

        PidAllocator(PidAllocator &other) = delete;

        PidAllocator operator = (PidAllocator &other) = delete;

    private:

        PidAllocator();

        unsigned int current;
        std::vector<unsigned int> recycled;
        std::mutex modifyMutex;

    };

    unsigned int PidAlloc();

    void PidDealloc(unsigned int);

}



#endif