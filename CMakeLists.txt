cmake_minimum_required(VERSION 3.5.0)
project(pack VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(pack test.cpp Database.cpp Toursite.cpp Place.cpp util/Comments.cpp )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
