add_subdirectory(MsgHandler)

include_directories(${PROJECT_SOURCE_DIR}/framework/LOG)
include_directories(${PROJECT_SOURCE_DIR}/Socket)
include_directories(${PROJECT_SOURCE_DIR}/Service/MsgAdapter)
include_directories(${PROJECT_SOURCE_DIR}/Service/MsgHandler)

set (LIB_SOURCE MsgDispatcher.cpp  PidAllocator.cpp)

add_library(Service_libirary STATIC ${LIB_SOURCE})
