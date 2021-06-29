cmake_minimum_required(VERSION 3.0.0)
project(myProject VERSION 0.1.0)

include(CTest)
enable_testing()

file(GLOB srcfile2 "./LeetCode/*.cpp")
add_executable(LeetCode ${srcfile2})

file(GLOB srcfile "./DesignMode/*.cpp")
add_executable(DesignMode ${srcfile})

add_executable(DealFile "./DealFile.cpp")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
