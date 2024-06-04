cmake_minimum_required(VERSION 3.5.0)
project(pack LANGUAGES C CXX)

include(CTest)
enable_testing()
# set(CMAKE_BUILD_TYPE "Debug")
# set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
# set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

#工程根目录(即为CMakeLists.txt文件所在目录)
message("PROJECT_SOURCE_DIR : " ${PROJECT_SOURCE_DIR})
#编译目录(即为执行cmake的目录)
message("PROJECT_BINARY_DIR : " ${PROJECT_BINARY_DIR})
 

# 设置可执行文件的输出位置
#set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

#include_directories(${WORKSPACE_PATH})
#include_directories(${WORKSPACE_PATH}/util)

aux_source_directory(./shc/src SOURCE_FILES)
aux_source_directory(./shc/util/src SOURCE_FILES_UTIL)
#set(SOURCE_FILES test.cpp util/List.cpp util/Comments.cpp Database.cpp Toursite.cpp Place.cpp  )
add_executable(a test.cpp ${SOURCE_FILES} ${SOURCE_FILES_UTIL}
        shc/util/BiMap.h
        shc/util/TablePlace.h)

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
