include_directories(${PROJECT_SOURCE_DIR}/framework/DBAdapter)
include_directories(.)

set (LIB_SOURCE UserInfoTable.cpp)

add_library(UserInfo_lib OBJECT ${LIB_SOURCE})
