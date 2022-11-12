include_directories(${PROJECT_SOURCE_DIR}/NetIO)
include_directories(${PROJECT_SOURCE_DIR}/Service/MsgAdapter)
include_directories(${PROJECT_SOURCE_DIR}/Service)
include_directories(.)


set (LIB_SOURCE RegisterMsgHandler.cpp MsgDispatcher.cpp)

add_library(MsgHandler_libirary SHARED ${LIB_SOURCE})
