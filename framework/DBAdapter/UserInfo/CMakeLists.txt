include_directories(${PROJECT_SOURCE_DIR}/framework/Utils)
include_directories(${PROJECT_SOURCE_DIR}/framework/DBAdapter)
set(LIB_SOURCE UserInfoTable.cpp)

add_library(UserInfo_lib OBJECT ${LIB_SOURCE})