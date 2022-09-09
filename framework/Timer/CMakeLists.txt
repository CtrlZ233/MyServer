include_directories(${PROJECT_SOURCE_DIR}/SafeContainer)

set (LIB_SOURCE Timer.cpp ITimerListener.cpp)

add_library(Timer_libirary STATIC ${LIB_SOURCE})
