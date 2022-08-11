include_directories(${PROJECT_SOURCE_DIR}/framework/Singleton)
include_directories(${PROJECT_SOURCE_DIR}/SafeContainer)

set (LIB_SOURCE LOG.cpp)

add_library(LOG_libirary STATIC ${LIB_SOURCE})
