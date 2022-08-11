#ifndef PID_ALLOCATOR_H_
#define PID_ALLOCATOR_H_

#include <vector>
#include <mutex>

namespace Utils {

    class PidAllocator {
    public:
        static PidAllocator& Instance();

        unsigned int alloc();

        void delloc(unsigned int id);

    private:

        PidAllocator();

        PidAllocator(PidAllocator &other) = delete;

        PidAllocator operator = (PidAllocator &other) = delete;

        unsigned int current;
        std::vector<unsigned int> recycled;
        std::mutex modifyMutex;

    };

    unsigned int PidAlloc();

}



#endif