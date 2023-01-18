include_directories(${PROJECT_SOURCE_DIR}/NetIO)
include_directories(${PROJECT_SOURCE_DIR}/framework/Timer)
include_directories(${PROJECT_SOURCE_DIR}/SafeContainer)
include_directories(${PROJECT_SOURCE_DIR}/Service/MsgAdapter)
include_directories(${PROJECT_SOURCE_DIR}/Service)
include_directories(.)

set(LIB_SOURCE RegisterMsgHandler.cpp MsgDispatcher.cpp DisConnctionMsgHandler.cpp DisConnctionMsgHandler.h)

add_library(MsgHandler_lib OBJECT ${LIB_SOURCE})
