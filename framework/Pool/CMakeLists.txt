include_directories(${PROJECT_SOURCE_DIR}/SafeContainer)
set (LIB_SOURCE ThreadPool.cpp)

add_library(ThreadPool_lib OBJECT ${LIB_SOURCE})