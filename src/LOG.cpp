#include "LOG.h"
namespace Utils{

const int LOG::maxSize = 1024;


// LOG:: public method

LOG::LOG(std::string filename, int maxWaitSeconds) : logFilePath_(filename), maxWaitSeconds_(maxWaitSeconds){
    fd_.open(filename, std::ios::out);
    if (!fd_) {
        printf("open log file failed.\n");
        exit(-1);
    }
    isShutDown_ = false;
    currentBuffer_ = std::unique_ptr<LogBuffer>(new LogBuffer);
    nextBuffer_ = std::unique_ptr<LogBuffer>(new LogBuffer);
}


LOG & LOG::operator << (const std::string & s ) {
    Append(s);
    return *this;
}

void LOG::ShutDown() {
    isShutDown_ = true;
    conditionLock_.notify_all();
    std::lock_guard<std::mutex> lock(currentBufferMutex_);
    WriteFile(currentBuffer_);
}

LOG:: ~LOG() {
    // 善后
    if (!isShutDown_)
        ShutDown();
    fd_.close();
}


// LOG::private method

void LOG::Append(const std::string & s) {
    if (!isShutDown_) {
        std::lock_guard<std::mutex> lock(currentBufferMutex_);
        if (currentBuffer_->size() >= maxSize) {
            std::lock_guard<std::mutex> lock(nextBufferMutex_);
            currentBuffer_.swap(nextBuffer_);
            conditionLock_.notify_one();
        }
        currentBuffer_->Append(s);
    } 
}


void LOG::WriteFile() {
    while (!isShutDown_) {
        {
            std::unique_lock<std::mutex> lock(ConditionMutex_);
            if (nextBuffer_->empty()) {
                conditionLock_.wait(lock);
            }
            // 写文件
            std::lock_guard<std::mutex> lock(nextBufferMutex_);
            WriteFile(nextBuffer_);
        }
    }
}

void LOG::WriteFile(std::shared_ptr<LogBuffer> pBuffer) {
    std::lock_guard<std::mutex> lock(FileMutex_);
    if (pBuffer->size() > 0) {
        for (int i = 0; i < pBuffer->size(); ++i) {
            fd_ << pBuffer->getString(i) << std::endl;
        }
    }
}



}