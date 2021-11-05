#ifndef DEFINES_H_
#define DEFINES_H_
#include "Singleton.h"
#include "LOG.h"


#define GETLOG Utils::Singleton<Utils::Log>::GetInstance()
#define LOG(s) GETLOG.Append((s), __FILE__, std::to_string(__LINE__), __FUNCTION__)


#endif