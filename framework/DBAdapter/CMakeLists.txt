include_directories(${PROJECT_SOURCE_DIR}/framework/DBAdapter/UserInfo)

set(LIB_SOURCE DBOperator.cpp)
add_library(DBAdapter_lib OBJECT ${LIB_SOURCE})