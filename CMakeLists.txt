cmake_minimum_required(VERSION 3.5)
project(MyServer)
# SET(CMAKE_BUILD_TYPE "Debug")
# SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
# SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O0 -Wall")

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
file(MAKE_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}/log)

add_subdirectory(NetIO)
add_subdirectory(framework)
add_subdirectory(Service)

include_directories(${PROJECT_SOURCE_DIR}/framework/LOG)
include_directories(${PROJECT_SOURCE_DIR}/framework/Pool)
include_directories(${PROJECT_SOURCE_DIR}/framework/Singleton)
include_directories(${PROJECT_SOURCE_DIR}/framework/Timer)
include_directories(${PROJECT_SOURCE_DIR}/framework/DBAdapter)
include_directories(${PROJECT_SOURCE_DIR}/SafeContainer)
include_directories(${PROJECT_SOURCE_DIR}/NetIO)
include_directories(${PROJECT_SOURCE_DIR}/Service)
include_directories(${PROJECT_SOURCE_DIR}/Service/MsgAdapter)
include_directories(${PROJECT_SOURCE_DIR}/Service/MsgHandler)

add_executable(Server
    main.cpp
        )


target_link_libraries(Server PUBLIC
            pthread Timer_lib ISock_lib  ThreadPool_lib LOG_lib MsgHandler_lib Service_lib MsgAdapter_lib
        )
