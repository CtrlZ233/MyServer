cmake_minimum_required(VERSION 3.5)
project(MyServer)

# SET(CMAKE_BUILD_TYPE "Debug")
# SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
# SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
file(MAKE_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}/log)
add_library(ISock_library SHARED
    src/ISock.cpp    
)

add_library(ThreadPool_libirary SHARED
    src/ThreadPool.cpp
)

add_library(LOG_libirary SHARED
    src/LOG.cpp
)


add_library(Timer_libirary SHARED
    src/Timer.cpp
)

include_directories(  ${PROJECT_SOURCE_DIR}/include)


add_executable(Server
    src/Server.cpp
)

add_executable(Client
    src/Client.cpp
)

add_executable(test
    src/test.cpp
)

target_link_libraries(Server
    PRIVATE
        ISock_library pthread ThreadPool_libirary LOG_libirary Timer_libirary
)


target_link_libraries(test 
    PRIVATE
        Timer_libirary ThreadPool_libirary pthread
)


target_link_libraries(Client
    PRIVATE
        ISock_library pthread LOG_libirary
)
