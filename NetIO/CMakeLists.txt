include_directories(.)
include_directories(${PROJECT_SOURCE_DIR}/framework/Timer)
include_directories(${PROJECT_SOURCE_DIR}/SafeContainer)
include_directories(${PROJECT_SOURCE_DIR}/Service)
include_directories(${PROJECT_SOURCE_DIR}/Service/MsgHandler)
include_directories(${PROJECT_SOURCE_DIR}/Service/MsgAdapter)
set (LIB_SOURCE ISock.cpp EpollService.cpp Connection.cpp Connection.h)

add_library(ISock_library STATIC ${LIB_SOURCE})
