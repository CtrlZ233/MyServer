add_subdirectory(MsgHandler)

include_directories(${PROJECT_SOURCE_DIR}/framework/LOG)
include_directories(${PROJECT_SOURCE_DIR}/Socket)
include_directories(${PROJECT_SOURCE_DIR}/Service/MsgAdapter)
include_directories(${PROJECT_SOURCE_DIR}/Service/MsgHandler)
include_directories(.)

set (LIB_SOURCE   PidAllocator.cpp)

add_library(PidAllocator_lib STATIC ${LIB_SOURCE})
