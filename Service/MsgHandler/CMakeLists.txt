include_directories(${PROJECT_SOURCE_DIR}/Socket)
include_directories(${PROJECT_SOURCE_DIR}/Service/MsgAdapter)


set (LIB_SOURCE RegisterMsgHandler.cpp)

add_library(MsgHandler_libirary STATIC ${LIB_SOURCE})