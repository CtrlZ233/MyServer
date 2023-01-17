add_subdirectory(MsgHandler)
add_subdirectory(MsgAdapter)

include_directories(${PROJECT_SOURCE_DIR}/framework/LOG)
include_directories(${PROJECT_SOURCE_DIR}/framework/Timer)
include_directories(${PROJECT_SOURCE_DIR}/SafeContainer)
include_directories(${PROJECT_SOURCE_DIR}/NetIO)
include_directories(${PROJECT_SOURCE_DIR}/Service/MsgAdapter)
include_directories(${PROJECT_SOURCE_DIR}/Service/MsgHandler)
include_directories(.)

set (LIB_SOURCE PidAllocator.cpp EpollService.cpp Connection.cpp MsgAdapter/MsgEncoder.cpp MsgAdapter/MsgEncoder.h)

add_library(Service_lib OBJECT ${LIB_SOURCE})
