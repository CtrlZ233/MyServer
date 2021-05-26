#include "LOG.h"
#include <ctime>
#include <cstring>
namespace Utils{

std::string GetCurrentDateTime() {
    time_t ts=time(NULL);
    char tmp[32]{0};
    strncpy(tmp,ctime(&ts),sizeof(tmp));
    return std::string(tmp);
}

const int Log::maxSize = 1024;


// LOG:: public method

Log::Log(std::string logDir, int maxWaitSeconds) : maxWaitSeconds_(maxWaitSeconds){
    char curTime[64];
    time_t rawtime;
    struct tm *ptminfo;
    time(&rawtime);
    ptminfo = localtime(&rawtime);
    sprintf(curTime, "LOG-%02d-%02d-%02d_%02d:%02d:%02d.log", ptminfo->tm_year + 1900, ptminfo->tm_mon + 1, ptminfo->tm_mday, 
                ptminfo->tm_hour, ptminfo->tm_min, ptminfo->tm_sec);
    logFilePath_ = logDir + std::string(curTime);
    fd_.open(logFilePath_, std::ios::out);
    if (!fd_) {
        printf("open log file failed.\n");
        exit(-1);
    }
    isShutDown_ = false;
    currentBuffer_ = std::shared_ptr<LogBuffer>(new LogBuffer);
    nextBuffer_ = std::shared_ptr<LogBuffer>(new LogBuffer);
}




void Log::ShutDown() {
    isShutDown_ = true;
    conditionLock_.notify_all();
    std::lock_guard<std::mutex> lock(currentBufferMutex_);
    WriteFile(currentBuffer_);
}

Log:: ~Log() {
    // 善后
    // printf("~LOG\n");
    if (!isShutDown_){
        ShutDown();
    }
        
    fd_.close();
}




void Log::Append(const std::string & s, const std::string & fileName, const std::string & line, const std::string functionName) {
    // printf("Append\n");
    time_t ts=time(NULL);
    std::string res = GetCurrentDateTime() +  " " + fileName + " line: " + line + " " + functionName + ": " + s +"\n";
    if (!isShutDown_) {
        std::lock_guard<std::mutex> lock(currentBufferMutex_);
        if (currentBuffer_->size() >= maxSize) {
            std::lock_guard<std::mutex> lock(nextBufferMutex_);
            currentBuffer_.swap(nextBuffer_);
            conditionLock_.notify_one();
        }
        currentBuffer_->Append(res);
    } 
}


void Log::WriteFile() {
    while (!isShutDown_) {
        {
            std::unique_lock<std::mutex> lock1(ConditionMutex_);
            if (nextBuffer_->empty()) {
                conditionLock_.wait(lock1);
            }
            // 写文件
            std::lock_guard<std::mutex> lock2(nextBufferMutex_);
            WriteFile(nextBuffer_);
            nextBuffer_->clear();
        }
    }
}


// LOG::private method
void Log::WriteFile(std::shared_ptr<LogBuffer> pBuffer) {
    // printf("WriteFile(string)\n");
    std::lock_guard<std::mutex> lock(FileMutex_);
    if (pBuffer->size() > 0) {
        for (int i = 0; i < pBuffer->size(); ++i) {
            fd_ << pBuffer->getString(i);
        }
    }
}

}