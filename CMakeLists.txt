cmake_minimum_required(VERSION 3.5)
project(MyServer)
# SET(CMAKE_BUILD_TYPE "Debug")
# SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
# SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
file(MAKE_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}/log)

add_subdirectory(Socket)
add_subdirectory(framework)
add_subdirectory(Service)

include_directories(${PROJECT_SOURCE_DIR}/framework/LOG)
include_directories(${PROJECT_SOURCE_DIR}/framework/Pool)
include_directories(${PROJECT_SOURCE_DIR}/framework/Singleton)
include_directories(${PROJECT_SOURCE_DIR}/framework/Timer)
include_directories(${PROJECT_SOURCE_DIR}/SafeContainer)
include_directories(${PROJECT_SOURCE_DIR}/Socket)

add_executable(Server
    main.cpp
)

# add_executable(Client
#     src/Client.cpp
# )

# add_executable(test
#     src/test.cpp
# )

target_link_libraries(Server
    PRIVATE
        ISock_library pthread ThreadPool_libirary LOG_libirary Timer_libirary
)


# target_link_libraries(test 
#     PRIVATE
#         Timer_libirary ThreadPool_libirary pthread
# )


# target_link_libraries(Client
#     PRIVATE
#         ISock_library pthread LOG_libirary
# )
