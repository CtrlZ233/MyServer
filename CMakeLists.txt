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


add_executable(Server
    src/Server.cpp
)

add_executable(Client
    src/Client.cpp
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


target_link_libraries(Client
    PRIVATE
        ISock_library
)