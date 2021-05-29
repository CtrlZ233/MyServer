cmake_minimum_required(VERSION 3.5)
project(MyServer)
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

target_include_directories(ISock_library
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/include
)

target_include_directories(ThreadPool_libirary
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/include
)

target_include_directories(LOG_libirary
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/include
)

target_include_directories(Timer_libirary
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/include
)



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
        ISock_library
)

target_link_libraries(Server 
    PRIVATE
        pthread
)

target_link_libraries(Server 
    PRIVATE
        ThreadPool_libirary
)

target_link_libraries(Server 
    PRIVATE
        LOG_libirary
)

target_link_libraries(Server 
    PRIVATE
        Timer_libirary
)

target_link_libraries(test 
    PRIVATE
        Timer_libirary
)

target_link_libraries(test 
    PRIVATE
        ThreadPool_libirary
)

target_link_libraries(test 
    PRIVATE
        pthread
)


target_link_libraries(Client
    PRIVATE
        ISock_library
)
target_link_libraries(Client
    PRIVATE
        pthread
)

target_link_libraries(Client
    PRIVATE
        LOG_libirary
)