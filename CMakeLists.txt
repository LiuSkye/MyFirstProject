cmake_minimum_required(VERSION 3.0.0)
project(myProject VERSION 0.1.0)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_C_COMPILER "D:/OneDrive/MinGW64/bin/x86_64-w64-mingw32-gcc.exe")

# set(CMAKE_CXX_COMPILER "D:/OneDrive/MinGW64/bin/x86_64-w64-mingw32-g++.exe")

# find_package(MPI REQUIRED) 
# if (MPI_FOUND) 
#     include_directories(SYSTEM ${MPI_INCLUDE_PATH}) 
# else (MPI_FOUND) 
#     message(SEND_ERROR "This application cannot compile without MPI") 
# endif (MPI_FOUND) 

file(GLOB srcfile2 "./LeetCode/*.cpp")
add_executable(LeetCode ${srcfile2})

file(GLOB srcfile "./DesignMode/*.cpp")
add_executable(DesignMode ${srcfile})

add_executable(DealFile "./DealFile.cpp")
add_executable(huawei "./huawei.cpp")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
